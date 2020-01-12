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

int			interobj(t_object r, t_object *o, t_vector *p, t_vector *n)
{
	int		i;
	double	min;
	double	t;
	int		o_id;

	min = 1E99;
	i = 0;
	o_id = 0;
	while (i < g_nobjs)
	{
		if (inters(r, o[i], &t) == 1)
		{
			if (t <= min)
			{
				min = t;
				*p = add_v(r.origin, mult_v(t, r.dir));
				o[i].dist = t;
				*n = get_normal(o[i], p, r, t);
				o_id = i + 1;
			}
		}
		i++;
	}
	return (o_id);
}

double		interlight(t_object r, t_object *o, double *min)
{
	int		i;
	int		k;
	double	d_light;
	double	has_inter;

	k = 0;
	*min = 1E99;
	i = 0;
	has_inter = 0;
	while (i < g_nobjs)
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
