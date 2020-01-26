/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exportbmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rturcey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 14:44:41 by rturcey           #+#    #+#             */
/*   Updated: 2020/01/15 14:44:42 by rturcey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	init_val(unsigned char *f, unsigned char *i, unsigned char *p)
{
	int		k;

	k = 1;
	f[0] = 'B';
	f[1] = 'M';
	while (++k < 10)
		f[k] = 0;
	f[k] = 54;
	while (++k < 14)
		f[k] = 0;
	k = 0;
	i[0] = 40;
	while (++k < 40)
		i[k] = 0;
	i[12] = 1;
	i[14] = 24;
	i[15] = 0;
	p[0] = 0;
	p[1] = 0;
	p[2] = 0;
}

void	cdata(t_p *p, unsigned char *f, unsigned char *inf, unsigned char *pad)
{
	int				fd;
	unsigned char	*data;
	int				i;

	i = -1;
	fd = open(p->filename, O_CREAT | O_RDWR, 0666);
	write(fd, f, 14);
	write(fd, inf, 40);
	if (!(data = malloc(p->w * p->h * 3 * sizeof(unsigned char))))
		return ;
	while (++i < p->w * p->h)
	{
		data[i * 3] = p->endbf[i].blue;
		data[i * 3 + 1] = p->endbf[i].green;
		data[i * 3 + 2] = p->endbf[i].red;
	}
	i = -1;
	while (++i < p->h)
	{
		write(fd, &data[0] + (p->w * (p->h - i - 1) * 3), 3 * p->w);
		write(fd, pad, (4 - (p->w * 3) % 4) % 4);
	}
	close(fd);
}

void	export_bmp(t_p *p)
{
	unsigned char	file_h[14];
	unsigned char	info_h[40];
	unsigned char	pad[3];
	int				size;

	init_val(file_h, info_h, pad);
	size = 54 + 3 * p->w * p->h;
	file_h[2] = (unsigned char)size;
	file_h[3] = (unsigned char)(size >> 8);
	file_h[4] = (unsigned char)(size >> 16);
	file_h[5] = (unsigned char)(size >> 24);
	info_h[4] = (unsigned char)p->w;
	info_h[5] = (unsigned char)(p->w >> 8);
	info_h[6] = (unsigned char)(p->w >> 16);
	info_h[7] = (unsigned char)(p->w >> 24);
	info_h[8] = (unsigned char)p->h;
	info_h[9] = (unsigned char)(p->h >> 8);
	info_h[10] = (unsigned char)(p->h >> 16);
	info_h[11] = (unsigned char)(p->h >> 24);
	cdata(p, file_h, info_h, pad);
}
