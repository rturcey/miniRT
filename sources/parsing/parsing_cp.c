/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_cp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rturcey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 14:46:53 by rturcey           #+#    #+#             */
/*   Updated: 2020/01/15 14:46:55 by rturcey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int		parse_cp(char *buff, t_object *obj, char t, t_p *p)
{
	if (t == 'c' && parse_cylinder(buff, obj, p) == -1)
		return (-1);
	else if (t == 'p' && parse_pyramid(buff, obj, p) == -1)
		return (-1);
	else if (t == 'q' && parse_cube(buff, obj, p) == -1)
		return (-1);
	return (0);
}

void	create_cylinder(t_object *obj, t_p *p)
{
	p->o[p->ct + 1] = *obj;
	p->o[p->ct + 1].o = mult_v(obj->h / 2, obj->rot);
	p->o[p->ct + 1].o = min_v(obj->o, p->o[p->ct + 1].o);
	p->o[p->ct + 1].cp = 1;
	p->o[p->ct + 1].t = 'd';
	p->o[p->ct + 2] = *obj;
	p->o[p->ct + 2].o = mult_v(obj->h / 2, obj->rot);
	p->o[p->ct + 2].o = add_v(obj->o, p->o[p->ct + 2].o);
	p->o[p->ct + 2].cp = 1;
	p->o[p->ct + 2].t = 'd';
}

int		parse_cylinder(char *buff, t_object *obj, t_p *p)
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
	obj->t = 'c';
	if (parse_textures(&buff[i], obj, p) == -1)
		return (-1);
	create_cylinder(obj, p);
	obj->cp = -1;
	return (0);
}

int		parse_pyramid(char *buff, t_object *obj, t_p *p)
{
	int			i;
	t_vector	v;

	i = 2;
	if (parse_vector(buff, &v, &i) == -1)
		return (-1);
	obj->o = v;
	obj->ctr = v;
	if (parse_vecrot(buff, &v, &i) == -1)
		return (-1);
	obj->rot = v;
	if ((obj->rayon = ft_atod(buff, &i, 1)) == 1E99)
		return (-1);
	if ((obj->h = ft_atod(buff, &i, 1)) < 0 || obj->h == 1E99)
		return (-1);
	if (parse_color(buff, &v, &i) == -1)
		return (-1);
	obj->col = utd_v(v.z, v.y, v.x);
	obj->t = 'q';
	if (parse_textures(&buff[i], obj, p) == -1)
		return (-1);
	create_pyramid(obj, p);
	obj->cp = -3;
	return (0);
}

int		parse_cube(char *buff, t_object *obj, t_p *p)
{
	int			i;
	t_vector	v;

	i = 2;
	if (parse_vector(buff, &v, &i) == -1)
		return (-1);
	obj->o = v;
	obj->ctr = v;
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
	create_cube(obj, p);
	obj->cp = -2;
	return (0);
}
