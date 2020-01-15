/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rturcey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 17:36:56 by rturcey           #+#    #+#             */
/*   Updated: 2020/01/07 12:22:49 by rturcey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFF_SIZE
#  define BUFF_SIZE 32
# endif
# ifndef OPEN_MAX
#  define OPEN_MAX 1024
# endif

# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdlib.h>
# include <limits.h>
# include <unistd.h>
# include "libft.h"

int		get_next_line(int fd, char **line);
char	*new_line(char *tab_line, char **line);
char	*ft_strjoin_gnl(char *s1, char *s2);
char	*ft_strndup(const char *s1, size_t len);
char	*ft_strchr_gnl(const char *s, int c);

#endif
