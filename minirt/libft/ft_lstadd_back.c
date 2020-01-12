/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rturcey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 17:39:17 by rturcey           #+#    #+#             */
/*   Updated: 2019/10/16 17:32:30 by rturcey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **alst, t_list *new)
{
	t_list	*buf;

	buf = NULL;
	if (alst && new)
	{
		buf = *alst;
		if (buf != NULL)
		{
			while (buf->next != NULL)
				buf = buf->next;
			buf->next = new;
			new->next = NULL;
		}
		else
		{
			new->next = NULL;
			*alst = new;
		}
	}
}
