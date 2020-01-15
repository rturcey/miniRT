/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rturcey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 11:35:55 by rturcey           #+#    #+#             */
/*   Updated: 2019/10/16 17:21:34 by rturcey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_intarr(char *result, long i, long j, long k)
{
	if (j == 1)
		result[0] = '-';
	while (i >= 1)
	{
		result[j] = ((k / i) % 10) + '0';
		i /= 10;
		j++;
	}
	result[j] = '\0';
	return (result);
}

char	*ft_itoa(int n)
{
	long	i;
	long	j;
	long	k;
	char	*result;

	i = 1;
	j = 0;
	k = n;
	if (n < 0)
		k = -k;
	while (k / i >= 10)
	{
		j++;
		i *= 10;
	}
	if (n == 0)
		j = -1;
	if (!(result = malloc((j + 3) * sizeof(char))))
		return (NULL);
	j = 0;
	if (n < 0)
		return (ft_intarr(result, i, 1, k));
	else
		return (ft_intarr(result, i, 0, k));
}
