/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rturcey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 12:01:49 by rturcey           #+#    #+#             */
/*   Updated: 2019/10/22 16:33:58 by rturcey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_strlencat(const char *s, size_t dsize)
{
	size_t	i;

	i = 0;
	while (i < dsize)
	{
		if (s[i] == '\0')
			return (i);
		i++;
	}
	return (dsize);
}

size_t			ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	dstlen;
	size_t	i;
	size_t	j;

	dstlen = ft_strlencat(dst, dstsize);
	i = dstlen;
	j = 0;
	if (dstlen == dstsize)
		return (ft_strlen(src) + dstsize);
	while (i < dstsize - 1 && src[j])
		dst[i++] = src[j++];
	dst[i] = '\0';
	return (dstlen + ft_strlen(src));
}
