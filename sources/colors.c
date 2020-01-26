/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rturcey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 14:44:07 by rturcey           #+#    #+#             */
/*   Updated: 2020/01/15 14:44:09 by rturcey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_color_db	utd_colors_db(double x, double y, double z)
{
	t_color_db		color;

	color.red = z;
	color.green = y;
	color.blue = x;
	color.alpha = 0;
	return (color);
}

t_vector	mult_col_vec(t_color_db c, t_vector v)
{
	v.x *= c.red;
	v.y *= c.green;
	v.z *= c.blue;
	return (v);
}

t_vector	utd_colors_object(double r, double g, double b)
{
	t_vector	col;

	col.x = b;
	col.y = g;
	col.z = r;
	return (col);
}

t_color_db	add_colors(t_color_db c1, t_color_db c2)
{
	c1.red += c2.red;
	c1.green += c2.green;
	c1.blue += c2.blue;
	return (c1);
}

t_color		final_color(t_p *p, t_color_db c2)
{
	t_color	c1;

	c1.red = fmax(0, fmin(255, c2.red));
	c1.green = fmax(0, fmin(255, c2.green));
	c1.blue = fmax(0, fmin(255, c2.blue));
	c1.alpha = 0;
	return (apply_filter(p, c1));
}
