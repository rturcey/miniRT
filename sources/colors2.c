/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rturcey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 14:44:14 by rturcey           #+#    #+#             */
/*   Updated: 2020/01/15 14:44:16 by rturcey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void		final_bf(t_p *p)
{
	int	i;

	i = 0;
	while (i < p->w * p->h)
	{
		p->endbf[i] = final_color(p, p->bf[i]);
		p->endbf[i].alpha = 0;
		i++;
	}
	free(p->bf);
}

t_color_db	minmax_px(t_p *p, t_vector px)
{
	t_color_db	c;

	c.red = fmax(0, fmin(255, px.z)) / p->aa;
	c.green = fmax(0, fmin(255, px.y)) / p->aa;
	c.blue = fmax(0, fmin(255, px.x)) / p->aa;
	return (c);
}

t_color_db	minmax_px_lite(t_vector px)
{
	t_color_db	c;

	c.red = fmax(0, fmin(255, px.z));
	c.green = fmax(0, fmin(255, px.y));
	c.blue = fmax(0, fmin(255, px.x));
	return (c);
}

t_color		utd_colors(double x, double y, double z)
{
	t_color	color;

	color.red = z;
	color.green = y;
	color.blue = x;
	color.alpha = 0;
	return (color);
}
