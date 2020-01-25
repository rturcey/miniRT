/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rturcey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 14:45:51 by rturcey           #+#    #+#             */
/*   Updated: 2020/01/15 14:45:52 by rturcey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_object	spray(t_p *p, double x, double y)
{
	p->ray.dir.x = x - p->w / 2;
	p->ray.dir.y = y - p->h / 2;
	p->ray.dir.z = -p->w / (2 * tan(p->fov / 2));
	return (p->ray);
}

void		pixelise_lite(t_p *p, int x, int y)
{
	if ((p->h - y) * p->w + x < p->w * p->h)
		p->bf[(p->h - y) * p->w + x] = p->bf[(p->h - y - 1) * p->w + x];
	if ((p->h - y + 1) * p->w + x < p->w * p->h)
		p->bf[(p->h - y + 1) * p->w + x] = p->bf[(p->h - y - 1) * p->w + x];
	if ((p->h - y + 2) * p->w + x < p->w * p->h)
		p->bf[(p->h - y + 2) * p->w + x] = p->bf[(p->h - y - 1) * p->w + x];
}

void		free_everything(t_p *p)
{
	int i;

	i = -1;
	while (++i < p->nobjs)
		if (p->o[i].uvmap)
		{
			mlx_destroy_image(p->mlx_p, p->o[i].uvmap->ptr);
			free_ret(p->o[i].uvmap, 0);
		}
	if (p->nobjs > 0)
		free(p->o);
	if (p->nbcams > 0)
		free(p->r);
	if (p->nblights > 0)
		free(p->l);
	if (p->mlx_i)
		mlx_destroy_image(p->mlx_p, p->mlx_i);
	if (p->mlx_w)
		mlx_destroy_window(p->mlx_p, p->mlx_w);
	if (p->mlx_p)
		free_ret(p->mlx_p, 0);
	if (p->filename)
		free_ret(p->filename, 0);
	free(p);
	exit(0);
}

t_p			*p_copy(t_p *p)
{
	t_p	*n;

	if (!(n = malloc(sizeof(t_p))))
		return (n);
	ft_memcpy(n, p, sizeof(t_p));
	return (n);
}
