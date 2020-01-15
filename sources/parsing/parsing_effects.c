
#include "minirt.h"

int 	parse_effects(char **buff, t_p *p)
{
	if (parse_antialiasing(buff, p) == -1)
		return (-1);
	if (parse_filters(buff, p) == -1)
		return (-1);
	return (0);
}

int		parse_antialiasing(char **buff, t_p *p)
{
	int			k;
	int			i;

	k = 0;
	i = 0;
	p->aa = 1;
	while (buff[k] && ft_memcmp(buff[k], "aa ", 3) != 0)
		k++;
	if (!buff[k] || ft_memcmp(buff[k], "aa ", 3) != 0)
		return (0);
	i = k;
	k = 0;
	while (buff[k] && (ft_memcmp(buff[k], "aa ", 3) != 0 || k == i))
		k++;
	if (buff[k])
		return (error_msg(12, k + 1));
	k = 2;
	while ((buff[i][k] >= 9 && buff[i][k] <= 13) || buff[i][k] == 32)
		k++;
	if ((p->aa = ft_atod(buff[i], &k)) < 2 || p->aa > 6)
		return (error_msg(13, i + 1));
	p->aa = pow(p->aa, 2);
	return (0);
}

int		parse_filters(char **buff, t_p *p)
{
	int			k;
	int			i;

	k = 0;
	i = 0;
	p->filter = '\0';
	while (buff[k] && ft_memcmp(buff[k], "f ", 2) != 0)
		k++;
	if (!buff[k] || ft_memcmp(buff[k], "f ", 2) != 0)
		return (0);
	i = k;
	k = 0;
	while (buff[k] && (ft_memcmp(buff[k], "f ", 2) != 0 || k == i))
		k++;
	if (buff[k])
		return (error_msg(14, k + 1));
	k = 1;
	while ((buff[i][k] >= 9 && buff[i][k] <= 13) || buff[i][k] == 32)
		k++;
	if (buff[i][k] == 'r' || buff[i][k] == 'g' || buff[i][k] == 'b' || \
		buff[i][k] == 'n' || buff[i][k] == 'p')
		p->filter = buff[i][k];
	else
		return (error_msg(15, i + 1));
	return (0);
}
