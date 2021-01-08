#include <GL/glut.h>
#include <math.h>
#include <stdio.h>
#include "genart.h"

// globals
double expcoeff=0.05;
double wamp=300.0;
double rcoeff=0.8;
double m=1.0;
// end globals

// funxions
void d(char* msg)
{
  printf("%s\n",msg);
}

void init()
{
  glClearColor(0,0,0,0);
  glMatrixMode(GL_PROJECTION);
  gluOrtho2D(0,1280,0,720);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
}

double drnd(){
  double dr=(double)rand();
  return dr/(double)RAND_MAX;
}

void cloud(double x1,double y1,double x2,double y2)
{
  double br=15;
  for(int i=0;i<150;i++)
  {
    double xavg=(x1+x2)/2.0;
    double yavg=(y1+y2)/2.0;
    double rr=br*drnd();
    double f=0.05*drnd();
    //double f=drnd();
    double xx=xavg+rr*cos(i*f);
    double yy=yavg+rr*sin(i*f);
    glVertex2f(xx,yy);
  }
}

void art_00(double cx,double cy,double n)
{
  double t=0.0;
  vec2 a={.x=0,.y=0};
  for(int i=0;i<n;i++)
  {
    glVertex2f(cx+a.x,cy+a.y);
    a.x+=3*exp(-0.0125*t)*cos(m*t);
    a.y+=3*sin(1*t);
    t+=0.01;
  }
}

void art_01(double cx,double cy,double n)
{
  double t=0.0;
  vec2 a={.x=0,.y=0};
  for(int i=0;i<n;i++)
  {
    glVertex2f(cx+a.x,cy+a.y);
    a.x+=3*exp(-0.025*t)*cos(m*t);
    a.y+=3*exp(-0.015*t)*sin(1*t);
    t+=0.01;
  }
}

void art_02(double cx,double cy,double n)
{
  double t=0.0;
  double ox=cx;
  double oy=cy;
  vec2 a={.x=0,.y=0};
  for(int i=0;i<n;i++)
  {
    cloud(ox,oy,cx+a.x,cy+a.y);
    a.x+=3*exp(-0.025*t)*cos(m*t);
    a.y+=3*exp(-0.015*t)*sin(1*t);
    t+=0.01;
    ox=cx+a.x;
    oy=cy+a.y;
  }
}

void draw()
{
  glClear(GL_COLOR_BUFFER_BIT);
  glColor4f(0.2,1,1,0.1);
  glBegin(GL_POINTS);
    art_02(600,50,5000);
  glEnd();
  glFlush();
}
// end funxions

// sensors
void keydown(unsigned char key,int x,int y)
{
  if(key=='q')
  {
    d("exiting. bye!");
    exit(0);
  }
}

void mousemove(int x,int y)
{
  if(x>0.0 && x<1280.0)
  {
    rcoeff=((double)x)/1280.0;
    m=1+rcoeff;
    glutPostRedisplay();
  }
}
// end sensors

// flow
void main(int argc,char **argv)
{
  glutInit(&argc,argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glutInitWindowPosition(50,100);
  glutInitWindowSize(1280,720);
  glutCreateWindow("opengl-genart");
  
  init();
  glutDisplayFunc(draw);
  glutKeyboardFunc(keydown);
  glutPassiveMotionFunc(mousemove);
  glutMainLoop();
}

