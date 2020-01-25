/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rturcey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 14:47:36 by rturcey           #+#    #+#             */
/*   Updated: 2020/01/15 14:47:38 by rturcey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	init_p(t_p **p)
{
	if (!((*p) = malloc(sizeof(t_p))))
		return ;
	(*p)->w = 0;
	(*p)->h = 0;
	(*p)->nbcams = 0;
	(*p)->nblights = 0;
	(*p)->nobjs = 0;
	(*p)->ct = 0;
	(*p)->fov = 0;
	(*p)->x = 0;
	(*p)->amb_int = 0;
	(*p)->aa = 1;
	(*p)->filter = '\0';
	(*p)->mlx_p = NULL;
	(*p)->mlx_i = NULL;
	(*p)->mlx_w = NULL;
	(*p)->filename = NULL;
	(*p)->threads = 8;
	(*p)->aarainb = 1;
	(*p)->mouse = -1;
	(*p)->ray.o = utd_v(0, 0, 0);
	(*p)->ray.dir = utd_v(0, 0, 0);
	(*p)->save = '\0';
}
