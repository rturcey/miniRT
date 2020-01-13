/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rturcey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 14:46:00 by rturcey           #+#    #+#             */
/*   Updated: 2019/10/22 18:48:59 by rturcey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	int		add;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	add = 0;
	while (haystack[i] && i < len)
	{
		while ((haystack[i + j] == needle[j]) && needle[j] && ((i + j) < len))
			j++;
		if (!needle[j])
			return ((char *)&haystack[i]);
		j = 0;
		i++;
	}
	if (!needle[0])
		return ((char *)&haystack[i]);
	return (NULL);
}
