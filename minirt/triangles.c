#include "minirt.h"

void	init_triangle(t_vector origin, t_vector s1, t_vector s2, char effect)
{
	g_o[g_nobjs].origin = origin;
	g_o[g_nobjs].true_origin = origin;
	g_o[g_nobjs].s1 = s1;
	g_o[g_nobjs].s2 = s2;
	g_o[g_nobjs].effect = effect;
	g_o[g_nobjs].type = 't';
	g_o[g_nobjs].composed = -1;
	g_o[g_nobjs].nobjs = g_nobjs;
	g_o[g_nobjs].rb = -1;
	g_nobjs++;
}

int		intertriangle(t_object r, t_object tr, double *t)
{
	double		d[3];
	t_vector	v[5];

	v[0] = min_v(tr.s1, tr.origin);
	v[1] = min_v(tr.s2, tr.origin);
	v[2] = cross_v(r.dir, v[1]);
	d[0] = scal_v(v[0], v[2]);
	if (d[0] == 0)
		return (0);
	d[0] = 1 / d[0];
	v[3] = min_v(r.origin, tr.origin);
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
