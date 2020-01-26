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

void	ft_filename(t_p *p, char *av)
{
	int		i;
	int		k;
	char	*buf;

	i = (int)ft_strlen(av);
	k = -1;
	if (!(p->filename = malloc(i - 1)))
		return ;
	while (++k < i - 2)
		p->filename[k] = av[k];
	p->filename[k] = 0;
	buf = ft_strjoin(&p->filename[7], "bmp");
	free(p->filename);
	p->filename = buf;
	buf = ft_strjoin("images/", p->filename);
	free(p->filename);
	p->filename = buf;
	p->save = 's';
}

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
	p->w = (int)fmin(2560, p->w);
	p->h = (int)fmin(1440, p->h);
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
	ft_putstr_fd("\033[35m==================\033[0m\n", 1);
	ft_putstr_fd("\033[1m\033[32mCONFIGURATION OK !\033[0m\n", 1);
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
	free_ret(full, 1);
	p->mlx_p = mlx_init();
	if (argc == 3 && ft_memcmp(argv[2], "-save", ft_strlen(argv[2])) == 0)
		ft_filename(p, argv[1]);
	i = -1;
	if (ft_parser(buf, p) == 0)
	{
		while (buf[++i])
			free_ret(buf[i], 0);
		free(buf);
		init_image(p);
	}
	return (0);
}
