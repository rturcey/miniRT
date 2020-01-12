/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rturcey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 17:36:46 by rturcey           #+#    #+#             */
/*   Updated: 2020/01/07 12:21:30 by rturcey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strjoin_gnl(char *s1, char *s2)
{
	char	*s3;
	size_t	i;
	size_t	j;
	size_t	len;

	s3 = NULL;
	i = 0;
	j = 0;
	len = 0;
	if (s1 == NULL || s2 == NULL || !(s3 = malloc((ft_strlen(s1) \
						+ ft_strlen(s2) + 1) * sizeof(char))))
		return (s3);
	while (s1[i])
	{
		s3[i] = s1[i];
		i++;
	}
	while (s2[j])
		s3[i++] = s2[j++];
	s3[i] = '\0';
	free(s1);
	return (s3);
}

char	*ft_strndup(const char *s1, size_t len)
{
	char	*s2;
	size_t	i;

	i = 0;
	if (len == 0)
	{
		if (!(s2 = malloc(1)))
			return (NULL);
		s2[0] = '\0';
		return (s2);
	}
	if (!(s2 = malloc((len + 1) * sizeof(char))))
		return (NULL);
	while (s1[i] && i < len)
	{
		s2[i] = s1[i];
		i++;
	}
	s2[i] = '\0';
	return (s2);
}

char	*ft_strchr_gnl(const char *s, int c)
{
	int		i;

	i = 0;
	while (s[i] != (char)c)
		if (!s[i++])
			return (NULL);
	return ((char *)&s[i]);
}
