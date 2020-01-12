/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rturcey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 13:08:47 by rturcey           #+#    #+#             */
/*   Updated: 2019/10/18 15:13:05 by rturcey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

size_t	ft_check_start(char const *s1, char const *set)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (set[j])
	{
		if (s1 && s1[i] == set[j])
		{
			i++;
			j = 0;
		}
		else
			j++;
	}
	return (i);
}

size_t	ft_check_end(char const *s1, char const *set, size_t k)
{
	size_t	i;
	size_t	j;

	i = ft_strlen(s1) - 1;
	j = 0;
	while (set[j])
	{
		if (i > k && s1[i] == set[j])
		{
			i--;
			j = 0;
		}
		else
			j++;
	}
	return (i);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*s2;
	size_t	i;
	size_t	j;
	size_t	k;

	i = 0;
	j = 0;
	k = 0;
	if (s1 == NULL || set == NULL)
		return (NULL);
	k = ft_check_start(s1, set);
	i = ft_check_end(s1, set, k);
	if (!(s2 = malloc((i - k + 2) * sizeof(char))))
		return (NULL);
	while (k <= i && s1[k])
		s2[j++] = s1[k++];
	s2[j] = '\0';
	return (s2);
}
