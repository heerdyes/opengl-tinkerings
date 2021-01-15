#include <GL/glut.h>
#include <math.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "genart.h"
#include "midilib.h"
#include "turtle.h"

// globals
double expcoeff=0.05;
double wamp=300.0;
double rcoeff=0.8;
double m=1.0;
double q=1.0;
unsigned char inpacket[4];
int seqfd;
turtle T;
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

void drawing_00(double cx,double cy,double n)
{
  int m0=(int)inpacket[0];
  int kn=(int)inpacket[1];
  int vu=(int)inpacket[2];
  int ch=(int)inpacket[3];
  double f=5.0;
  double l=1.0;
  printf("[art_02] m0=%d,kn=%d,vu=%d,ch=%d\n",m0,kn,vu,ch);
  for(int i=0;i<n;i++)
  {
    cloud(T.x-5,T.y-5,T.x+5,T.y+5);
    if(m0==176 && kn==3){ f=((double)vu); }
    else if(m0==176 && kn==9){ l=(double)vu; }
    fd(T,f);
    lt(T,l);
  }
}

void draw()
{
  glClear(GL_COLOR_BUFFER_BIT);
  glColor4f(0.2,1,1,0.1);
  glBegin(GL_POINTS);
    drawing_00(600,0,10);
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
  initmidi();
  T=create_turtle(600,350);
  
  glutDisplayFunc(draw);
  glutKeyboardFunc(keydown);
  glutIdleFunc(rdmidipkts);
  glutMainLoop();
}

