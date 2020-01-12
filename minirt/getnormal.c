#include "minirt.h"

t_vector	triangle_normal(t_object o, t_object r)
{
	t_vector	n;

	n = cross_v(min_v(o.s1, o.origin), min_v(o.s2, o.origin));
	if (scal_v(normed(n), r.dir) > 0)
		n = cross_v(min_v(o.s2, o.origin), min_v(o.s1, o.origin));
	return (n);
}

t_vector	square_normal(t_object o, t_object r)
{
	t_vector	n;

	n = cross_v(min_v(o.s1, o.origin1), min_v(o.s2, o.origin1));
	if (scal_v(normed(n), r.dir) > 0)
		n = cross_v(min_v(o.s2, o.origin1), min_v(o.s1, o.origin1));
	return (n);
}

t_vector	cylinder_normal(t_object o, t_vector *p, t_object r, double t)
{
	t_vector	n;
	double		temp;

	o.rot = utd_v(sin(o.rot.x), sin(o.rot.y), sin(o.rot.z));
	n = min_v(r.origin, o.origin);
	temp = scal_v(r.dir, mult_v(t, o.rot)) + scal_v(n, o.rot);
	n = add_v(o.origin, mult_v(temp, o.rot));
	return (min_v(*p, n));
}

t_vector	cone_normal(t_object o, t_vector *p, t_object r, double t)
{
	t_vector	n;
	double		temp;

	temp = scal_v(r.dir, o.rot) * t + scal_v(min_v(r.origin, o.origin), o.rot);
	n = min_v(min_v(*p, o.origin), mult_v(temp, mult_v((1 + \
		pow(tan(o.rayon * M_PI / 180), 2)), o.rot)));
	return (n);
}

t_vector	get_normal(t_object o, t_vector *p, t_object r, double t)
{
	t_vector	n;

	n = utd_v(0, 0, 0);
	if (o.type == 'p' || o.type == 'd')
	{
		n = min_v(o.rot, o.origin);
		if (o.type == 'd' && scal_v(normed(n), r.dir) > 0)
			n = mult_v(-1, n);
	}
	else if (o.type == 't')
		n = triangle_normal(o, r);
	else if (o.type == 'q')
		n = square_normal(o, r);
	else if (o.type == 's')
		n = min_v(*p, o.origin);
	else if (o.type == 'c')
		n = cylinder_normal(o, p, r, t);
	else if (o.type == 'o')
		n = cone_normal(o, p, r, t);
	if (o.effect >= 'A' && o.effect <= 'Z')
		n = utd_v(sin(50 * n.x + 100 * p->x), sin(50 * n.y + 100 * p->x), sin(50 * n.z + 100 * p->z));
	n = normed(n);
	return (n);
}
