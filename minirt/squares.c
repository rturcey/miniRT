#include "minirt.h"

void	init_square(t_vector o, t_vector r, double h, char effect)
{
	g_o[g_nobjs].origin = o;
	g_o[g_nobjs].rot = r;
	g_o[g_nobjs].h = h;
	g_o[g_nobjs].origin1 = add_v(o, rot_xyz(utd_v(-h / 2, 0, h / 2), r));
	g_o[g_nobjs].origin2 = add_v(o, rot_xyz(utd_v(h / 2, 0, -h / 2), r));
	g_o[g_nobjs].s1 = add_v(o, rot_xyz(utd_v(h / 2, 0, h / 2), r));
	g_o[g_nobjs].s2 = add_v(o, rot_xyz(utd_v(-h / 2, 0, -h / 2), r));
	g_o[g_nobjs].effect = effect;
	g_o[g_nobjs].type = 'q';
	g_o[g_nobjs].composed = -1;
	g_o[g_nobjs].nobjs = g_nobjs;
	g_o[g_nobjs].rb = -1;
	g_nobjs++;
}

int		intersquarebis(t_object r, t_object sq, double *t)
{
	double		d[3];
	t_vector	v[5];

	v[0] = min_v(sq.s1, sq.origin1);
	v[1] = min_v(sq.s2, sq.origin1);
	v[2] = cross_v(r.dir, v[1]);
	d[0] = scal_v(v[0], v[2]);
	if (d[0] == 0)
		return (0);
	d[0] = 1 / d[0];
	v[3] = min_v(r.origin, sq.origin1);
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

	v[0] = min_v(sq.s1, sq.origin2);
	v[1] = min_v(sq.s2, sq.origin2);
	v[2] = cross_v(r.dir, v[1]);
	d[0] = scal_v(v[0], v[2]);
	if (d[0] == 0)
		return (0);
	d[0] = 1 / d[0];
	v[3] = min_v(r.origin, sq.origin2);
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
