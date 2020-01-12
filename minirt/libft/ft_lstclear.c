/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rturcey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 14:43:49 by rturcey           #+#    #+#             */
/*   Updated: 2019/11/05 17:45:21 by rturcey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*buf;
	t_list	*buf2;

	buf = NULL;
	buf2 = NULL;
	if (lst && *lst && del)
	{
		buf = *lst;
		while (buf->next)
		{
			buf2 = buf->next;
			(*del)(buf->content);
			free(buf);
			buf = buf2;
		}
		if (buf)
		{
			(*del)(buf->content);
			free(buf);
		}
		*lst = NULL;
	}
}
