/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cones.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rturcey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 14:44:21 by rturcey           #+#    #+#             */
/*   Updated: 2020/01/15 14:44:23 by rturcey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int			intercone(t_object r, t_object co, double *t)
{
	double		q[3];
	double		a[4];
	double		delta;
	t_vector	v[2];

	v[0] = min_v(r.o, co.o);
	v[1] = mult_v(-1, r.dir);
	a[0] = tan(co.rayon * M_PI / 180);
	a[1] = 1 + a[0] * a[0];
	a[2] = scal_v(v[1], co.rot);
	a[3] = scal_v(v[0], co.rot);
	q[0] = scal_v(v[1], v[1]) - (a[1] * a[2] * a[2]);
	q[1] = 2 * (scal_v(v[1], v[0]) - (a[1] * a[2] * a[3]));
	q[2] = scal_v(v[0], v[0]) - (a[1] * a[3] * a[3]);
	delta = q[1] * q[1] - 4 * q[0] * q[2];
	if (delta <= 0)
		return (0);
	a[0] = (q[1] - sqrt(delta)) / (2 * q[0]);
	a[1] = (q[1] + sqrt(delta)) / (2 * q[0]);
	if ((*t = quadracone(r, co, a)) == -1)
	{
		*t = 1E99;
		return (0);
	}
	return (1);
}

double		quadracone(t_object r, t_object co, double *a)
{
	t_vector	v;
	double		s;

	s = 1E99;
	if (a[0] > 0)
	{
		v = add_v(mult_v(a[0], r.dir), min_v(r.o, co.o));
		a[3] = scal_v(v, co.rot);
		if (a[3] <= co.h / 2 && a[3] >= -co.h / 2)
			s = a[0];
	}
	if (a[1] > 0)
	{
		v = add_v(mult_v(a[1], r.dir), min_v(r.o, co.o));
		a[3] = scal_v(v, co.rot);
		if (a[3] <= co.h / 2 && a[3] >= -co.h / 2 && a[1] < s)
			s = a[1];
	}
	if (s < 1E99)
		return (s);
	return (-1);
}

t_vector	cone_normal(t_object o, t_vector p, t_object r, double t)
{
	t_vector	n;
	double		temp;

	temp = scal_v(r.dir, o.rot) * t + scal_v(min_v(r.o, o.o), o.rot);
	n = min_v(min_v(p, o.o), mult_v(temp, mult_v((1 + \
		pow(tan(o.rayon * M_PI / 180), 2)), o.rot)));
	return (n);
}
