/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_textures.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rturcey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 14:47:30 by rturcey           #+#    #+#             */
/*   Updated: 2020/01/15 14:47:31 by rturcey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int		save_uv_mapping(char *s, t_object *obj, t_p *p)
{
	t_mapping	*m;
	int			i;
	char		addr[255];
	int			u;

	i = 0;
	while (s[i] && s[i] != '"')
		i++;
	if (i > 255)
	{
		ft_putstr_fd("The path of your file is too long\n", 2);
		return (-1);
	}
	ft_strlcpy(addr, s, i + 1);
	if (!(m = malloc(sizeof(t_mapping))))
		return (-1);
	if (!(m->ptr = mlx_xpm_file_to_image(p->mlx_p, addr, &m->x, &m->y)))
		return (-1);
	if (!(m->img = (t_color *)mlx_get_data_addr(m->ptr, &u, &u, &u)))
		return (-1);
	obj->uvmap = m;
	return (0);
}

int		parse_uv_mapping(char *s, t_object *obj, t_p *p)
{
	int	i;
	int	k;

	i = 0;
	while ((s[i] >= 9 && s[i] <= 13) || s[i] == 32)
		i++;
	if (s[i] != '"')
	{
		ft_putstr_fd("You should indicate a .xpm file for UV mapping\n", 2);
		return (-1);
	}
	i++;
	k = i;
	while (s[i + 4] && s[i] != '.' && s[i + 1] != 'x' && \
		s[i + 2] != 'p' && s[i + 3] != 'm' && s[i + 4] != '"')
		i++;
	if (!s[i + 4])
	{
		ft_putstr_fd("You should indicate a .xpm file for UV mapping\n", 2);
		return (-1);
	}
	return (save_uv_mapping(&s[k], obj, p));
}

int		parse_textures(char *s, t_object *obj, t_p *p)
{
	int			i;
	t_vector	v;

	i = -1;
	while (++i < (int)ft_strlen(s) && s[i] && obj->effect == '\0')
	{
		if ((s[i] == 'd' || s[i] == 'D') && (obj->effect = s[i++]))
		{
			obj->col1 = obj->col;
			if (parse_color(s, &v, &i) == -1)
				return (-1);
			obj->col2 = utd_v(v.z, v.y, v.x);
			if ((obj->ch = ft_atoi(&s[i])) < 1)
				return (-1);
		}
		if ((s[i] == 'r' || s[i] == 'R') && (obj->effect = s[i++]))
			if ((obj->rainbow = ft_atod(s, &i, 1)) < 0 || obj->rainbow > 255)
				return (-1);
		if ((s[i] == 'b' || s[i] == 'B') && (obj->effect = s[i]))
			if (parse_uv_mapping(&s[i + 1], obj, p) == -1)
				return (-1);
		if (s[i] == 'm' || s[i] == 'M')
			obj->effect = s[i];
	}
	return (0);
}
