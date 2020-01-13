#include "minirt.h"

t_object	dirch_ray(t_object ray, double x, double y, double z)
{
	t_object	r;

	r.origin.x = ray.origin.x;
	r.origin.y = ray.origin.y;
	r.origin.z = ray.origin.z;
	r.dir.x = x;
	r.dir.y = y;
	r.dir.z = z;
	r.rot = ray.rot;
	return (r);
}

t_object	spray(t_p *p, double x, double y)
{
	double	d;

	d = -p->w / (2 * tan(p->fov / 2));
	x -= p->w / 2;
	y -= p->h / 2;
	return (dirch_ray(p->ray, x, y, d));
}
