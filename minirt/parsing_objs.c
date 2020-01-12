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

int		parse_objects(char **buff, t_object *obj, t_p *p)
{
	int 	k;
	int 	i;
	int 	r;

	k = 0;
	i = 0;
	r = 0;
	if ((p->nobjs = count_objects(buff)) == 0)
		return (0);
	if (!(obj = malloc(p->nobjs * sizeof(t_object))))
		return (error_msg(4, -1));
	while (buff[k])
	{
		if ((ft_strnstr(buff[k], "sp ", 3) || ft_strnstr(buff[k], "pl ", 3) || \
			ft_strnstr(buff[k], "sq ", 3) || ft_strnstr(buff[k], "tr ", 3) || \
			ft_strnstr(buff[k], "co ", 3)))
		{
			r = parse_simple(buff[k], &obj[i], buff[k][1], p);
			i++;
		}
		/*else if (ft_strnstr(buff[k], "cy ", 3))
		{
			r = parse_composed(buff[k], obj[i], 'c');
			i += 3;
		}
		else if (ft_strnstr(buff[k], "py ", 3))
		{
			r = parse_composed(buff[k], obj[i], 'p');
			i += 5;
		}
		else if (ft_strnstr(buff[k], "cu ", 3))
		{
			r = parse_composed(buff[k], obj[i], 'q');
			i += 6;
		}*/
		if (r == -1 && free_ret(obj, 1))
			return (error_msg(17, k + 1));
		k++;
	}
	return (0);

}

int 	parse_cone(char *buff, t_object *obj, t_p *p)
{
	int 		i;
	t_vector	v;

	i = 2;
	if (parse_vector(buff, &v, &i) == -1)
		return (-1);
	obj->origin = v;
	if (parse_vecrot(buff, &v, &i) == -1)
		return (-1);
	obj->rot = v;
	if ((obj->h = ft_atod(buff, &i)) < 0 || obj->rayon == 1E99)
		return (-1);
	if ((obj->rayon = ft_atod(buff, &i)) < 0 || obj->rayon == 1E99)
		return (-1);
	if (parse_color(buff, &v, &i) == -1)
		return (-1);
	obj->col = utd_v(v.z, v.y, v.x);
	while (ft_isdigit(buff[i]) || buff[i] == ',')
		i++;
	obj->type = 'o';
	if (parse_textures(&buff[i], obj, p) == -1)
		return (-1);
	return (0);
}

int 	parse_triangle(char *buff, t_object *obj, t_p *p)
{
	int 		i;
	t_vector	v;

	i = 2;
	if (parse_vector(buff, &v, &i) == -1)
		return (-1);
	obj->origin = v;
	if (parse_vector(buff, &v, &i) == -1)
		return (-1);
	obj->s1 = v;
	if (parse_vector(buff, &v, &i) == -1)
		return (-1);
	obj->s2 = v;
	if (parse_color(buff, &v, &i) == -1)
		return (-1);
	obj->col = utd_v(v.z, v.y, v.x);
	while (ft_isdigit(buff[i]) || buff[i] == ',')
		i++;
	obj->type = 't';
	if (parse_textures(&buff[i], obj, p) == -1)
		return (-1);
	return (0);
}

void	create_square(char *buff, t_object *obj)
{
	obj->origin1 = add_v(obj->origin, rot_xyz(utd_v(-obj->h / 2, 0, obj->h / 2), obj->rot));
	obj->origin2 = add_v(obj->origin, rot_xyz(utd_v(obj->h / 2, 0, -obj->h / 2), obj->rot));
	obj->s1 = add_v(obj->origin, rot_xyz(utd_v(obj->h / 2, 0, obj->h / 2), obj->rot));
	obj->s2 = add_v(obj->origin, rot_xyz(utd_v(-obj->h / 2, 0, -obj->h / 2), obj->rot));
}

int 	parse_square(char *buff, t_object *obj, t_p *p)
{
	int 		i;
	t_vector	v;

	i = 2;
	if (parse_vector(buff, &v, &i) == -1)
		return (-1);
	obj->origin = v;
	if (parse_vecrot(buff, &v, &i) == -1)
		return (-1);
	obj->rot = v;
	if ((obj->h = ft_atod(buff, &i)) < 0 || obj->rayon == 1E99)
		return (-1);
	if (parse_color(buff, &v, &i) == -1)
		return (-1);
	obj->col = utd_v(v.z, v.y, v.x);
	while (ft_isdigit(buff[i]) || buff[i] == ',')
		i++;
	obj->type = 'q';
	if (parse_textures(&buff[i], obj, p) == -1)
		return (-1);
	create_square(buff, obj);
	return (0);
}

int 	parse_plane(char *buff, t_object *obj, t_p *p)
{
	int 		i;
	t_vector	v;

	i = 2;
	if (parse_vector(buff, &v, &i) == -1)
		return (-1);
	obj->origin = v;
	if (parse_vecrot(buff, &v, &i) == -1)
		return (-1);
	obj->rot = v;
	if (parse_color(buff, &v, &i) == -1)
		return (-1);
	obj->col = utd_v(v.z, v.y, v.x);
	while (ft_isdigit(buff[i]) || buff[i] == ',')
		i++;
	obj->type = 'p';
	if (parse_textures(&buff[i], obj, p) == -1)
		return (-1);
	return (0);
}

int 	parse_sphere(char *buff, t_object *obj, t_p *p)
{
	int 		i;
	t_vector	v;

	i = 2;
	if (parse_vector(buff, &v, &i) == -1)
		return (-1);
	obj->origin = v;
	if ((obj->rayon = ft_atod(buff, &i)) < 0 || obj->rayon == 1E99)
		return (-1);
	if (parse_color(buff, &v, &i) == -1)
		return (-1);
	obj->col = utd_v(v.z, v.y, v.x);
	while (ft_isdigit(buff[i]) || buff[i] == ',')
		i++;
	obj->type = 's';
	if (parse_textures(&buff[i], obj, p) == -1)
		return (-1);
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
	if (type == 'r' && parse_triangle(buff, obj, p) == -1)
		return (-1);
	if (type == 'o' && parse_cone(buff, obj, p) == -1)
		return (-1);
	return (0);
}