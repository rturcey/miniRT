/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_simple.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rturcey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 14:47:24 by rturcey           #+#    #+#             */
/*   Updated: 2020/01/15 14:47:25 by rturcey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int		parse_cone(char *buff, t_object *obj, t_p *p)
{
	int			i;
	t_vector	v;

	i = 2;
	if (parse_vector(buff, &v, &i) == -1)
		return (-1);
	obj->o = v;
	if (parse_vecrot(buff, &v, &i) == -1)
		return (-1);
	obj->rot = normed(v);
	if ((obj->rayon = ft_atod(buff, &i, 1)) < 0 || obj->rayon == 1E99)
		return (-1);
	if ((obj->h = ft_atod(buff, &i, 1)) < 0 || obj->h == 1E99)
		return (-1);
	if (parse_color(buff, &v, &i) == -1)
		return (-1);
	obj->col = utd_v(v.z, v.y, v.x);
	obj->t = 'o';
	if (parse_textures(&buff[i], obj, p) == -1)
		return (-1);
	return (0);
}

int		parse_triangle(char *buff, t_object *obj, t_p *p)
{
	int			i;
	t_vector	v;

	i = 2;
	if (parse_vector(buff, &v, &i) == -1)
		return (-1);
	obj->o = v;
	obj->true_o = v;
	if (parse_vector(buff, &v, &i) == -1)
		return (-1);
	obj->s1 = v;
	if (parse_vector(buff, &v, &i) == -1)
		return (-1);
	obj->s2 = v;
	if (parse_color(buff, &v, &i) == -1)
		return (-1);
	obj->col = utd_v(v.z, v.y, v.x);
	obj->t = 't';
	if (parse_textures(&buff[i], obj, p) == -1)
		return (-1);
	return (0);
}

int		parse_square(char *buff, t_object *obj, t_p *p)
{
	int			i;
	t_vector	v;

	i = 2;
	if (parse_vector(buff, &v, &i) == -1)
		return (-1);
	obj->o = v;
	if (parse_vecrot(buff, &v, &i) == -1)
		return (-1);
	obj->rot = v;
	if ((obj->h = ft_atod(buff, &i, 1)) < 0 || obj->h == 1E99)
		return (-1);
	if (parse_color(buff, &v, &i) == -1)
		return (-1);
	obj->col = utd_v(v.z, v.y, v.x);
	obj->t = 'q';
	if (parse_textures(&buff[i], obj, p) == -1)
		return (-1);
	create_square(obj);
	return (0);
}

int		parse_plane(char *buff, t_object *obj, t_p *p)
{
	int			i;
	t_vector	v;

	i = 2;
	if (parse_vector(buff, &v, &i) == -1)
		return (-1);
	obj->o = v;
	if (parse_vecrot(buff, &v, &i) == -1)
		return (-1);
	obj->rot = normed(v);
	if (parse_color(buff, &v, &i) == -1)
		return (-1);
	obj->col = utd_v(v.z, v.y, v.x);
	obj->col1 = obj->col;
	obj->t = 'p';
	if (parse_textures(&buff[i], obj, p) == -1)
		return (-1);
	return (0);
}

int		parse_sphere(char *buff, t_object *obj, t_p *p)
{
	int			i;
	t_vector	v;

	i = 2;
	if (parse_vector(buff, &v, &i) == -1)
		return (-1);
	obj->o = v;
	if ((obj->rayon = ft_atod(buff, &i, 1)) < 0 || obj->rayon == 1E99)
		return (-1);
	if (parse_color(buff, &v, &i) == -1)
		return (-1);
	obj->col = utd_v(v.z, v.y, v.x);
	obj->t = 's';
	if (parse_textures(&buff[i], obj, p) == -1)
		return (-1);
	return (0);
}
