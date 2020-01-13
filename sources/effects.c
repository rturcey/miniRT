#include "minirt.h"

void	apply_effect(t_p *par, int o_id)
{
	if (par->o[o_id].effect == 'd' || par->o[o_id].effect == 'D')
		damier(par, o_id);
	if (par->o[o_id].effect == 'r' || par->o[o_id].effect == 'R')
		rainbow(par, o_id);
	if (par->o[o_id].type == 's' && (par->o[o_id].effect == 'b' || par->o[o_id].effect == 'B'))
		par->o[o_id].col = px_mapping(par->o[o_id], par->p);
}

t_color	apply_filter(t_p *p, t_color c1)
{
	double	tmp;

	tmp = 0;
	if (p->filter == 'r' || p->filter == 'g')
		c1.blue = 0;
	if (p->filter == 'r' || p->filter == 'b')
		c1.green = 0;
	if (p->filter == 'g' || p->filter == 'b')
		c1.red = 0;
	if (p->filter == 'n')
	{
		tmp = (c1.red + c1.green + c1.blue) / 3;
		c1 = utd_colors(tmp, tmp, tmp);
	}
	if (p->filter == 'p')
	{
		tmp = c1.red + c1.green + c1.blue;
		c1.red = fmax(0, fmin(255, tmp / 3 * 1.40));
		c1.green = tmp / 3;
		c1.blue = fmax(0, fmin(255, tmp / 3 * 0.60));
	}
	return (c1);
}

void	damier(t_p *par, int o_id)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (abs((int)((par->p.x + 999) / par->o[o_id].ch)) % 2 == 0)
		i++;
	if (abs((int)((par->p.y + 999) / par->o[o_id].ch)) % 2 == 0)
		i++;
	if (abs((int)((par->p.z + 999) / par->o[o_id].ch)) % 2 == 0)
		i++;
	if (i == 1 || i == 3)
		par->o[o_id].col = par->o[o_id].col1;
	else
		par->o[o_id].col = par->o[o_id].col2;
}

void	rainbow(t_p *p, int o)
{
	if (p->aa > 1 && ++p->aarainb != 1)
	{
		if (p->aarainb == p->aa)
			p->aarainb = 0;
		return ;
	}
	if (p->o[o].rb == -1 && (p->o[o].rb = 0) == 0)
		p->o[o].col = utd_colors_object(0, 0, 255);
	if (p->o[o].rb == 0 && (p->o[o].col.y += p->o[o].rainbow) >= 255)
		p->o[o].rb = 1;
	else if (p->o[o].rb == 1 && (p->o[o].col.x -= p->o[o].rainbow) <= 0)
		p->o[o].rb = 2;
	else if (p->o[o].rb == 2 && (p->o[o].col.z += p->o[o].rainbow) >= 255)
		p->o[o].rb = 3;
	else if (p->o[o].rb == 3 && (p->o[o].col.y -= p->o[o].rainbow) <= 0)
		p->o[o].rb = 4;
	else if (p->o[o].rb == 4 && (p->o[o].col.x += p->o[o].rainbow) >= 255)
		p->o[o].rb = 5;
	else if (p->o[o].rb == 5 && (p->o[o].col.z -= p->o[o].rainbow) <= 0)
		p->o[o].rb = -1;
}
