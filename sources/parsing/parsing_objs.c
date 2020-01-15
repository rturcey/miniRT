/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_objs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rturcey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 14:47:18 by rturcey           #+#    #+#             */
/*   Updated: 2020/01/15 14:47:19 by rturcey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int		ct_objects(char **buff)
{
	int		k;
	int		i;

	k = 0;
	i = 0;
	while (buff[k])
	{
		if (ft_strnstr(buff[k], "sp ", 3) || ft_strnstr(buff[k], "pl ", 3) || \
			ft_strnstr(buff[k], "sq ", 3) || ft_strnstr(buff[k], "tr ", 3) || \
			ft_strnstr(buff[k], "co ", 3))
			i++;
		else if (ft_strnstr(buff[k], "cy ", 3))
			i += 3;
		else if (ft_strnstr(buff[k], "py ", 3))
			i += 5;
		else if (ft_strnstr(buff[k], "cu ", 3))
			i += 6;
		k++;
	}
	return (i);
}

int		is_simple(char *buff, t_object *obj)
{
	if (ft_strnstr(buff, "sp ", 3) || ft_strnstr(buff, "pl ", 3) || \
		ft_strnstr(buff, "sq ", 3) || ft_strnstr(buff, "tr ", 3) || \
		ft_strnstr(buff, "co ", 3))
	{
		obj->cp = -1;
		return (1);
	}
	return (0);
}

void	init_obj(t_object **o, int n)
{
	int		i;

	i = 0;
	while (i < n)
	{
		(*o)[i].rainbow = 0;
		(*o)[i].ch = 0;
		(*o)[i].effect = '\0';
		(*o)[i].t = '\0';
		(*o)[i].uvmap = NULL;
		(*o)[i].cp = -1;
		(*o)[i].rayon = 0;
		(*o)[i].h = 0;
		(*o)[i].dist = 0;
		(*o)[i].intensity = 0;
		(*o)[i].rb = -1;
		i++;
	}
}

int		parse_objects(char **buff, t_object **obj, t_p *p)
{
	int		k;
	int		i;
	int		r;

	k = -1;
	i = 0;
	p->nobjs = ct_objects(buff);
	if (!(*obj = malloc(p->nobjs * sizeof(t_object))))
		return (error_msg(4, -1));
	init_obj(obj, p->nobjs);
	while (buff[++k] && i < p->nobjs)
	{
		if (is_simple(buff[k], &(*obj)[i]) && (p->ct = i) > -1 && ++i)
			r = parse_simple(buff[k], &(*obj)[i - 1], buff[k][1], p);
		if (ft_strnstr(buff[k], "cy ", 3) && (p->ct = i) > -1 && (i += 3))
			r = parse_cp(buff[k], &(*obj)[i - 3], 'c', p);
		if (ft_strnstr(buff[k], "py ", 3) && (p->ct = i) > -1 && (i += 5))
			r = parse_cp(buff[k], &(*obj)[i - 5], 'p', p);
		if (ft_strnstr(buff[k], "cu ", 3) && (p->ct = i) > -1 && (i += 6))
			r = parse_cp(buff[k], &(*obj)[i - 6], 'q', p);
		if (r == -1 && free_ret(*obj, 1))
			return (error_msg(17, k + 1));
	}
	p->ct = 0;
	return (0);
}

int		parse_simple(char *buff, t_object *obj, char t, t_p *p)
{
	if (t == 'p' && parse_sphere(buff, obj, p) == -1)
		return (-1);
	else if (t == 'l' && parse_plane(buff, obj, p) == -1)
		return (-1);
	else if (t == 'q' && parse_square(buff, obj, p) == -1)
		return (-1);
	else if (t == 'r' && parse_triangle(buff, obj, p) == -1)
		return (-1);
	else if (t == 'o' && parse_cone(buff, obj, p) == -1)
		return (-1);
	return (0);
}
