#include "includes/minirt.h"

void	create_cylinder(t_object *obj, t_p *p)
{
	t_vector	c;

	p->o[count + 1] = obj;
	p->o[count + 1]->origin = mult_v(o->h / 2, o->r);
	p->o[count + 1]->origin = min_v(o->origin, p->o[count]->origin);
	p->o[count + 1]->composed = 1;
	p->o[count + 2] = obj;
	p->o[count + 2]->origin = mult_v(o->h / 2, o->r);
	p->o[count + 2]->origin = add_v(o->origin, p->o[count]->origin);
	p->o[count + 2]->composed = 1;
}

int 	parse_cylinder(char *buff, t_object *obj, t_p *p)
{
	int 		i;
	t_vector	v;

	i = 2;
	if (parse_vector(buff, &v, &i) == -1)
		return (-1);
	obj->origin = v;
	if (parse_vecrot(buff, &v, &i) == -1)
		return (-1);
	obj->rot = normed(v);
	if ((obj->rayon = ft_atod(buff, &i)) < 0 || obj->rayon == 1E99)
		return (-1);
	if ((obj->h = ft_atod(buff, &i)) < 0 || obj->h == 1E99)
		return (-1);
	if (parse_color(buff, &v, &i) == -1)
		return (-1);
	obj->col = utd_v(v.z, v.y, v.x);
	obj->type = 'c';
	if (parse_textures(&buff[i], obj, p) == -1)
		return (-1);
	create_cylinder(obj, p)
	obj->composed = -1;
	return (0);
}

int 	parse_pyramid(char *buff, t_object *obj, t_p *p)
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
	if ((obj->rayon = ft_atod(buff, &i)) == 1E99)
		return (-1);
	if ((obj->h = ft_atod(buff, &i)) < 0 || obj->h == 1E99)
		return (-1);
	if (parse_color(buff, &v, &i) == -1)
		return (-1);
	obj->col = utd_v(v.z, v.y, v.x);
	obj->type = 'q';
	if (parse_textures(&buff[i], obj, p) == -1)
		return (-1);
	create_pyramid(obj, p)
	obj->composed = -3;
	return (0);
}

int 	parse_cube(char *buff, t_object *obj, t_p *p)
{
	int 		i;
	t_vector	v;

	i = 2;
	if (parse_vector(buff, &v, &i) == -1)
		return (-1);
	obj->center = v;
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
	create_cube(buff, obj);
	obj->composed = -2;
	return (0);
}