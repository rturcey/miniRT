/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rturcey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 16:38:32 by rturcey           #+#    #+#             */
/*   Updated: 2019/10/22 17:38:45 by rturcey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*buf;
	t_list	*mem;

	buf = NULL;
	if (!lst || !f || !del)
		return (NULL);
	buf = ft_lstnew(NULL);
	mem = buf;
	while (lst)
	{
		if (!(buf->content = (*f)(lst->content)))
		{
			ft_lstclear(&mem, del);
			return (NULL);
		}
		lst = lst->next;
		buf->next = ft_lstnew(NULL);
		buf = buf->next;
	}
	return (mem);
}
