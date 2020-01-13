#include "minirt.h"

t_vector	get_pixel(int x, int y, t_p *p)
{
	int			nb;
	t_color		c;
	t_vector	v;

	v = utd_v(255, 255, 255);
	if (x >= 0 && x <= p->uvmap->x - 1 && y > 0 && y <= p->uvmap->y - 1)
	{
		nb = ((p->uvmap->x * p->uvmap->y[1])) - (p->uvmap->x * y - x);
		if (nb < 0)
			nb = 0;
		c = p->uvmap->img[nb];
		v = utd_colors_object(c.red, c.green, c.blue);
	}
	return (v);
}

t_vector	px_mapping(t_object s, t_p *p)
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
	n[0] = min_v(p->p, s.origin);
	n[0] = normed(n[0]);
	v = acos(-scal_v(n[2], n[0])) / M_PI;
	u = (acos(scal_v(n[0], n[1]) / sin(v * M_PI))) / (2 * M_PI);
	if (scal_v(cross_v(n[2], n[1]), n[0]) <= 0)
		u = 1 - u;
	v *= p->uvmap->y;
	u *= p->uvmap->x;
	x = ((int)u) % p->uvmap->x;
	y = ((int)v) % p->uvmap->y;
	return (get_pixel(x, y, p));
}
