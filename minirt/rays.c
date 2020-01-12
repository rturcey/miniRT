#include "minirt.h"

void		init_ray(double x, double y, double z, t_vector range)
{
	t_object	r;

	r.origin.x = x;
	r.origin.y = y;
	r.origin.z = z;
	r.dir.x = 0;
	r.dir.y = 0;
	r.dir.z = 0;
	r.type = 'r';
	r.rot = range;
	g_r[g_nbcams++] = r;
}

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

	d = -g_w / (2 * tan(p->fov / 2));
	x -= g_w / 2;
	y -= g_h / 2;
	return (dirch_ray(p->ray, x, y, d));
}
