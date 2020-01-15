/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rturcey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 14:45:14 by rturcey           #+#    #+#             */
/*   Updated: 2020/01/15 14:45:16 by rturcey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	create_threads(t_p *p)
{
	pthread_t	threads[8];
	t_p			*pr[8];
	int			i;

	i = -1;
	while (++i < p->threads)
		pr[i] = p_copy(p);
	i = 0;
	write(1, "[", 1);
	while (i < p->threads)
	{
		pr[i]->x = i;
		pthread_create(&threads[i], NULL, aff_objs, pr[i]);
		i++;
	}
	while (i--)
	{
		pthread_join(threads[i], NULL);
		free(pr[i]);
	}
	ft_putstr_fd("]\nImage generated !\n", 1);
}

void	create_threads_lite(t_p *p)
{
	pthread_t	threads[8];
	t_p			*pr[8];
	int			i;

	i = -1;
	while (++i < p->threads)
		pr[i] = p_copy(p);
	i = 0;
	while (i < p->threads)
	{
		pr[i]->x = i;
		pthread_create(&threads[i], NULL, aff_objs_lite, pr[i]);
		i++;
	}
	while (i--)
	{
		pthread_join(threads[i], NULL);
		free(pr[i]);
	}
}

void	make_image(t_p *p)
{
	int		b;

	if (p->curr->t == 'r' && p->ct < p->nbcams)
		p->ray = *p->curr;
	p->fov = p->ray.fov;
	if (!(p->mlx_i = mlx_new_image(p->mlx_p, p->w, p->h)))
		return ;
	if (!(p->endbf = (t_color *)mlx_get_data_addr(p->mlx_i, &b, &b, &b)))
		return ;
	if (!(p->bf = malloc(p->w * p->h * sizeof(t_color_db))))
		return ;
	create_threads(p);
	final_bf(p);
}

void	make_image_lite(t_p *p)
{
	int		b;

	p->w /= 2;
	p->h /= 2;
	if (p->curr->t == 'r' && p->ct < p->nbcams)
		p->ray = *p->curr;
	p->fov = p->ray.fov;
	if (!(p->mlx_i = mlx_new_image(p->mlx_p, p->w, p->h)))
		return ;
	if (!(p->endbf = (t_color *)mlx_get_data_addr(p->mlx_i, &b, &b, &b)))
		return ;
	if (!(p->bf = malloc(p->w * p->h * sizeof(t_color_db))))
		return ;
	create_threads_lite(p);
	final_bf(p);
	p->w *= 2;
	p->h *= 2;
	mlx_put_image_to_window(p->mlx_p, p->mlx_w, p->mlx_i, 0, 0);
	mlx_key_hook(p->mlx_w, key_hook, p);
	mlx_mouse_hook(p->mlx_w, mouse_hook, p);
	mlx_hook(p->mlx_w, 6, (1L << 6), motion_hook, p);
	mlx_hook(p->mlx_w, 17, 0L, motion_close, p);
	mlx_loop(p->mlx_p);
}

void	init_image(t_p *p)
{
	if (!(p->mlx_w = mlx_new_window(p->mlx_p, p->w, p->h, "MiniRT")))
		return ;
	p->fov = p->r[0].fov;
	p->curr = &p->r[0];
	p->ct = 0;
	make_image(p);
	if (p->save != 's')
	{
		mlx_put_image_to_window(p->mlx_p, p->mlx_w, p->mlx_i, 0, 0);
		mlx_key_hook(p->mlx_w, key_hook, p);
		mlx_mouse_hook(p->mlx_w, mouse_hook, p);
		mlx_hook(p->mlx_w, 6, (1L << 6), motion_hook, p);
		mlx_hook(p->mlx_w, 17, 0L, motion_close, p);
		mlx_loop(p->mlx_p);
	}
	else
		free_everything(p);
	return ;
}
