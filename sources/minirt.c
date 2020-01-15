/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rturcey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 14:45:28 by rturcey           #+#    #+#             */
/*   Updated: 2020/01/15 14:45:29 by rturcey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vector	px_add(double d, t_p *par, int i, int o_id)
{
	t_vector	a;
	t_vector	b;
	t_vector	c;

	if (par->o[o_id].effect == 'd')
		damier(par, o_id);
	a = mult_col_vec(par->l[i].color, par->o[o_id].col);
	b = mult_v(par->l[i].intensity, a);
	c = min_v(par->l[i].o, par->p);
	c = normed(c);
	a = mult_v(scal_v(c, par->n), b);
	return (div_v(d, a));
}

t_color_db	calc_px_intensity(t_object ray, t_p *par, int o_id)
{
	t_vector	px;
	double		has_inter_light;
	int			i;
	double		d_light;
	double		d_light2;

	i = 0;
	if (par->o[o_id].effect)
		apply_effect(par, o_id);
	px = mult_v(par->amb_int, div_v(2, add_v(par->o[o_id].col, par->ambient)));
	while (i < par->nblights)
	{
		ray.dir = normed(min_v(par->l[i].o, par->p));
		ray.o = add_v(par->p, mult_v(0.0001, ray.dir));
		has_inter_light = interlight(ray, par, &d_light, par->o);
		d_light2 = norm_v(min_v(par->l[i].o, par->p));
		d_light *= d_light;
		if (!(has_inter_light == 1 && d_light < d_light2))
			px = add_v(px, px_add(d_light2, par, i, o_id));
		i++;
	}
	return (minmax_px(par, px));
}

t_color_db	get_color(t_object ray, t_p *par, int rebonds)
{
	int			o_id;
	double		has_inter;

	has_inter = interobj(ray, par, par->o);
	par->color = utd_colors_db(0, 0, 0);
	if (rebonds == 0)
		return (par->color);
	if (has_inter != 0)
	{
		o_id = has_inter - 1;
		if (par->o[o_id].effect == 'm' || par->o[o_id].effect == 'M')
		{
			par->ray_m.dir = min_v(ray.dir, mult_v(2 * \
			scal_v(par->n, ray.dir), par->n));
			par->ray_m.o = add_v(par->p, mult_v(0.0001, par->n));
			par->color = get_color(par->ray_m, par, rebonds - 1);
		}
		else
			return (calc_px_intensity(ray, par, o_id));
	}
	return (par->color);
}

t_color_db	al_objs(t_p *p, t_color_db c, int x, int y)
{
	double			k;
	double			k2;

	k2 = 0;
	while (k2 < 1)
	{
		k = 0;
		while (k < 1)
		{
			p->ray = spray(p, x + k, y + k2);
			p->ray.dir = normed(rotv(p->ray.dir, \
				p->ray.rot));
			c = add_colors(c, get_color(p->ray, p, 100));
			k += sqrt(p->aa) * (1 / p->aa);
		}
		k2 += sqrt(p->aa) * (1 / p->aa);
	}
	return (c);
}

void		*aff_objs(void *par)
{
	int			x;
	int			y;
	t_color_db	color;
	int			ct;
	t_p			*p;

	y = 0;
	p = (t_p *)par;
	ct = 1;
	while (y < p->h)
	{
		if (p->x == 0 && y > (p->h / 10) * ct && (ct++))
			write(1, "*", 1);
		x = p->x;
		while (x < p->w)
		{
			color = utd_colors_db(0, 0, 0);
			p->buffer[(p->h - y - 1) * p->w + x] \
			= al_objs(p, color, x, y);
			x += p->threads;
		}
		y++;
	}
	pthread_exit(NULL);
	return (p);
}
