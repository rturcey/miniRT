/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pyracubes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rturcey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 14:45:40 by rturcey           #+#    #+#             */
/*   Updated: 2020/01/15 14:45:41 by rturcey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	create_pyramid(t_object *obj, t_p *p)
{
	t_vector	c;

	obj->o = add_v(obj->ctr, rotv(utd_v(0, -obj->rayon / 2, 0), obj->rot));
	create_square(obj);
	c = utd_v(0, obj->rayon / 2, 0);
	c = add_v(obj->ctr, rotv(c, obj->rot));
	p->o[p->ct].cp = -3;
	p->o[p->ct + 1] = p->o[p->ct];
	p->o[p->ct + 1].o = c;
	p->o[p->ct + 1].cp = 1;
	p->o[p->ct + 1].s1 = obj->o1;
	p->o[p->ct + 1].s2 = obj->s1;
	p->o[p->ct + 1].t = 't';
	p->o[p->ct + 2] = p->o[p->ct + 1];
	p->o[p->ct + 2].s1 = obj->s1;
	p->o[p->ct + 2].s2 = obj->o2;
	p->o[p->ct + 2].t = 't';
	p->o[p->ct + 3] = p->o[p->ct + 1];
	p->o[p->ct + 3].s1 = obj->o2;
	p->o[p->ct + 3].s2 = obj->s2;
	p->o[p->ct + 3].t = 't';
	p->o[p->ct + 4] = p->o[p->ct + 1];
	p->o[p->ct + 4].s1 = obj->s2;
	p->o[p->ct + 4].s2 = obj->o1;
	p->o[p->ct + 4].t = 't';
}

void	create_square_fb(t_object *o)
{
	o->o1 = add_v(o->o, rotv(utd_v(0, -o->h / 2, o->h / 2), o->rot));
	o->o2 = add_v(o->o, rotv(utd_v(0, o->h / 2, -o->h / 2), o->rot));
	o->s1 = add_v(o->o, rotv(utd_v(0, o->h / 2, o->h / 2), o->rot));
	o->s2 = add_v(o->o, rotv(utd_v(0, -o->h / 2, -o->h / 2), o->rot));
}

void	create_square_lr(t_object *o)
{
	o->o1 = add_v(o->o, rotv(utd_v(-o->h / 2, -o->h / 2, 0), o->rot));
	o->o2 = add_v(o->o, rotv(utd_v(o->h / 2, o->h / 2, 0), o->rot));
	o->s1 = add_v(o->o, rotv(utd_v(-o->h / 2, o->h / 2, 0), o->rot));
	o->s2 = add_v(o->o, rotv(utd_v(o->h / 2, -o->h / 2, 0), o->rot));
}

void	create_cube(t_object *o, t_p *p)
{
	o->ctr = o->o;
	o->o = add_v(o->ctr, rotv(utd_v(0, -o->h / 2, 0), o->rot));
	create_square(o);
	o->cp = -2;
	p->o[p->ct + 1] = *o;
	p->o[p->ct + 1].cp = 1;
	p->o[p->ct + 1].o = add_v(o->ctr, rotv(utd_v(0, o->h / 2, 0), o->rot));
	create_square(&p->o[p->ct + 1]);
	p->o[p->ct + 2] = *o;
	p->o[p->ct + 2].cp = 1;
	p->o[p->ct + 2].o = add_v(o->ctr, rotv(utd_v(o->h / 2, 0, 0), o->rot));
	create_square_fb(&p->o[p->ct + 2]);
	p->o[p->ct + 3] = *o;
	p->o[p->ct + 3].cp = 1;
	p->o[p->ct + 3].o = add_v(o->ctr, rotv(utd_v(-o->h / 2, 0, 0), o->rot));
	create_square_fb(&p->o[p->ct + 3]);
	p->o[p->ct + 4] = *o;
	p->o[p->ct + 4].cp = 1;
	p->o[p->ct + 4].o = add_v(o->ctr, rotv(utd_v(0, 0, o->h / 2), o->rot));
	create_square_lr(&p->o[p->ct + 4]);
	p->o[p->ct + 5] = *o;
	p->o[p->ct + 5].cp = 1;
	p->o[p->ct + 5].o = add_v(o->ctr, rotv(utd_v(0, 0, -o->h / 2), o->rot));
	create_square_lr(&p->o[p->ct + 5]);
}
