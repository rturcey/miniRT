#include "minirt.h"

int 	count_objects(char **buff)
{
	int 	k;
	int 	i;

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

int 	is_simple(char *buff, t_object *obj)
{
	if ((ft_strnstr(buff[k], "sp ", 3) || ft_strnstr(buff[k], "pl ", 3) || \
		ft_strnstr(buff[k], "sq ", 3) || ft_strnstr(buff[k], "tr ", 3) || \
		ft_strnstr(buff[k], "co ", 3)) && (p->count = i) > -1)
	{
		obj->composed = -1;
		return (1);
	}
	return (0);
}

int		parse_objects(char **buff, t_object *obj, t_p *p)
{
	int 	k;
	int 	i;
	int 	r;

	k = 0;
	i = 0;
	r = 0;
	p->nobjs = count_objects(buff)
	if (!(obj = malloc(p->nobjs * sizeof(t_object))))
		return (error_msg(4, -1));
	while (buff[k] && p->nobjs)
	{
		if (is_simple(buff[k], obj) && (p->count = i) > -1 && ++i)
			r = parse_simple(buff[k], &obj[i], buff[k][1], p);
		else if (ft_strnstr(buff[k], "cy ", 3) && (p->count = i) > -1 && (i += 3))
			r = parse_composed(buff[k], obj[i], 'c', p);
		else if (ft_strnstr(buff[k], "py ", 3) && (p->count = i) > -1 && (i += 5))
			r = parse_composed(buff[k], obj[i], 'p', p);
		else if (ft_strnstr(buff[k], "cu ", 3) && (p->count = i) > -1 && (i += 6))
			r = parse_composed(buff[k], obj[i], 'q', p);
		if (r == -1)
		{
			free(obj);
			return (error_msg(17, k + 1));
		}
		k++;
	}
	p->count = 0;
	return (0);
}

int 	parse_simple(char *buff, t_object *obj, char type, t_p *p)
{
	if (type == 'p' && parse_sphere(buff, obj, p) == -1)
		return (-1);
	else if (type == 'l' && parse_plane(buff, obj, p) == -1)
		return (-1);
	else if (type == 'q' && parse_square(buff, obj, p) == -1)
		return (-1);
	else if (type == 'r' && parse_triangle(buff, obj, p) == -1)
		return (-1);
	else if (type == 'o' && parse_cone(buff, obj, p) == -1)
		return (-1);
	return (0);
}

int 	parse_composed(char *buff, t_object *obj, char type, t_p *p)
{
	if (type == 'c' && parse_cylinder(buff, obj, p) == -1)
		return (-1);
	else if (type == 'p' && parse_pyramid(buff, obj, p) == -1)
		return (-1);
	else if (type == 'q' && parse_cube(buff, obj, p) == -1)
		return (-1);
	return (0);
}