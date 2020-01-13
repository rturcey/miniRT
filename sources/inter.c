#include "minirt.h"

int			inters(t_object r, t_object o, double *t)
{
	if (o.type == 's')
		return (intersphere(r, o, t));
	if (o.type == 'p')
		return (interplane(r, o, t));
	if (o.type == 't')
		return (intertriangle(r, o, t));
	if (o.type == 'q')
		return (intersquare(r, o, t));
	if (o.type == 'c')
		return (intercylinder(r, o, t));
	if (o.type == 'd')
		return (interdisk(r, o, t));
	if (o.type == 'o')
		return (intercone(r, o, t));
	return (0);
}

int			interobj(t_object r, t_p *par)
{
	int		i;
	double	min;
	double	t;
	int		o_id;

	min = 1E99;
	i = 0;
	o_id = 0;
	while (i < par->nobjs)
	{
		if (inters(r, par->o[i], &t) == 1)
		{
			if (t <= min)
			{
				min = t;
				par->p = add_v(r.origin, mult_v(t, r.dir));
				o[i].dist = t;
				par->n = get_normal(o[i], par->p, r, t);
				o_id = i + 1;
			}
		}
		i++;
	}
	return (o_id);
}

double		interlight(t_object r, t_p *par, double *min)
{
	int		i;
	int		k;
	double	d_light;
	double	has_inter;

	k = 0;
	*min = 1E99;
	i = 0;
	has_inter = 0;
	while (i < par->nobjs)
	{
		if (inters(r, o[i], &d_light) == 1)
		{
			if (d_light <= *min)
			{
				has_inter = 1;
				*min = d_light;
			}
		}
		i++;
	}
	return (has_inter);
}

t_vector	get_normal(t_object o, t_vector *p, t_object r, double t)
{
	t_vector	n;

	n = utd_v(0, 0, 0);
	if (o.type == 'p' || o.type == 'd')
	{
		n = min_v(o.rot, o.origin);
		if (o.type == 'd' && scal_v(normed(n), r.dir) > 0)
			n = mult_v(-1, n);
	}
	else if (o.type == 't')
		n = triangle_normal(o, r);
	else if (o.type == 'q')
		n = square_normal(o, r);
	else if (o.type == 's')
		n = min_v(*p, o.origin);
	else if (o.type == 'c')
		n = cylinder_normal(o, p, r, t);
	else if (o.type == 'o')
		n = cone_normal(o, p, r, t);
	if (o.effect >= 'A' && o.effect <= 'Z')
		n = utd_v(sin(50 * n.x + 100 * p->x), sin(50 * n.y + 100 * p->x), sin(50 * n.z + 100 * p->z));
	n = normed(n);
	return (n);
}
