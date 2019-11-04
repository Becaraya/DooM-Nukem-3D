#include <stdio.h>
#include <math.h>

typedef struct		s_walls
{
	double			x1;
	double			y1;
	double			x2;
	double			y2;
}					t_walls;

typedef struct		s_ent
{
	double			posx;
	double			posy;
}					t_entity;
#define Y 1
#define X 0

   // b1 /= a2;
    //b2 /= a2;
   // a1 /= a2;
   // a2 = a2 / a2 - a1;
    //b1 -= b2;
   // b1 /= a2;
double		work_on(t_walls w, t_entity e)
{
    double a[2];
    double b[2];
    double x;
    double y;

	printf("  y2:%f y1:%f x2:%f x1:%f\n\n",w.y2,w.y1,w.x2,w.x1);
	a[0] = (w.y2 - w.y1) / (w.x2 - w.x1);
	b[0] = w.y2 - (a[0] * w.x2);
	a[1] = -1 / a[0];
	b[1] = e.posy - (a[1] *e.posx);
	printf("a[0]: %f a[1]: %f b[0]: %f b[1]: %f\n\n",a[0],a[1],b[0],b[1]);

    x = ((b[0] / a[1]) - (b[1] / a[1])) / (a[1] / a[1] - (a[0] / a[1]));
    y = (a[0] * x) + b[0];
    printf("a[0]: %f a[1]: %f b[0]: %f b[1]: %f   \n\nx:  %f\ny:  %f\n\n",a[0],a[1],b[0],b[1],x,y);
    return (sqrt((x - e.posx) * (x - e.posx) + (y - e.posy) * (y - e.posy)));
}

int main()
{
    t_walls w;
    t_entity e;

    w.x1 = 2;
    w.x2 = 0;
    w.y1 = 1;
    w.y2 = 5;
    e.posx = 4;
    e.posy = 6;

    
    printf("distance: %f\n",work_on(w, e));
}