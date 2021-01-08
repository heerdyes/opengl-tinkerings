#include<GL/glut.h>
#include<math.h>

void init()
{
  glClearColor(0,0,0,0);
  glMatrixMode(GL_PROJECTION);
  gluOrtho2D(0,1280,0,720);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
}

void wave1(double a,double f,double c,double p,int r)
{
  for(int i=0;i<r;i++)
  {
    glVertex2f(i,c+a*sin(i*f+p));
  }
}

void draw()
{
  glClear(GL_COLOR_BUFFER_BIT);
  glColor4f(0,1,1,0.40);
  glBegin(GL_POINTS);
    for(int i=0;i<60;i++)
    {
      wave1(200,0.05+0.005*sin(0.02*i),400,i*0.02,1100);
    }
  glEnd();
  glFlush();
}

void main(int argc,char **argv)
{
  glutInit(&argc,argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glutInitWindowPosition(50,100);
  glutInitWindowSize(1280,720);
  glutCreateWindow("opengl example");
  
  init();
  glutDisplayFunc(draw);
  glutMainLoop();
}
