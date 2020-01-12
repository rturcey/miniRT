#include "minirt.h"

void	init_cone(t_vector origin, t_vector r, double h, double rayon, char effect)
{
	r = normed(r);
	g_o[g_nobjs].origin = origin;
	g_o[g_nobjs].rayon = rayon;
	g_o[g_nobjs].h = h;
	g_o[g_nobjs].effect = effect;
	g_o[g_nobjs].rot = r;
	g_o[g_nobjs].type = 'o';
	g_o[g_nobjs].nobjs = g_nobjs;
	g_o[g_nobjs].composed = -1;
	g_o[g_nobjs].effect = effect;
	g_o[g_nobjs].rb = -1;
	g_nobjs++;
}

int		intercone(t_object r, t_object co, double *t)
{
	double		q[3];
	double		a[4];
	double		delta;
	t_vector	v[2];

	v[0] = min_v(r.origin, co.origin);
	v[1] = mult_v(-1, r.dir);
	a[0] = tan(co.rayon * M_PI / 180);
	a[1] = 1 + a[0] * a[0];
	a[2] = scal_v(v[1], co.rot);
	a[3] = scal_v(v[0], co.rot);
	q[0] = scal_v(v[1], v[1]) - (a[1] * a[2] * a[2]);
	q[1] = 2 * (scal_v(v[1], v[0]) - (a[1] * a[2] * a[3]));
	q[2] = scal_v(v[0], v[0]) - (a[1] * a[3] * a[3]);
	delta = q[1] * q[1] - 4 * q[0] * q[2];
	if (delta <= 0)
		return (0);
	a[0] = (q[1] - sqrt(delta)) / (2 * q[0]);
	a[1] = (q[1] + sqrt(delta)) / (2 * q[0]);
	if ((*t = quadracone(r, co, a)) == -1)
	{
		*t = 1E99;
		return (0);
	}
	return (1);
}

double	quadracone(t_object r, t_object co, double *a)
{
	t_vector	v;
	double		s;

	s = 1E99;
	if (a[0] > 0)
	{
		v = add_v(mult_v(a[0], r.dir), min_v(r.origin, co.origin));
		a[3] = scal_v(v, co.rot);
		if (a[3] <= co.h / 2 && a[3] >= -co.h / 2)
			s = a[0];
	}
	if (a[1] > 0)
	{
		v = add_v(mult_v(a[1], r.dir), min_v(r.origin, co.origin));
		a[3] = scal_v(v, co.rot);
		if (a[3] <= co.h / 2 && a[3] >= -co.h / 2 && a[1] < s)
			s = a[1];
	}
	if (s < 1E99)
		return (s);
	return (-1);
}
