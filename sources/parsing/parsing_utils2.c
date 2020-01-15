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

	msg[0] = "Invalid argument(s)";
	msg[2] = "Invalid file";
	msg[3] = "Problem while reading the file";
	msg[4] = "An allocation failed while parsing";
	msg[5] = "Resolution is missing or incorrect";
	msg[6] = "How are you supposed to see something without a camera ?";
	msg[7] = "Your camera has wrong parameters";
	msg[8] = "Your light has wrong parameters";
	msg[9] = "You shouldn't have more than one ambient light";
	msg[10] = "Your ambient light has wrong parameters";
	msg[11] = "I'm not able to understand at least one of your lines";
	msg[12] = "What would I do with a second antialiasing ?";
	msg[13] = "Antialiasing requires an integer between 2 and 6";
	msg[14] = "I can't deal with more than one filter";
	msg[15] = "Wrong filter parameter ('r'/'g'/'b'/'p'/'n')";
	msg[16] = "What would I do with a second resolution ?";
	msg[17] = "Your object has wrong parameters";
	return (msg[n]);
}

int		error_msg(int n, int line)
{
	ft_putstr_fd("Error\n", 2);
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
