/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inter.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rturcey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 14:44:58 by rturcey           #+#    #+#             */
/*   Updated: 2020/01/15 14:45:00 by rturcey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int			inters(t_object r, t_object o, double *t)
{
	if (o.t == 's')
		return (intersphere(r, o, t));
	if (o.t == 'p')
		return (interplane(r, o, t));
	if (o.t == 't')
		return (intertriangle(r, o, t));
	if (o.t == 'q')
		return (intersquare(r, o, t));
	if (o.t == 'c')
		return (intercylinder(r, o, t));
	if (o.t == 'd')
		return (interdisk(r, o, t));
	if (o.t == 'o')
		return (intercone(r, o, t));
	return (0);
}

int			interobj(t_object r, t_p *par, t_object *o)
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
		if (inters(r, o[i], &t) == 1)
		{
			if (t <= min)
			{
				min = t;
				par->p = utd_v(0, 0, 0);
				par->p = add_v(r.o, mult_v(t, r.dir));
				o[i].dist = t;
				par->n = get_normal(o[i], par->p, r, t);
				o_id = i + 1;
			}
		}
		i++;
	}
	return (o_id);
}

double		interlight(t_object r, t_p *par, double *min, t_object *o)
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

t_vector	get_normal(t_object o, t_vector p, t_object r, double t)
{
	t_vector	n;

	n = utd_v(0, 0, 0);
	if (o.t == 'p' || o.t == 'd')
	{
		n = min_v(o.rot, o.o);
		if (o.t == 'd' && scal_v(normed(n), r.dir) > 0)
			n = mult_v(-1, n);
	}
	else if (o.t == 't')
		n = triangle_normal(o, r);
	else if (o.t == 'q')
		n = square_normal(o, r);
	else if (o.t == 's')
		n = min_v(p, o.o);
	else if (o.t == 'c')
		n = cylinder_normal(o, p, r, t);
	else if (o.t == 'o')
		n = cone_normal(o, p, r, t);
	if (o.effect >= 'A' && o.effect <= 'Z')
		n = utd_v(sin(50 * n.x + 100 * p.x), sin(50 * n.y + 100 * p.x), \
			sin(50 * n.z + 100 * p.z));
	n = normed(n);
	return (n);
}
