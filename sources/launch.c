/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rturcey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/16 12:23:21 by rturcey           #+#    #+#             */
/*   Updated: 2019/11/16 12:23:23 by rturcey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	create_threads(double fov)
{
	pthread_t	threads[8];
	int 	i;

	i = 0;
	while (i < p->threads)
	{
		pthread_create(&threads[i], NULL, aff_objs, p);
		i++;
	}
	while (i--)
		pthread_join(threads[i], NULL);
}

void	create_threads_lite(t_p *p)
{
	pthread_t	threads[8];
	int 	i;

	i = 0;
	while (i < p->threads)
	{
		pthread_create(&threads[i], NULL, aff_objs_lite, p);
		i++;
	}
	while (i--)
		pthread_join(threads[i], NULL);
}

void	*make_image(t_p *p)
{
	int 		bits;
	t_color		*buffer;

	if (!(p->mlx_i = mlx_new_image(p->mlx_p, size_x, size_y)))
		return ;
	if (!(p->endbuffer = (t_color *)mlx_get_data_addr(p->mlx_i, &bits, &bits, &bits)))
		return ;
	if (!(p->buffer = malloc(p->w * p->h * sizeof(t_color_db))))
		return;
	create_threads(p);
	final_buffer(p);
	return (buffer);
}

void	make_image_lite(t_p *p)
{
	int 		bits;
	t_color		*buffer;

	p->w /= 2;
	p->h /= 2;
	if (!(p->mlx_i = mlx_new_image(p->mlx_p, size_x / 2, size_y / 2)))
		return (NULL);
	if (!(p->endbuffer = (t_color *)mlx_get_data_addr(p->mlx_i, &bits, &bits, &bits)))
		return (NULL);
	if (!(p->buffer = malloc(p->w * p->h * sizeof(t_color_db))))
		return (NULL);
	create_threads_lite(p);
	final_buffer(p);
	p->w *= 2;
	p->h *= 2;
}

void	free_everything(t_p *p)
{
	int i;

	i = -1;
	while (++i < p->nobjs)
		if (p->o[i]->uvmap->img)
		{
			mlx_destroy_image(p->mlx_p, p->o[i]->uvmap->ptr);
			free_ret(p->o[i]->uvmap->img, 0);
		}
	if (p->nobjs > 0)
		free(p->o);
	if (p->nbcams > 0)
		free(p->r);
	if (p->nblights > 0)
		free(p->l);
	free(p->endbuffer, 0);
	if (p->mlx_i)
	{
		mlx_destroy_image(p->mlx_p, p->mlx_i);
		p->mlx_i = NULL;
	}
	if (p->mlx_w)
	{
		mlx_destroy_window(p->mlx_p, p->mlx_w);
		p->mlx_i = NULL;
	}
	if (p->mlx_p)
		free_ret(mlx_p);
	exit(0);
}

void	init_image(t_p *p, int s)
{

	p->mlx_p = mlx_init();
	if(!(p->mlx_w = mlx_new_window(p->mlx_p, p->w, p->h, "MiniRT")))
		return ;
	make_image(p);
	if (s != 's')
	{
		mlx_put_image_to_window(p->mlx_p, p->mlx_w, p->mlx_i, 0, 0);
		mlx_key_hook(p->mlx_w, key_hook, p);
		mlx_mouse_hook(p->mlx_w, mouse_hook, p);
		mlx_hook(p->mlx_w, 6, (1L << 6), motion_hook, p);
		mlx_hook(p->mlx_w, 17, 0L, motion_close, p);
		mlx_loop(p->mlx_p);
	}
	/*else
		save_img(p)*/
	free_everything(p);
	return ;
}
