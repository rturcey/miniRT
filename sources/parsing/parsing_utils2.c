/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rturcey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 14:47:36 by rturcey           #+#    #+#             */
/*   Updated: 2020/01/15 14:47:38 by rturcey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int		free_ret(void *ptr, int ret)
{
	free(ptr);
	ptr = NULL;
	return (ret);
}

int		check_ts(char **buff)
{
	int		k;

	k = 0;
	while (buff[k] != NULL)
	{
		if (!(ft_strnstr(buff[k], "A ", 2) || ft_strnstr(buff[k], "R", 1) || \
			ft_strnstr(buff[k], "c ", 2) || ft_strnstr(buff[k], "l ", 2) || \
			ft_strnstr(buff[k], "sp ", 3) || ft_strnstr(buff[k], "pl ", 3) || \
			ft_strnstr(buff[k], "sq ", 3) || ft_strnstr(buff[k], "cy ", 3) || \
			ft_strnstr(buff[k], "tr ", 3) || ft_strnstr(buff[k], "py ", 3) || \
			ft_strnstr(buff[k], "cu ", 3) || ft_strnstr(buff[k], "aa ", 3) || \
			ft_strnstr(buff[k], "f ", 2) || ft_strnstr(buff[k], "co ", 3)))
			return (error_msg(11, k + 1));
		k++;
	}
	return (0);
}

char	*error_stock(int n)
{
	char	*msg[18];

	msg[0] = "\033[31mInvalid argument(s)\033[0m";
	msg[2] = "\033[31mInvalid file\033[0m";
	msg[3] = "\033[31mProblem while reading the file\033[0m";
	msg[4] = "\033[31mAn allocation failed while parsing\033[0m";
	msg[5] = "\033[31mResolution is missing or incorrect\033[0m";
	msg[6] = "\033[31mHow are you supposed to see something without a camera ?\033[0m";
	msg[7] = "\033[31mYour camera has wrong parameters\033[0m";
	msg[8] = "\033[31mYour light has wrong parameters\033[0m";
	msg[9] = "\033[31mYou shouldn't have more than one ambient light\033[0m";
	msg[10] = "\033[31mYour ambient light has wrong parameters\033[0m";
	msg[11] = "\033[31mI'm not able to understand at least one of your lines\033[0m";
	msg[12] = "\033[31mWhat would I do with a second antialiasing ?\033[0m";
	msg[13] = "\033[31mAntialiasing requires an integer between 2 and 6\033[0m";
	msg[14] = "\033[31mI can't deal with more than one filter\033[0m";
	msg[15] = "\033[31mWrong filter parameter ('r'/'g'/'b'/'p'/'n')\033[0m";
	msg[16] = "\033[31mWhat would I do with a second resolution ?\033[0m";
	msg[17] = "\033[31mYour object has wrong parameters\033[0m";
	return (msg[n]);
}

int		error_msg(int n, int line)
{
	ft_putstr_fd("\033[1m\033[31mError\033[0m\n", 2);
	ft_putstr_fd(error_stock(n), 2);
	if (line > -1)
	{
		write(2, " (line ", 7);
		ft_putnbr_fd(line, 2);
		write(2, ")", 1);
	}
	write(2, "\n", 1);
	return (-1);
}

int		checkfilename(char *s)
{
	int		i;

	i = ft_strlen(s);
	if (ft_memcmp(&s[i - 3], ".rt", ft_strlen(&s[i - 3])) != 0)
		return (-1);
	return (0);
}
