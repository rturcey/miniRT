/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_transformations.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rturcey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 14:46:26 by rturcey           #+#    #+#             */
/*   Updated: 2020/01/15 14:46:27 by rturcey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	key_rotation(int k, t_p *p)
{
	int	l;

	l = 0;
	if (p->curr->t != 'q' && p->curr->t != 'r')
		return ;
	if (p->curr->cp <= -2 && ((k >= 0 && k <= 2) || (k >= 12 && k <= 14)))
		p->curr->o = p->curr->ctr;
	if (k == 13 && (l = 1))
		add_range(&p->curr->rot.x, 0.05);
	else if (k == 1 && (l = 1))
		add_range(&p->curr->rot.x, -0.05);
	else if (k == 0 && (l = 1))
		add_range(&p->curr->rot.y, 0.05);
	else if (k == 2 && (l = 1))
		add_range(&p->curr->rot.y, -0.05);
	else if (k == 12 && (l = 1))
		add_range(&p->curr->rot.z, 0.05);
	else if (k == 14 && (l = 1))
		add_range(&p->curr->rot.z, -0.05);
	if (p->curr->t == 'q' && p->curr->cp > -2 && l == 1)
		create_square(p->curr);
	else if (p->curr->t == 'q' && p->curr->cp == -2 && l == 1)
		create_cube(p->curr, p);
	else if (p->curr->t == 'q' && p->curr->cp == -3 && l == 1)
		create_pyramid(p->curr, p);
}

void	key_rotation_bis(int k, t_p *p)
{
	int	l;

	l = 0;
	if (p->curr->t != 'c' && p->curr->t != 'p' && p->curr->t != 'o')
		return ;
	if (k == 13 && (l = 1))
		rot_p(&p->curr->rot, 0.1, 0);
	else if (k == 1 && (l = 1))
		rot_p(&p->curr->rot, -0.1, 0);
	else if (k == 0 && (l = 1))
		rot_p(&p->curr->rot, 0.1, 1);
	else if (k == 2 && (l = 1))
		rot_p(&p->curr->rot, -0.1, 1);
	else if (k == 12 && (l = 1))
		rot_p(&p->curr->rot, 0.1, 2);
	else if (k == 14 && (l = 1))
		rot_p(&p->curr->rot, -0.1, 2);
	if (p->curr->t == 'c' && l == 1)
		create_cylinder(p->curr, p);
}

void	recreate(int k, t_p *p)
{
	if (p->curr->t == 'q' && p->curr->cp > -2)
		create_square(p->curr);
	else if (p->curr->t == 'q' && p->curr->cp == -2)
		create_cube(p->curr, p);
	else if (p->curr->t == 'q' && p->curr->cp == -3)
		create_pyramid(p->curr, p);
	else if (p->curr->t == 'c')
		create_cylinder(p->curr, p);
	else if (p->curr->t == 'l' && (k == 30 || k == 33))
	{
		p->curr->intensity -= 5;
		if (k == 30)
			p->curr->intensity += 10;
		p->curr->intensity = fmax(0, fmin(100, p->curr->intensity));
	}
	else if (p->curr->t == 'r' && (k == 30 || k == 33))
	{
		p->curr->fov -= (5 * M_PI / 180);
		if (k == 30)
			p->curr->fov += (10 * M_PI / 180);
		p->curr->fov = fmax(0, fmin(M_PI, p->curr->fov));
	}
}

void	key_translation(int k, t_p *p)
{
	int			l;

	l = 0;
	if (p->curr->cp <= -2 && ((k >= 123 && k <= 126) || k == 78 || k == 69))
		p->curr->o = p->curr->ctr;
	if (k == 126 && (l = 1))
		p->curr->o.y += 20;
	else if (k == 125 && (l = 1))
		p->curr->o.y -= 20;
	else if (k == 123 && (l = 1))
		p->curr->o.x -= 20;
	else if (k == 124 && (l = 1))
		p->curr->o.x += 20;
	else if (k == 78 && (l = 1))
		p->curr->o.z += 20;
	else if (k == 69 && (l = 1))
		p->curr->o.z -= 20;
	if (l == 1 && p->curr->t == 't')
	{
		p->curr->s1 = add_v(p->curr->s1, min_v(p->curr->o, p->curr->true_o));
		p->curr->s2 = add_v(p->curr->s2, min_v(p->curr->o, p->curr->true_o));
	}
	else if (l == 1)
		recreate(k, p);
}

void	key_attribute(int k, t_p *p)
{
	int			l;

	l = 0;
	if (p->curr->t == 'q' && p->curr->cp == -2)
		p->curr->o = p->curr->ctr;
	if (k == 30 && (l = 1))
		p->curr->h += 5;
	else if (k == 33 && (l = 1))
		p->curr->h -= 5;
	else if (k == 39 && (l = 1))
		p->curr->rayon += 5;
	else if (k == 41 && (l = 1))
		p->curr->rayon += -5;
	if (l == 1)
		recreate(k, p);
}
