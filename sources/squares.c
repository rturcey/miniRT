
#include "minirt.h"

void	create_square(t_object *o)
{
	o->o1 = add_v(o->origin, rot_xyz(utd_v(-o->h / 2, 0, o->h / 2), o->rot));
	o->o2 = add_v(o->origin, rot_xyz(utd_v(o->h / 2, 0, -o->h / 2), o->rot));
	o->s1 = add_v(o->origin, rot_xyz(utd_v(o->h / 2, 0, o->h / 2), o->rot));
	o->s2 = add_v(o->origin, rot_xyz(utd_v(-o->h / 2, 0, -o->h / 2), o->rot));
}

int		intersquarebis(t_object r, t_object sq, double *t)
{
	double		d[3];
	t_vector	v[5];

	v[0] = min_v(sq.s1, sq.o1);
	v[1] = min_v(sq.s2, sq.o1);
	v[2] = cross_v(r.dir, v[1]);
	d[0] = scal_v(v[0], v[2]);
	if (d[0] == 0)
		return (0);
	d[0] = 1 / d[0];
	v[3] = min_v(r.origin, sq.o1);
	d[1] = d[0] * scal_v(v[3], v[2]);
	if (d[1] < 0 || d[1] > 1)
		return (0);
	v[4] = cross_v(v[3], v[0]);
	d[2] = d[0] * scal_v(r.dir, v[4]);
	if (d[2] < 0.0 || d[1] + d[2] > 1.0)
		return (0);
	d[1] = d[0] * scal_v(v[1], v[4]);
	if (d[1] > 0.001)
	{
		*t = d[1];
		return (1);
	}
	return (0);
}

int		intersquarebisbis(t_object r, t_object sq, double *t)
{
	double		d[3];
	t_vector	v[5];

	v[0] = min_v(sq.s1, sq.o2);
	v[1] = min_v(sq.s2, sq.o2);
	v[2] = cross_v(r.dir, v[1]);
	d[0] = scal_v(v[0], v[2]);
	if (d[0] == 0)
		return (0);
	d[0] = 1 / d[0];
	v[3] = min_v(r.origin, sq.o2);
	d[1] = d[0] * scal_v(v[3], v[2]);
	if (d[1] < 0 || d[1] > 1)
		return (0);
	v[4] = cross_v(v[3], v[0]);
	d[2] = d[0] * scal_v(r.dir, v[4]);
	if (d[2] < 0.0 || d[1] + d[2] > 1.0)
		return (0);
	d[1] = d[0] * scal_v(v[1], v[4]);
	if (d[1] > 0.001)
	{
		*t = d[1];
		return (1);
	}
	return (0);
}

int		intersquare(t_object r, t_object sq, double *t)
{
	double	tbis;

	if (intersquarebis(r, sq, &tbis) == 1 || \
		intersquarebisbis(r, sq, &tbis) == 1)
	{
		*t = tbis;
		return (1);
	}
	return (0);
}

t_vector	square_normal(t_object o, t_object r)
{
	t_vector	n;

	n = cross_v(min_v(o.s1, o.o1), min_v(o.s2, o.o1));
	if (scal_v(normed(n), r.dir) > 0)
		n = cross_v(min_v(o.s2, o.o1), min_v(o.s1, o.o1));
	return (n);
}