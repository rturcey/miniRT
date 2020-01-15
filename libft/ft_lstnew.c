/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rturcey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 09:19:06 by rturcey           #+#    #+#             */
/*   Updated: 2019/10/15 15:52:41 by rturcey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list			*newelem;
	char			*buf;
	size_t			len;

	if (!(newelem = malloc(sizeof(t_list))))
		return (NULL);
	if (content == NULL)
	{
		newelem->content = NULL;
		newelem->next = NULL;
		return (newelem);
	}
	buf = (char *)content;
	len = ft_strlen(buf) + 1;
	if (!(newelem->content = malloc(sizeof(content) * len)))
		return (NULL);
	newelem->content = ft_memcpy(newelem->content, content, len);
	newelem->next = NULL;
	return (newelem);
}
