#include "minirt.h"

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
