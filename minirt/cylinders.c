#include "minirt.h"

void	init_cylinder(t_vector origin, t_vector r, double h, double rayon, char effect)
{
	t_vector	c;

	r = normed(r);
	g_o[g_nobjs].origin = origin;
	g_o[g_nobjs].rayon = rayon;
	g_o[g_nobjs].h = h;
	g_o[g_nobjs].effect = effect;
	g_o[g_nobjs].rot = r;
	g_o[g_nobjs].type = 'c';
	g_o[g_nobjs].nobjs = g_nobjs;
	g_o[g_nobjs].composed = -1;
	g_o[g_nobjs].rb = -1;
	g_nobjs++;
	if (g_o[g_nobjs - 1].disks == 0)
		return ;
	c = mult_v(h / 2, r);
	c = min_v(origin, c);
	g_o[g_nobjs].col = g_o[g_nobjs - 1].col;
	init_disk(c, r, rayon, effect);
	g_o[g_nobjs - 1].composed = g_nobjs - 2;
	c = mult_v(h / 2, r);
	c = add_v(origin, c);
	g_o[g_nobjs].col = g_o[g_nobjs - 1].col;
	init_disk(c, r, rayon, effect);
	g_o[g_nobjs - 1].composed = g_o[g_nobjs - 2].composed;
}

void	init_disk(t_vector origin, t_vector r, double rayon, char effect)
{
	g_o[g_nobjs].origin = origin;
	g_o[g_nobjs].rayon = rayon;
	g_o[g_nobjs].effect = effect;
	g_o[g_nobjs].rot = r;
	g_o[g_nobjs].type = 'd';
	g_o[g_nobjs].composed = -1;
	g_o[g_nobjs].nobjs = g_nobjs;
	g_o[g_nobjs].rb = -1;
	g_nobjs++;
}

int		interdisk(t_object r, t_object d, double *t)
{
	t_vector	p;
	double		dist;

	if (interplane(r, d, t) == 1)
	{
		p = add_v(r.origin, mult_v(*t, r.dir));
		p = min_v(p, d.origin);
		dist = scal_v(p, p);
		if (sqrt(dist) <= d.rayon / 2)
			return (1);
	}
	return (0);
}

int		intercylinder(t_object r, t_object cy, double *t)
{
	double		d[4];
	t_vector	v[3];
	double		delta;

	v[2] = min_v(r.origin, cy.origin);
	v[0] = min_v(r.dir, mult_v(scal_v(r.dir, cy.rot), cy.rot));
	d[0] = scal_v(v[0], v[0]);
	v[1] = min_v(v[2], mult_v(scal_v(v[2], cy.rot), cy.rot));
	d[1] = 2 * scal_v(v[0], v[1]);
	d[2] = scal_v(v[1], v[1]) - pow(cy.rayon / 2, 2);
	delta = d[1] * d[1] - 4 * d[0] * d[2];
	if (delta < 0)
		return (0);
	*t = (-d[1] - sqrt(delta)) / (2 * d[0]);
	d[3] = (-d[1] + sqrt(delta)) / (2 * d[0]);
	return (quadracylinder(r, cy, d, t));
}

int		quadracylinder(t_object r, t_object cy, double *d, double *t)
{
	t_vector	v;

	if (*t > 0)
	{
		v = add_v(mult_v(*t, r.dir), min_v(r.origin, cy.origin));
		d[2] = scal_v(v, cy.rot);
		if (d[2] < cy.h / 2 && d[2] > -cy.h / 2)
			return (1);
	}
	*t = d[3];
	if (*t > 0)
	{
		v = add_v(mult_v(*t, r.dir), min_v(r.origin, cy.origin));
		d[2] = scal_v(v, cy.rot);
		if (d[2] < cy.h / 2 && d[2] > -cy.h / 2)
			return (1);
	}
	return (0);
}
