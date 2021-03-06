/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rturcey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 17:36:38 by rturcey           #+#    #+#             */
/*   Updated: 2020/01/15 14:50:28 by rturcey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*new_line(char *tab_line, char **line)
{
	int		i;
	char	*rest;

	i = 0;
	rest = NULL;
	while (tab_line[i] && tab_line[i] != '\n')
		i++;
	*line = ft_strndup(tab_line, i);
	if (tab_line[i] && tab_line[i + 1])
		rest = ft_strndup(&tab_line[i + 1], ft_strlen(&tab_line[i + 1]));
	free(tab_line);
	return (rest);
}

int		get_next_line(int fd, char **line)
{
	static char	*tab_lines[OPEN_MAX];
	char		bf[BUFF_SIZE + 1];
	int			i;
	int			lev;

	i = 0;
	lev = 0;
	if (fd < 0 || !line || BUFF_SIZE < 1 || read(fd, bf, 0) < 0)
		return (-1);
	if (tab_lines[fd] == NULL)
		tab_lines[fd] = ft_strndup("", 0);
	while (ft_strchr_gnl(tab_lines[fd], '\n') || \
		(i = read(fd, bf, BUFF_SIZE)) > 0)
	{
		bf[i] = '\0';
		tab_lines[fd] = ft_strjoin_gnl(tab_lines[fd], bf);
		if (ft_strchr_gnl(tab_lines[fd], '\n') && ++i)
			break ;
	}
	if (i >= 0)
		tab_lines[fd] = new_line(tab_lines[fd], line);
	if (i > 0 || *line[0])
		return (1);
	return (i);
}
