/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_mousemotion.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rturcey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 14:46:18 by rturcey           #+#    #+#             */
/*   Updated: 2020/01/15 14:46:19 by rturcey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	add_range(double *r, double d)
{
	if (*r + d > 1)
		*r = -1;
	else if (*r + d < -1)
		*r = 1;
	else
		*r += d;
}

int		motion_hook(int x, int y, void *param)
{
	t_p		*p;

	p = ((t_p *)param);
	if (p->mouse < 0)
		return (-1);
	if (p->curr->t != 'r')
		p->curr = &p->r[0];
	if (x > p->w / 3 && x < p->w / 2)
		add_range(&p->curr->rot.y, -0.01 * p->mouse);
	else if (x < p->w / 2 / 3)
		add_range(&p->curr->rot.y, 0.01 * p->mouse);
	if (y > p->h / 3 && y < p->h / 2)
		add_range(&p->curr->rot.x, -0.01 * p->mouse);
	else if (y < p->h / 2 / 3)
		add_range(&p->curr->rot.x, 0.01 * p->mouse);
	mlx_destroy_image(p->mlx_p, p->mlx_i);
	p->mlx_i = NULL;
	make_image_lite(p);
	return (0);
}

int		motion_close(void *param)
{
	t_p	*p;

	p = ((t_p *)param);
	free_everything(p);
	return (0);
}

int		mouse_hook(int button, int x, int y, void *param)
{
	t_p		*p;
	int		l;

	l = 0;
	x += x - x;
	y += y - y;
	p = ((t_p *)param);
	if (button == 4 && (l = 1))
		p->r[p->ct].o.z -= 20;
	else if (button == 5 && (l = 1))
		p->r[p->ct].o.z += 20;
	else if (button == 3 && (l = 1))
		p->mouse *= -1;
	else if (button == 1 && p->mouse > 0 && (l = 1))
		p->mouse++;
	else if (button == 2 && p->mouse > 1 && (l = 1))
		p->mouse--;
	if (l == 1)
	{
		mlx_destroy_image(p->mlx_p, p->mlx_i);
		p->mlx_i = NULL;
		make_image_lite(p);
	}
	return (button);
}
