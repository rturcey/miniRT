#include "minirt.h"

t_vector	get_pixel(int x, int y)
{
	int			nb;
	t_color		c;
	t_vector	v;

	v = utd_v(255, 255, 255);
	if (x >= 0 && x <= g_flemme[0] - 1 && y > 0 && y <= g_flemme[1] - 1)
	{
		nb = ((g_flemme[0] * g_flemme[1])) - (g_flemme[0] * y - x);
		if (nb < 0)
			nb = 0;
		c = g_buffy[nb];
		v = utd_colors_object(c.red, c.green, c.blue);
	}
	return (v);
}

t_vector	px_mapping(t_object s, t_vector p)
{
	double		u;
	double		v;
	int			x;
	int			y;
	t_vector	n[3];

	n[2] = utd_v(0, s.rayon, 0);
	n[1] = utd_v(0, 0, -s.rayon);
	n[1] = normed(n[1]);
	n[2] = normed(n[2]);
	n[0] = min_v(p, s.origin);
	n[0] = normed(n[0]);
	v = acos(-scal_v(n[2], n[0])) / M_PI;
	u = (acos(scal_v(n[0], n[1]) / sin(v * M_PI))) / (2 * M_PI);
	if (scal_v(cross_v(n[2], n[1]), n[0]) <= 0)
		u = 1 - u;
	v *= g_flemme[1];
	u *= g_flemme[0];
	x = ((int)u) % g_flemme[0];
	y = ((int)v) % g_flemme[1];
	return (get_pixel(x, y));
}
