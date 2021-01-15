#define PI 3.141592654

typedef struct turtle
{
  double x;
  double y;
  double a;
}turtle;

turtle create_turtle(double cx,double cy)
{
  turtle t1={.x=cx,.y=cy,.a=0};
  return t1;
}

void fd(turtle t,double r)
{
  double newx=t.x+r*cos(t.a);
  double newy=t.y+r*sin(t.a);
  /*
  glBegin(GL_LINES);
    glVertex2f(t.x,t.y);
    glVertex2f(newx,newy);
  glEnd();
  */
  t.x=newx;
  t.y=newy;
}

void lt(turtle t,double th)
{
  t.a+=th*PI/180.0;
}

void rt(turtle t,double th)
{
  lt(t,-th);
}

void bk(turtle t,double r)
{
  fd(t,-r);
}

