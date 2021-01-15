// abstract types
typedef struct vec2
{
  double x;
  double y;
}vec2;

typedef struct particle
{
  double x;
  double y;
  vec2 v;
}particle;

typedef struct parsys
{
  double radius;
  particle swarm[];
}parsys;
// end abstract types

