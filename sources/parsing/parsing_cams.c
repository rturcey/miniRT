#include "minirt.h"

int		parse_resolution(char **buff, t_p *p)
{
	int		k;
	int		i;

	k = 0;
	i = 0;
	while (buff[k] != NULL && ft_memcmp(buff[k], "R", 1) != 0)
		k++;
	if (!buff[k] || ft_memcmp(buff[k], "R", 1) != 0)
		return (error_msg(5, k + 1));
	i = k;
	k = 0;
	while (buff[k] && (ft_memcmp(buff[k], "R", 1) != 0 || k == i))
		k++;
	if (buff[k])
		return (error_msg(16, k + 1));
	k = i;
	i = 1;
	p->w = ft_atoi(&buff[k][i]);
	while (buff[k][i] && ft_isdigit(buff[k][i]) == 1)
		i++;
	p->h = ft_atoi(&buff[k][i]);
	if (p->w <= 0 || p->h <= 0)
		return (error_msg(5, -1));
	return (0);
}

int 	save_cam(char *buff, t_object *cam)
{
	t_vector	v;
	int 		i;

	i = 1;
	if (parse_vector(buff, &v, &i) == -1)
		return (-1);
	cam->origin = v;
	if (parse_vecrot(buff, &v, &i) == -1)
		return (-1);
	cam->rot = v;
	if ((cam->fov = ft_atod(buff, &i)) < 0 || cam->fov > 180)
		return (-1);
	cam->fov = cam->fov * M_PI / 180;
	cam->type = 'r';
	return (0);
}

int		parse_cameras(char **buff, t_object **cam, t_p *p)
{
	int			k;
	int			i;

	k = 0;
	i = 0;
	while (buff[k] && ft_memcmp(buff[k], "c ", 2) != 0)
		k++;
	if (buff[k][0] != 'c')
		return (error_msg(6, -1));
	p->nbcams = 1;
	while (buff[++k])
		if (ft_memcmp(&buff[k][0], "c ", 2) == 0)
			p->nbcams++;
	k = 0;
	if (!(*cam = malloc(p->nbcams * sizeof(t_object))))
		return (error_msg(4, -1));
	init_obj(cam, p->nbcams);
	while (buff[k])
	{
		if (ft_memcmp(buff[k], "c ", 2) == 0)
		{
			if (save_cam(buff[k], &(* cam)[i]) == -1)
			{
				free(*cam);
				return (error_msg(7, k + 1));
			}
			i++;
		}
		k++;
	}
	return (0);
}