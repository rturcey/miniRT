#include "minirt.h"

int		free_ret(void *ptr, int ret)
{
	free(ptr);
	ptr = NULL;
	return (ret);
}

double	checkdouble(char *str)
{
	int 	i;
	int 	k;

	i = 0;
	k = -1;
	while (str[i++])
		if ((str[i] < '0' || str[i] > '9') && str[i] != '.' && str[i] != '-')
			str[i] = '\0';
	i = 0;
	while (str[i])
	{
		if (k > -1 && (k++) > 15)
			return (free_ret(str, -1));
		if (str[i] == '.')
		{
			if (ft_strchr(&str[i + 1], '.'))
				return (free_ret(str, -1));
			k = 0;
		}
		i++;
	}
	return (free_ret(str, 0));
}

double	ft_atod(char *str, int *i)
{
	double 	number;
	double	sign;
	double	dot;

	number = 0;
	sign = 1;
	dot = 1;
	while ((str[*i] >= 9 && str[*i] <= 13) || str[*i] == 32)
		(* i)++;
	if (checkdouble(ft_strdup(&str[*i])) == -1)
		return (1E99);
	if (str[*i] == '-')
	{
		sign = -1;
		(* i)++;
	}
	while ((str[*i] >= '0' && str[*i] <= '9') || str[*i] == '.')
	{
		if (str[*i] == '.')
			dot = 10;
		else if (dot == 1)
			number = number * 10 + str[*i] - '0';
		else
		{
			number = number + (str[*i] - '0') / dot;
			dot *= 10;
		}
		(* i)++;
	}
	while (str[*i] == '-' || ft_isdigit(str[*i]) || str[*i] == '.')
		(* i)++;
	return (sign * number);
}

int 	parse_vector(char *v, t_vector *r, int *i)
{
	while ((v[*i] >= 9 && v[*i] <= 13) || v[*i] == 32)
		(* i)++;
	if ((r->x = ft_atod(v, i)) == 1E99)
		return (-1);
	while (v[*i] == '-' || ft_isdigit(v[*i]) || v[*i] == '.')
		(* i)++;
	if (v[*i] != ',')
		return (-1);
	(* i)++;
	if ((r->y = ft_atod(v, i)) == 1E99)
		return (-1);
	while (v[*i] == '-' || ft_isdigit(v[*i]) || v[*i] == '.')
		(* i)++;
	if (v[*i] != ',')
		return (-1);
	(* i)++;
	if ((r->z = ft_atod(v, i)) == 1E99)
		return (-1);
	while (v[*i] == '-' || ft_isdigit(v[*i]) || v[*i] == '.')
		(* i)++;
	return (0);
}

int 	parse_vecrot(char *v, t_vector *r, int *i)
{
	while ((v[*i] >= 9 && v[*i] <= 13) || v[*i] == 32)
		(* i)++;
	if ((r->x = ft_atod(v, i)) == 1E99 || (r->x < -1 || r->x > 1))
		return (-1);
	while (v[*i] == '-' || ft_isdigit(v[*i]) || v[*i] == '.')
		(* i)++;
	if (v[*i] != ',')
		return (-1);
	(* i)++;
	if ((r->y = ft_atod(v, i)) == 1E99 || (r->y < -1 || r->y > 1))
		return (-1);
	while (v[*i] == '-' || ft_isdigit(v[*i]) || v[*i] == '.')
		(* i)++;
	if (v[*i] != ',')
		return (-1);
	(* i)++;
	if ((r->z = ft_atod(v, i)) == 1E99 || (r->z < -1 || r->z > 1))
		return (-1);
	while (v[*i] == '-' || ft_isdigit(v[*i]) || v[*i] == '.')
		(* i)++;
	return (0);
}

int 	parse_color(char *v, t_vector *r, int *i)
{
	while ((v[*i] >= 9 && v[*i] <= 13) || v[*i] == 32)
		(* i)++;
	if ((r->x = ft_atoi(&v[*i])) < 0 || r->x > 255)
		return (-1);
	while (v[*i] == '-' || ft_isdigit(v[*i]) || v[*i] == '.')
		(* i)++;
	if (v[*i] != ',')
		return (-1);
	(* i)++;
	while ((v[*i] >= 9 && v[*i] <= 13) || v[*i] == 32)
		(* i)++;
	if ((r->y = ft_atoi(&v[*i])) < 0 || r->y > 255)
		return (-1);
	while (v[*i] == '-' || ft_isdigit(v[*i]) || v[*i] == '.')
		(* i)++;
	if (v[*i] != ',')
		return (-1);
	(* i)++;
	while ((v[*i] >= 9 && v[*i] <= 13) || v[*i] == 32)
		(* i)++;
	if ((r->z = ft_atoi(&v[*i])) < 0 || r->z > 255)
		return (-1);
	while (v[*i] == '-' || ft_isdigit(v[*i]) || v[*i] == '.')
		(* i)++;
	return (0);
}
