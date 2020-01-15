#include "minirt.h"

t_object	spray(t_p *p, double x, double y)
{
	p->ray.dir.x = x - p->w / 2;
	p->ray.dir.y = y - p->h / 2;
	p->ray.dir.z = -p->w / (2 * tan(p->fov / 2));
	return (p->ray);
}
