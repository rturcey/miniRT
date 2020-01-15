#include "minirt.h"

void	create_pyramid(t_object *obj, t_p *p)
{
	t_vector	c;

	create_square(obj);
	c = utd_v(0, obj->rayon, 0);
	c = add_v(obj->origin, rot_xyz(c, obj->rot));
	p->o[p->count + 1] = p->o[p->count];
	p->o[p->count + 1].origin = c;
	p->o[p->count + 1].composed = 1;
	p->o[p->count + 1].s1 = obj->o1;
	p->o[p->count + 1].s2 = obj->s1;
	p->o[p->count + 2] = p->o[p->count + 1];
	p->o[p->count + 2].s1 = obj->s1;
	p->o[p->count + 2].s2 = obj->o2;
	p->o[p->count + 3] = p->o[p->count + 1];
	p->o[p->count + 3].s1 = obj->o2;
	p->o[p->count + 3].s2 = obj->s2;
	p->o[p->count + 4] = p->o[p->count + 1];
	p->o[p->count + 4].s1 = obj->s2;
	p->o[p->count + 4].s2 = obj->o1;
}

void	create_square_fb(t_object *o)
{
	o->o1 = add_v(o->origin, rot_xyz(utd_v(0, -o->h / 2, o->h / 2), o->rot));
	o->o2 = add_v(o->origin, rot_xyz(utd_v(0, o->h / 2, -o->h / 2), o->rot));
	o->s1 = add_v(o->origin, rot_xyz(utd_v(0, o->h / 2, o->h / 2), o->rot));
	o->s2 = add_v(o->origin, rot_xyz(utd_v(0, -o->h / 2, -o->h / 2), o->rot));
}

void	create_square_lr(t_object *o)
{
	o->o1 = add_v(o->origin, rot_xyz(utd_v(-o->h / 2, -o->h / 2, 0), o->rot));
	o->o2 = add_v(o->origin, rot_xyz(utd_v(o->h / 2, o->h / 2, 0), o->rot));
	o->s1 = add_v(o->origin, rot_xyz(utd_v(-o->h / 2, o->h / 2, 0), o->rot));
	o->s2 = add_v(o->origin, rot_xyz(utd_v(o->h / 2, -o->h / 2, 0), o->rot));
}

void	create_cube(t_object *o, t_p *p)
{
	p->o[p->count].origin = add_v(o->origin, rot_xyz(utd_v(0, -o->h / 2, 0), o->rot));
	create_square(o);
	p->o[p->count].composed = 1;
	p->o[p->count + 1] = p->o[p->count];
	p->o[p->count + 1].origin = add_v(o->origin, rot_xyz(utd_v(0, o->h / 2, 0), o->rot));
	create_square(&p->o[p->count + 1]);
	p->o[p->count + 2] = p->o[p->count];
	p->o[p->count + 2].origin = add_v(o->origin, rot_xyz(utd_v(0, o->h / 2, 0), o->rot));
	create_square_fb(&p->o[p->count + 2]);
	p->o[p->count + 3] = p->o[p->count];
	p->o[p->count + 3].origin = add_v(o->origin, rot_xyz(utd_v(0, o->h / 2, 0), o->rot));
	create_square_fb(&p->o[p->count + 3]);
	p->o[p->count + 4] = p->o[p->count];
	p->o[p->count + 4].origin = add_v(o->origin, rot_xyz(utd_v(0, 0, o->h / 2), o->rot));
	create_square_lr(&p->o[p->count + 4]);
	p->o[p->count + 5] = p->o[p->count];
	p->o[p->count + 5].origin = add_v(o->origin, rot_xyz(utd_v(0, 0, -o->h / 2), o->rot));
	create_square_lr(&p->o[p->count + 5]);
}