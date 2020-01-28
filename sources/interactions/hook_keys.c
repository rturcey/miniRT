/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_keys.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rturcey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 14:46:12 by rturcey           #+#    #+#             */
/*   Updated: 2020/01/15 14:46:13 by rturcey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int		key_effects(int k, t_p *p)
{
	if (k >= 83 && k <= 88)
		p->aa = pow(k - 82, 2);
	if (k == 15)
		p->filter = (p->filter == 'r') ? '\0' : 'r';
	else if (k == 5)
		p->filter = (p->filter == 'g') ? '\0' : 'g';
	else if (k == 11)
		p->filter = (p->filter == 'b') ? '\0' : 'b';
	else if (k == 45)
		p->filter = (p->filter == 'n') ? '\0' : 'n';
	else if (k == 35)
		p->filter = (p->filter == 'p') ? '\0' : 'p';
	else if (k == 116 && p->amb_int > -1)
		p->amb_int = fmin(1, p->amb_int + 0.05);
	else if (k == 121 && p->amb_int > -1)
		p->amb_int = fmax(0, p->amb_int - 0.05);
	return (k);
}

int		key_ct(int k, t_p *p)
{
	if (k == 24)
		p->ct++;
	else if (k == 27 && p->ct > 0)
		p->ct--;
	else if (k == 8)
	{
		if (p->ct >= p->nbcams)
			p->ct = 0;
		p->curr = &p->r[p->ct];
	}
	else if (k == 37)
	{
		if (p->ct >= p->nblights)
			p->ct = 0;
		p->curr = &p->l[p->ct];
	}
	else if (k == 31)
	{
		while (p->ct < p->nobjs && p->o[p->ct].cp > -1)
			p->ct++;
		if (p->ct >= p->nobjs)
			p->ct = 0;
		p->curr = &p->o[p->ct];
	}
	return (k);
}

int		key_normal(int k, void *param)
{
	t_p	*p;

	p = ((t_p *)param);
	if (k == 49 || (k >= 83 && k <= 88))
	{
		mlx_destroy_image(p->mlx_p, p->mlx_i);
		p->mlx_i = NULL;
		mlx_clear_window(p->mlx_p, p->mlx_w);
		make_image(p);
		mlx_put_image_to_window(p->mlx_p, p->mlx_w, p->mlx_i, 0, 0);
		return (-1);
	}
	return (k);
}

int		key_hook(int k, void *param)
{
	t_p	*p;

	p = ((t_p *)param);
	if (k == 53)
		free_everything(p);
	key_ct(k, p);
	key_rotation(k, p);
	key_rotation_bis(k, p);
	key_attribute(k, p);
	key_translation(k, p);
	key_effects(k, p);
	if (k == 82)
	{
		if (p->threads != 1)
			p->threads = 1;
		else
			p->threads = 8;
	}
	if (key_normal(k, p) == -1)
		return (k);
	mlx_destroy_image(p->mlx_p, p->mlx_i);
	p->mlx_i = NULL;
	make_image_lite(p);
	return (k);
}
