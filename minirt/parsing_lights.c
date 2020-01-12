#include "minirt.h"

int 	save_light(char *buff, t_object *light)
{
	t_vector	v;
	int 		i;

	i = 1;
	if (parse_vector(buff, &v, &i) == -1)
		return (-1);
	light->origin = v;
	if ((light->intensity = ft_atod(buff, &i)) < 0 || light->intensity > 1)
		return (-1);
	if (parse_color(buff, &v, &i) == -1)
		return (-1);
	light->color = minmax_px_lite(v);
	light->type = 'l';
	return (0);
}

int		parse_lights(char **buff, t_object *light, t_p *p)
{
	int			k;
	int			i;

	k = -1;
	i = 0;
	while (buff[++k])
		if (ft_memcmp(&buff[k][0], "l ", 2) == 0)
			p->nblights++;
	k = 0;
	if (!(light = malloc(p->nblights * sizeof(t_object))))
		return (error_msg(4, -1));
	while (buff[k])
	{
		if (ft_memcmp(&buff[k][0], "l ", 2) == 0)
		{
			if (save_light(buff[k], &light[i]) == -1 && free_ret(light, 1))
				return (error_msg(8, k + 1));
			i++;
		}
		k++;
	}
	return (0);
}

int 	parse_ambient(char **buff, t_p *p)
{
	int			k;
	int			i;

	t_vector	v;

	k = 0;
	i = 0;
	p->amb_int = 0;
	while (buff[k] && ft_memcmp(buff[k], "A ", 2) != 0)
		k++;
	if (ft_memcmp(buff[k], "A ", 2) != 0)
		return (0);
	i = k;
	k = 0;
	while (buff[k] && (ft_memcmp(buff[k], "A ", 2) != 0 || k == i))
		k++;
	if (buff[k])
		return (error_msg(9, -1));
	k = 1;
	if ((p->amb_int = ft_atod(buff[i], &k)) < 0 || p->amb_int > 1)
		return (error_msg(10, i + 1));
	if (parse_color(buff[i], &v, &k) == -1)
		return (error_msg(10, i + 1));
	p->ambient = utd_v(v.z, v.y, v.x);
	return (0);
}