#include "minirt.h"

int 	save_uv_mapping(char *buff, t_object *obj, t_p *p)
{
	/*t_mapping	m;
	int			i;
	char		addr[255];
	int 		useless;

	i = 0;
	while (buff[i] && buff[i] != '"')
		i++;
	if (i > 255)
	{
		ft_putstr_fd("The path of your file is too long\n", 2);
		return (-1);
	}
	ft_strlcpy(addr, buff, i);
	obj->uvmap = m;
	if (!(m.ptr = mlx_xpm_file_to_image(p->mlx_p, addr, &m.x, &m.y)))
	{
		ft_putstr_fd("mlx_xpm_file_to_image can't read your file\n", 2);
		return (-1);
	}
	if (!(m.img = (t_color *)mlx_get_data_addr(m.ptr, &useless, &useless, &useless)))
	{
		ft_putstr_fd("mlx_get_data_addr error\n", 2);
		return (-1);
	}*/
	return (0);
}

int 	parse_uv_mapping(char *buff, t_object *obj, t_p *p)
{
	int	i;
	int	k;

	i = 0;
	while ((buff[i] >= 9 && buff[i] <= 13) || buff[i] == 32)
		i++;
	if (buff[i] != '"')
	{
		ft_putstr_fd("You should indicate a .xpm file for UV mapping\n", 2);
		return (-1);
	}
	i++;
	k = i;
	while (buff[i + 4] && buff[i] != '.' && buff[i + 1] != 'x' && \
		buff[i + 2] != 'p' && buff[i + 3] != 'm' && buff[i + 4] != '"')
		i++;
	if (!buff[i + 4])
	{
		ft_putstr_fd("You should indicate a .xpm file for UV mapping\n", 2);
		return (-1);
	}
	return (save_uv_mapping(&buff[k], obj, p));
}

int 	parse_textures(char *buff, t_object *obj, t_p *p)
{
	int	i;

	i = 0;
	while (buff[i])
	{
		if (buff[i] == 'd' || buff[i] == 'D')
		{
			if ((obj->ch = ft_atoi(&buff[i + 1]) < 1))
				return (-1);
			obj->effect = buff[i];
		}
		else if (buff[i] == 'r' || buff[i] == 'R')
		{
			if ((obj->rainbow = ft_atod(buff, &i)) < 0 || obj->rainbow > 255)
				return (-1);
			obj->effect = buff[i];
		}
		else if ((buff[i] == 'b' || buff[i] == 'B') && obj->type == 's')
		{
			if (parse_uv_mapping(&buff[i + 1], obj, p) == -1)
				return (-1);
		}
		else if (buff[i] >= 'A' && buff[i] <= 'Z')
			obj->effect = buff[i];
		i++;
	}
	return (0);
}