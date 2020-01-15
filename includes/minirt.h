/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rturcey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 14:48:05 by rturcey           #+#    #+#             */
/*   Updated: 2020/01/15 14:48:06 by rturcey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <mlx.h>
# include <stdio.h>
# include <math.h>
# include <limits.h>
# include <stdlib.h>
# include <time.h>
# include <stdio.h>
# include <pthread.h>
# include "../libft/libft.h"
# include "structures.h"
# include "vectors/vectors.h"
# include "shapes.h"
# include "hook.h"
# include "parsing.h"

void		init_image(t_p *p);
void		free_everything(t_p *p);
void		make_image_lite(t_p *p);
void		make_image(t_p *p);
void		create_threads_lite(t_p *p);
void		create_threads(t_p *p);
void		*aff_objs(void *p);
void		*aff_objs_lite(void *p);
t_color_db	al_objs(t_p *p, t_color_db c, int x, int y);
t_color_db	al_objs_lite(t_p *p, t_color_db c, int x, int y);
t_color_db	get_color(t_object ray, t_p *par, int rebonds);
t_color_db	get_color_lite(t_object ray, t_p *par);
t_color_db	calc_px_intensity(t_object ray, t_p *par, int o_id);
t_color_db	calc_px_intensity_lite(t_object ray, t_p *par, int o_id);
t_vector	px_add(double d, t_p *par, int i, int o_id);
t_vector	px_add_lite(double d, t_p *par, int i, int o_id);
double		interlight(t_object r, t_p *par, double *min, t_object *o);
int			interobj(t_object r, t_p *par, t_object *o);
int			inters(t_object r, t_object o, double *t);
t_vector	get_normal(t_object o, t_vector p, t_object r, double t);
t_color		apply_filter(t_p *p, t_color c1);
void		damier(t_p *par, int o_id);
void		rainbow(t_p *p, int o);
void		apply_effect(t_p *par, int o_id);
t_vector	px_mapping(t_object *s, t_p *p);
t_vector	get_pixel(int x, int y, t_object *p);
t_color		utd_colors(double x, double y, double z);
t_color_db	utd_colors_db(double x, double y, double z);
t_vector	mult_col_vec(t_color_db color, t_vector v);
t_vector	utd_colors_object(double r, double g, double b);
t_color		final_color(t_p *p, t_color_db c2);
t_color_db	add_colors(t_color_db c1, t_color_db c2);
void		final_buffer(t_p *p);
t_color_db	minmax_px(t_p *p, t_vector px);
t_color_db	minmax_px_lite(t_vector px);
void		init_ray(double x, double y, double z, t_vector range);
t_object	spray(t_p *p, double x, double y);

#endif
