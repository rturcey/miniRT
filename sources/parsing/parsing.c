/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rturcey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 14:46:36 by rturcey           #+#    #+#             */
/*   Updated: 2020/01/15 14:46:39 by rturcey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int		fill_tab(char *line, char **full)
{
	char	*temp;

	if (ft_memcmp(line, "", ft_strlen(line)) == 0)
		return (0);
	*full = (*full == NULL) ? ft_strdup("") : *full;
	temp = ft_strjoin_gnl(*full, line);
	*full = ft_strjoin_gnl(temp, "\n");
	return (0);
}

int		ft_parser(char **buff, t_p *p)
{
	if (parse_resolution(buff, p) == -1)
		return (-1);
	if (parse_cameras(buff, &p->r, p) == -1)
		return (-1);
	if (parse_lights(buff, &p->l, p) == -1)
		return (-1);
	if (parse_ambient(buff, p) == -1)
		return (-1);
	if (parse_effects(buff, p) == -1)
		return (-1);
	if (parse_objects(buff, &p->o, p) == -1)
		return (-1);
	return (0);
}

int		parse_argts(int argc, char **argv, char **full)
{
	char	*line;
	int		i;

	*full = ft_strdup("");
	i = 0;
	if (argc <= 1 || (argc == 2 && argv[1] == NULL) || argc > 3 \
		|| (argc == 3 && ft_memcmp(argv[2], "-save", ft_strlen(argv[2])) != 0))
		return (error_msg(0, -1));
	if (checkfilename(argv[1]) == -1 || (i = open(argv[1], O_RDONLY)) < 1)
		return (error_msg(2, -1));
	while ((get_next_line(i, &line)) > 0)
	{
		if (fill_tab(line, full) == -1)
		{
			free(line);
			close(i);
			return (error_msg(4, -1));
		}
		free(line);
	}
	free(line);
	close(i);
	return (0);
}

int		main(int argc, char **argv)
{
	int		i;
	char	*full;
	char	**buf;
	t_p		*p;

	if ((i = parse_argts(argc, argv, &full)) == -1)
		return (error_msg(3, -1));
	init_p(&p);
	if (!(buf = ft_split(full, '\n')) && free_ret(full, 1))
		return (error_msg(4, -1));
	p->mlx_p = mlx_init();
	if (check_ts(buf) == -1)
		return (-1);
	if (argc == 3 && ft_memcmp(argv[2], "-save", ft_strlen(argv[2])) != 0)
		p->save = 's';
	if (ft_parser(buf, p) == 0)
	{
		ft_putstr_fd("Configuration OK\nRaytracing...\n", 1);
		init_image(p);
	}
	i = -1;
	while (buf[++i])
		free_ret(buf[i], 0);
	return (0);
}
