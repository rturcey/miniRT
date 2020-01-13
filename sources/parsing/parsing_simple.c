#include "includes/minirt.h"

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
	if ((obj->rayon = ft_atod(buff, &i)) < 0 || obj->rayon == 1E99)
		return (-1);
	if ((obj->h = ft_atod(buff, &i)) < 0 || obj->h == 1E99)
		return (-1);
	if (parse_color(buff, &v, &i) == -1)
		return (-1);
	obj->col = utd_v(v.z, v.y, v.x);
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
	obj->true_origin = v;
	if (parse_vector(buff, &v, &i) == -1)
		return (-1);
	obj->s1 = v;
	if (parse_vector(buff, &v, &i) == -1)
		return (-1);
	obj->s2 = v;
	if (parse_color(buff, &v, &i) == -1)
		return (-1);
	obj->col = utd_v(v.z, v.y, v.x);
	obj->type = 't';
	if (parse_textures(&buff[i], obj, p) == -1)
		return (-1);
	return (0);
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
	if ((obj->h = ft_atod(buff, &i)) < 0 || obj->h == 1E99)
		return (-1);
	if (parse_color(buff, &v, &i) == -1)
		return (-1);
	obj->col = utd_v(v.z, v.y, v.x);
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
	obj->type = 's';
	if (parse_textures(&buff[i], obj, p) == -1)
		return (-1);
	return (0);
}

