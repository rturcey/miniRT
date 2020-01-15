/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt_lite.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rturcey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 14:45:33 by rturcey           #+#    #+#             */
/*   Updated: 2020/01/15 14:45:34 by rturcey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vector	px_add_lite(double d, t_p *par, int i, int o_id)
{
	t_vector	a;
	t_vector	b;
	t_vector	c;

	a = mult_col_vec(par->l[i].color, par->o[o_id].col);
	b = mult_v(par->l[i].intensity, a);
	c = min_v(par->l[i].o, par->p);
	c = normed(c);
	a = mult_v(scal_v(c, par->n), b);
	return (div_v(d, a));
}

t_color_db	calc_px_intensity_lite(t_object ray, t_p *par, int o_id)
{
	t_vector	px;
	int			i;
	double		d_light2;

	i = 0;
	px = mult_v(par->amb_int, div_v(2, add_v(par->o[o_id].col, par->ambient)));
	while (i < par->nblights)
	{
		ray.dir = normed(min_v(par->l[i].o, par->p));
		ray.o = add_v(par->p, mult_v(0.0001, ray.dir));
		d_light2 = norm_v(min_v(par->l[i].o, par->p));
		px = add_v(px, px_add_lite(d_light2, par, i, o_id));
		i++;
	}
	return (minmax_px_lite(px));
}

t_color_db	get_color_lite(t_object ray, t_p *par)
{
	int			o_id;
	double		has_inter;

	has_inter = interobj(ray, par, par->o);
	par->color = utd_colors_db(0, 0, 0);
	if (has_inter != 0)
	{
		o_id = has_inter - 1;
		return (calc_px_intensity_lite(ray, par, o_id));
	}
	return (par->color);
}

t_color_db	al_objs_lite(t_p *p, t_color_db c, int x, int y)
{
	p->ray = spray(p, x, y);
	p->ray.dir = normed(rotv(p->ray.dir, \
		p->ray.rot));
	c = add_colors(c, get_color_lite(p->ray, p));
	return (c);
}

void		*aff_objs_lite(void *par)
{
	int			x;
	int			y;
	t_color_db	color;
	t_p			*p;

	p = (t_p *)par;
	y = 0;
	while (y < p->h)
	{
		x = p->x;
		while (x < p->w)
		{
			color = utd_colors_db(0, 0, 0);
			p->bf[(p->h - y - 1) * p->w + x] = al_objs_lite(p, color, x, y);
			pixelise_lite(p, x, y);
			x += p->threads;
		}
		y += 4;
	}
	pthread_exit(NULL);
	return (p);
}
