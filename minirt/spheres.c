#include "minirt.h"

void	init_sphere(t_vector origin, double rayon, char effect)
{
	g_o[g_nobjs].origin = origin;
	g_o[g_nobjs].rayon = rayon;
	g_o[g_nobjs].effect = effect;
	g_o[g_nobjs].type = 's';
	g_o[g_nobjs].composed = -1;
	g_o[g_nobjs].nobjs = g_nobjs;
	g_o[g_nobjs].rb = -1;
	g_nobjs++;
}

int		intersphere(t_object r, t_object s, double *t)
{
	double	a;
	double	b;
	double	c;
	double	delta;
	double	t2[2];

	a = scal_v(r.dir, r.dir);
	b = 2 * scal_v(r.dir, min_v(r.origin, s.origin));
	c = norm_v(min_v(r.origin, s.origin)) - (s.rayon * s.rayon);
	delta = b * b - 4 * a * c;
	if (delta < 0)
		return (0);
	t2[0] = (-b - sqrt(delta)) / (2 * a);
	t2[1] = (-b + sqrt(delta)) / (2 * a);
	if (t2[1] <= 0)
		return (0);
	if (t2[0] > 0)
		*t = t2[0];
	else
		*t = t2[1];
	return (1);
}
