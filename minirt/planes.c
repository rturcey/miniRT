#include "minirt.h"

void	init_plane(t_vector origin, t_vector range, char effect)
{
	g_o[g_nobjs].origin = origin;
	g_o[g_nobjs].rot = range;
	g_o[g_nobjs].effect = effect;
	g_o[g_nobjs].type = 'p';
	g_o[g_nobjs].composed = -1;
	g_o[g_nobjs].nobjs = g_nobjs;
	g_o[g_nobjs].rb = -1;
	g_nobjs++;
}

int		interplane(t_object r, t_object pl, double *t)
{
	double		scal;
	double		d;

	scal = scal_v(min_v(r.origin, pl.origin), pl.rot);
	d = scal_v(r.dir, pl.rot);
	if (d == 0)
		return (0);
	if (-scal / d > 0)
	{
		*t = -scal / d;
		return (1);
	}
	return (0);
}
