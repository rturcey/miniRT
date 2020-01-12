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

void	go_image(t_p *p)
{
	int 		bits;
	t_color		*buffer;

	if (!(p->mlx_i = mlx_new_image(p->mlx_p, size_x, size_y)))
		return ;
	if (!(buffer = (t_color *)mlx_get_data_addr(p->mlx_i, &bits, &bits, &bits)))
		return ;
	p->buffer = malloc(p->w * p->h * sizeof(t_color_db));
	create_threads(p);
	buffer = final_buffer(p, buffer);
	mlx_put_image_to_window(p->mlx_p, p->mlx_w, p->mlx_i, 0, 0);
}

void	go_image_lite(t_p *p)
{
	int 		bits;
	t_color		*buffer;

	p->w /= 2;
	p->h /= 2;
	if (!(p->buffer = malloc(p->w * p->h * sizeof(t_color_db))))
		return ;
	if (!(p->mlx_i = mlx_new_image(p->mlx_p, size_x / 2, size_y / 2)))
		return ;
	if (!(buffer = (t_color *)mlx_get_data_addr(p->mlx_i, &bits, &bits, &bits)))
		return ;
	create_threads_lite(p);
	buffer = final_buffer(p, buffer);
	p->w *= 2;
	p->h *= 2;
	mlx_put_image_to_window(p->mlx_p, p->mlx_w, p->mlx_i, 0, 0);
}

void	put_img(t_p *p)
{
	p->mlx_p = mlx_init();
	if(!(p->mlx_w = mlx_new_window(p->mlx_p, p->w, p->h, "MiniRT")))
		return ;
	go_image(p);
	mlx_key_hook(p->mlx_w, key_hook, NULL);
	mlx_mouse_hook(p->mlx_w, mouse_hook, NULL);
	mlx_hook(p->mlx_w, 6, (1L << 6), motion_hook, NULL);
	mlx_hook(p->mlx_w, 17, 0L, motion_close, NULL);
	mlx_loop(p->mlx_p);
	return ;
}
