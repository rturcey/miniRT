#include "includes/minirt.h"

void	add_range(double *r, double d)
{
	if (*r + d > 1)
		*r = -1;
	else if (*r + d < -1)
		*r = 1;
	else
		*r += d;
}

void	key_rotation(int keycode, t_p *p)
{
	int	l;

	l = 0;
	if (p->current->type != 'q' && p->current->type != 'r')
		return ;
	if (keycode == 13 && (l = 1))
		add_range(&p->current->rot.x, 0.05);
	else if (keycode == 1 && (l = 1))
		add_range(&p->current->rot.x, -0.05);
	else if (keycode == 0 && (l = 1))
		add_range(&p->current->rot.y, 0.05);
	else if (keycode == 2 && (l = 1))
		add_range(&p->current->rot.y, -0.05);
	else if (keycode == 12 && (l = 1))
		add_range(&p->current->rot.z, 0.05);
	else if (keycode == 14 && (l = 1))
		add_range(&p->current->rot.z, -0.05);
	if (p->current->type == 'q' && p->current->composed > -2 && l == 1)
		create_square(p->current);
	else if (p->current->type == 'q' && p->current->composed == -2 && l == 1)
		create_cube(p->current, p);
	else if (p->current->type == 'q' && p->current->composed == -3 && l == 1)
		create_pyramid(p->current, p);
}

void	key_rotation_bis(int keycode, t_p *p)
{
	int	l;

	l = 0;
	if (p->current->type != 'c' && p->current->type != 'p' && p->current->type != 'o')
		return ;
	if (keycode == 13 && (l = 1))
		rot_p(&p->current->rot, 0.1, 0);
	else if (keycode == 1 && (l = 1))
		rot_p(&p->current->rot, -0.1, 0);
	else if (keycode == 0 && (l = 1))
		rot_p(&p->current->rot, 0.1, 1);
	else if (keycode == 2 && (l = 1))
		rot_p(&p->current->rot, -0.1, 1);
	else if (keycode == 12 && (l = 1))
		rot_p(&p->current->rot, 0.1, 2);
	else if (keycode == 14 && (l = 1))
		rot_p(&p->current->rot, -0.1, 2);
	if (p->current->type == 'c' && l == 1)
		create_cylinder(p->current);
}

void	key_translation(int keycode, t_p *p)
{
	int			tmp;
	int			l;
	t_vector	temp;

	l = 0;
	if (p->current->type == 'q' && p->current->composed == -2)
		p->current->origin = p->current->center;
	if (keycode == 126 && (l = 1))
		p->current->origin.y += 20;
	else if (keycode == 125 && (l = 1))
		p->current->origin.y -= 20;
	else if (keycode == 123 && (l = 1))
		p->current->origin.x -= 20;
	else if (keycode == 124 && (l = 1))
		p->current->origin.x += 20;
	else if (keycode == 78 && (l = 1))
		p->current->origin.z += 20;
	else if (keycode == 69 && (l = 1))
		p->current->origin.z -= 20;
	if (p->current->type == 'q' && p->current->composed > -2 && l == 1)
		create_square(p->current);
	else if (p->current->type == 'q' && p->current->composed == -2 && l == 1)
		create_cube(p->current, p);
	else if (p->current->type == 'q' && p->current->composed == -3 && l == 1)
		create_pyramid(p->current, p);
	else if (p->current->type == 'c' && l == 1)
		create_cylinder(p->current, p);
	else if (p->current->type == 't' && l == 1)
	{
		temp = min_v(p->current->origin, p->current->true_origin);
		p->current->s1 = add_v(p->current->s1, temp);
		p->current->s2 = add_v(p->current->s2, temp);
	}
}

void	key_attribute(int keycode, t_p *p)
{
	int			l;

	l = 0;
	if (p->current->type == 'q' && p->current->composed == -2)
		p->current->origin = p->current->center;
	if (keycode == 30 && (l = 1))
		p->current->h += 5;
	else if (keycode == 33 && (l = 1))
		p->current->h -= 5;
	else if (keycode == 39 && (l = 1))
		p->current->rayon += 5;
	else if (keycode == 41 && (l = 1))
		p->current->rayon += -5;
	if (p->current->type == 'q' && p->current->composed > -2 && l == 1)
		create_square(p->current);
	else if (p->current->type == 'q' && p->current->composed == -2 && l == 1)
		create_cube(p->current, p);
	else if (p->current->type == 'q' && p->current->composed == -3 && l == 1)
		create_pyramid(p->current, p);
	else if (p->current->type == 'c' && l == 1)
		create_cylinder(p->current, p);
}
