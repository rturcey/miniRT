#include <stdio.h>
#include "includes/minirt.h"
#include "libft/libft.h"
#include "libft/get_next_line/get_next_line.h"

t_color_db	minmax_px_lite(t_vector px)
{
	t_color_db	c;

	c.red = fmax(0, fmin(255, px.z));
	c.green = fmax(0, fmin(255, px.y));
	c.blue = fmax(0, fmin(255, px.x));
	return (c);
}

//////////////////////////////////////////////////////////

int	error_msg(int n, int line)
{
	char	*msg[100];

	msg[0] = "Invalid argument(s)";
	msg[1] = "Please insert a .rt file";
	msg[2] = "Invalid file";
	msg[3] = "Problem while reading the file";
	msg[4] = "An allocation failed while parsing";
	msg[5] = "Resolution is missing or incorrect";
	msg[6] = "How are you suppose to see something without camera ?";
	msg[7] = "Your camera has bad parameters";
	msg[8] = "Your light has bad parameters";
	msg[9] = "You shouldn't have more than one ambient light";
	msg[10] = "Your ambient light has bad parameters";
	msg[11] = "I'm not able to understand at list one of your lines";
	msg[12] = "What would I do with a second antialiasing ?";
	msg[13] = "Antialiasing needs an integer between 2 and 6";
	msg[14] = "I can't deal with more than one filter";
	msg[15] = "Bad filter parameter ('r'/'g'/'b' or 'p' for sepia, 'n' for black & white)";
	msg[16] = "What would I do with a second resolution ?";
	msg[17] = "Your object has bad parameters";

	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd(msg[n], 2);
	if (line > -1)
	{
		write(2, " (line ", 7);
		ft_putnbr_fd(line, 2);
		write(2, ")", 1);
	}
	write (2, "\n", 1);
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

int 	fill_tab(char *line, char **full)
{
	char	*temp;

	if (ft_memcmp(line, "", ft_strlen(line)) == 0)
		return (0);
	*full = (*full == NULL) ? ft_strdup("") : *full;
	temp = ft_strjoin_gnl(*full, line);
	*full = ft_strjoin_gnl(temp, "\n");
	return (0);
}

char		**ft_buffcopy(char *full)
{
	int		i;
	int		j;
	int		k;
	int 	max;
	char	**buff;

	i = 0;
	j = 0;
	k = 0;
	max = 0;
	while (full[i])
	{
		if (full[i] == '\n')
			j++;
		i++;
	}
	i = 0;
	if(!(buff = malloc((j + 1) * sizeof(char *))))
		return (NULL);
	max = j;
	j = 0;
	while (i < ft_strlen(full))
	{
		while (full[i] && full[i] != '\n')
		{
			i++;
			j++;
		}
		i++;
		if (!(buff[k] = malloc((j + 2) * sizeof(char))))
			return (NULL);
		k++;
		j = 0;
	}
	k = 0;
	i = 0;
	j = 0;
	while (full[i] && k < max)
	{
		if (k < max)
		{
			buff[k][j] = full[i];
			j++;
		}
		i++;
		if (full[i] == '\n')
		{
			buff[k][j] = '\0';
			k++;
			j = 0;
			i++;
		}
	}
	buff[max] = NULL;
	free_ret(full, 0);
	return (buff);
}

int		ft_parser(char **buff, t_p *p)
{
	if (parse_resolution(buff, p) == -1)
		return (-1);
	if (parse_cameras(buff, p->r, p) == -1)
		return (-1);
	if (parse_lights(buff, p->l, p) == -1)
		return (-1);
	if (parse_ambient(buff, p) == -1)
		return (-1);
	if (parse_effects(buff, p) == -1)
		return (-1);
	if (parse_objects(buff, p->o, p) == -1)
		return (-1);
	return (0);
}

int 	check_types(char **buff)
{
	int 	k;

	k = 0;
	while (buff[k] != NULL)
	{
		if (!(ft_strnstr(buff[k], "A ", 2) || ft_strnstr(buff[k], "R ", 2) || \
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

int	main(int argc, char **argv)
{
	int		fd;
	int		i;
	char	*line;
	char	*full;
	char	**buf;
	t_p		*p;

	i = 0;
	init_p(p);
	full = ft_strdup("");
	if (argc <= 1 || (argc == 2 && argv[1] == NULL) || argc > 3 \
		|| (argc == 3 && ft_memcmp(argv[2], "-save", ft_strlen(argv[2])) != 0))
		return (error_msg(0, -1));
	if (checkfilename(argv[1]) == -1)
		return (error_msg(1, -1));
	if ((fd = open(argv[1], O_RDONLY)) < 1)
		return (error_msg(2, -1));
	while ((i = get_next_line(fd, &line)) > 0)
	{
		if (fill_tab(line, &full) == -1)
		{
			free(line);
			close(fd);
			return (error_msg(4, -1));
		}
		free(line);
	}
	free(line);
	close(fd);
	if (i < 0)
		return (error_msg(3, -1));
	if (!(buf = ft_buffcopy(full)))
	{
		free(full);
		return (error_msg(4, -1));
	}
	if (check_types(buf) == -1)
		return (-1);
	if (argc == 3 && ft_memcmp(argv[2], "-save", ft_strlen(argv[2])) != 0)
		fd = 's';
	if (ft_parser(buf, p) == 0)
		init_image(p, fd);
	i = -1;
	while (buf[++i])
		free_ret(buff[i], 0);
	return (0);
}

void	init_p(t_p *p)
{
	p->w = 0;
	p->h = 0;
	p->nbcams = 0;
	p->nblights = 0;
	p->nobjs = 0;
	p->count = 0;
	p->fov = 0;
	p->x = 0;
	p->amb_int = 0;
	p->aa = 1;
	p->filter = '\0';
	p->mlx_p = NULL;
	p->mlx_i = NULL;
	p->mlx_w = NULL;
	p->threads = 1;
	p->aarainb = 1;
	p->mouse = 1;
}