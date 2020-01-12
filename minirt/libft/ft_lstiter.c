/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rturcey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 16:19:09 by rturcey           #+#    #+#             */
/*   Updated: 2019/10/18 16:54:47 by rturcey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	t_list	*buf;

	buf = NULL;
	if (lst && f)
		buf = lst;
	while (buf)
	{
		(*f)(buf->content);
		if (buf->next)
			buf = buf->next;
		else
			buf = NULL;
	}
}
