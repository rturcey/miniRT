#include "minirt.h"

t_vector	px_add_lite(double d, t_p *par, int i, int o_id)
{
	t_vector	a;
	t_vector	b;
	t_vector	c;

	if (par->o[o_id].effect == 'd')
		damier(par, o_id);
	a = mult_col_vec(par->l[i].color, par->o[o_id].col);
	b = mult_v(par->l[i].intensity, a);
	c = min_v(par->l[i].origin, par->p);
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
	if (par->o[o_id].effect)
		apply_effect(par, o_id);
	px = mult_v(g_amb, div_v(2, add_v(par->o[o_id].col, par->ambient)));
	while (i < g_nblights)
	{
		ray.dir = normed(min_v(par->l[i].origin, par->p));
		ray.origin = add_v(par->p, mult_v(0.0001, ray.dir));
		d_light2 = norm_v(min_v(par->l[i].origin, par->p));
		px = add_v(px, px_add(d_light2, par, i, o_id));
		i++;
	}
	return (minmax_px_lite(px));
}

t_color_db	get_color_lite(t_object ray, t_p *par)
{
	int			o_id;
	double		has_inter;

	has_inter = interobj(ray, par->o, &par->p, &par->n);
	par->color = utd_colors_db(0, 0, 0);
	if (has_inter != 0)
	{
		o_id = has_inter - 1;
		return (calc_px_intensity_lite(ray, par, o_id));
	}
	return (par->color);
}

t_color_db	al_objs_lite(void *p, t_color_db c, int x, int y)
{
	((t_p *)p)->ray = spray(((t_p *)p), x, y);
	((t_p *)p)->ray.dir = normed(rot_xyz(((t_p *)p)->ray.dir, \
		((t_p *)p)->ray.rot));
	c = add_colors(c, get_color_lite(((t_p *)p)->ray, ((t_p *)p)));
	return (c);
}

void		*aff_objs_lite(void *p)
{
	int			x;
	int			y;
	t_color_db	color;

	y = 0;
	((t_p *)p)->fov = ((t_p *)p)->fov * M_PI / 180;
	while (y < g_h)
	{
		x = ((t_p *)p)->x;
		while (x < g_w)
		{
			color = utd_colors_db(0, 0, 0);
			g_buffer[(g_h - y - 1) * g_w + x] = al_objs_lite(p, color, x, y);
			if ((g_h - y) * g_w + x < g_w * g_h)
				g_buffer[(g_h - y) * g_w + x] = \
			g_buffer[(g_h - y - 1) * g_w + x];
			x += 8;
		}
		y += 2;
	}
	pthread_exit(NULL);
	return (p);
}
