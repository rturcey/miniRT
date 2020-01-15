/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basics.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rturcey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 14:43:52 by rturcey           #+#    #+#             */
/*   Updated: 2020/01/15 14:44:01 by rturcey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int			intersphere(t_object r, t_object s, double *t)
{
	double	a;
	double	b;
	double	c;
	double	delta;
	double	t2[2];

	a = scal_v(r.dir, r.dir);
	b = 2 * scal_v(r.dir, min_v(r.o, s.o));
	c = norm_v(min_v(r.o, s.o)) - (s.rayon * s.rayon);
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

int			interplane(t_object r, t_object pl, double *t)
{
	double		scal;
	double		d;

	scal = scal_v(min_v(r.o, pl.o), pl.rot);
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

int			intertriangle(t_object r, t_object tr, double *t)
{
	double		d[3];
	t_vector	v[5];

	v[0] = min_v(tr.s1, tr.o);
	v[1] = min_v(tr.s2, tr.o);
	v[2] = cross_v(r.dir, v[1]);
	d[0] = scal_v(v[0], v[2]);
	if (d[0] == 0)
		return (0);
	d[0] = 1 / d[0];
	v[3] = min_v(r.o, tr.o);
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

t_vector	triangle_normal(t_object o, t_object r)
{
	t_vector	n;

	n = cross_v(min_v(o.s1, o.o), min_v(o.s2, o.o));
	if (scal_v(normed(n), r.dir) > 0)
		n = cross_v(min_v(o.s2, o.o), min_v(o.s1, o.o));
	return (n);
}
