/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rturcey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 13:41:48 by rturcey           #+#    #+#             */
/*   Updated: 2019/10/18 10:39:09 by rturcey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

size_t	ft_count_strings(const char *s, char c)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (!s[i])
		return (0);
	while (s[i])
	{
		if (s[i] == c)
			j = 1;
		i++;
	}
	if (j == 0)
		return (0);
	j = 0;
	i = 0;
	while (s[i])
	{
		if ((s[0] != c && i == 0) || (s[i] == c && s[i + 1] && s[i + 1] != c))
			j++;
		i++;
	}
	return (j);
}

size_t	ft_count_char(const char *s, char c)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (s[j] == c && c != '\0')
		j++;
	i = j;
	while (s[i] && s[i] != c)
		i++;
	return (i - j + 1);
}

char	**ft_final_tab(char **tab, int k, const char *s, char c)
{
	if ((k == 0 && ft_count_char(s, c) > 1) ||
			k == (int)ft_count_strings(s, c) - 1)
	{
		tab[k + 1] = NULL;
		return (tab);
	}
	else
	{
		free(tab[k]);
		tab[k] = NULL;
		return (tab);
	}
}

int		ft_fullstr(const char *s, char c, char **tab, int k)
{
	int	j;
	int	i;

	j = 0;
	i = 0;
	while (s[i] != c && s[i])
		tab[k][j++] = s[i++];
	if (j != 0)
		tab[k][j] = '\0';
	return (j);
}

char	**ft_split(const char *s, char c)
{
	char	**tab;
	int		i;
	int		j;
	int		k;

	i = 0;
	k = 0;
	j = 0;
	if (s == NULL || !(tab = malloc(((ft_count_strings(s, c) + 2) * sizeof(char\
		*)))) || (!((tab[k] = malloc(ft_count_char(s, c) * sizeof(char))))))
		return (NULL);
	while (s[i])
	{
		while (s[i] == c && s[i])
			i++;
		if (tab[k][0] && s[i] != '\0' && j != 0)
		{
			k++;
			if (!(tab[k] = malloc(ft_count_char(&s[i], c) * sizeof(char))))
				return (NULL);
		}
		j = ft_fullstr(&s[i], c, tab, k);
		i += j;
	}
	return (ft_final_tab(tab, k, s, c));
}
