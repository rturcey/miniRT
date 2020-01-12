#include "minirt.h"

void	add_range(double *r, double d)
{
	if (*r + d > 1)
		*r = -1;
	else if (*r + d < -1)
		*r = 1;
	else
		*r += d;
}

void	key_rotation(int keycode)
{
	int	tmp;
	int	l;

	tmp = g_nobjs;
	l = 0;
	if (g_current->type != 'q' && g_current->type != 'r')
		return ;
	if (keycode == 13 && (l = 1))
		add_range(&g_current->rot.x, 0.05);
	else if (keycode == 1 && (l = 1))
		add_range(&g_current->rot.x, -0.05);
	else if (keycode == 0 && (l = 1))
		add_range(&g_current->rot.y, 0.05);
	else if (keycode == 2 && (l = 1))
		add_range(&g_current->rot.y, -0.05);
	else if (keycode == 12 && (l = 1))
		add_range(&g_current->rot.z, 0.05);
	else if (keycode == 14 && (l = 1))
		add_range(&g_current->rot.z, -0.05);
	g_nobjs = g_current->nobjs;
	if (g_current->type == 'q' && g_current->composed > -2 && l == 1)
		init_square(g_current->origin, g_current->rot, g_current->h, g_current->effect);
	else if (g_current->type == 'q' && g_current->composed == -2 && l == 1)
		init_cube(g_current->center, g_current->rot, g_current->h, g_current->effect);
	else if (g_current->type == 'q' && g_current->composed == -3 && l == 1)
	{
		init_square(g_current->origin, g_current->rot, g_current->h, g_current->effect);
		init_pyramid(g_o[g_nobjs - 1], g_o[g_nobjs - 1].s, g_current->effect);
	}
	g_nobjs = tmp;
}

void	key_rotation_bis(int keycode)
{
	int	tmp;
	int	l;

	tmp = g_nobjs;
	l = 0;
	if (g_current->type != 'c' && g_current->type != 'p' && g_current->type != 'o')
		return ;
	if (keycode == 13 && (l = 1))
		rot_p(&g_current->rot, 0.1, 0);
	else if (keycode == 1 && (l = 1))
		rot_p(&g_current->rot, -0.1, 0);
	else if (keycode == 0 && (l = 1))
		rot_p(&g_current->rot, 0.1, 1);
	else if (keycode == 2 && (l = 1))
		rot_p(&g_current->rot, -0.1, 1);
	else if (keycode == 12 && (l = 1))
		rot_p(&g_current->rot, 0.1, 2);
	else if (keycode == 14 && (l = 1))
		rot_p(&g_current->rot, -0.1, 2);
	g_nobjs = g_current->nobjs;
	if (g_current->type == 'c' && l == 1)
		init_cylinder(g_current->origin, g_current->rot, g_current->h, g_current->rayon, g_current->effect);
	if (g_current->type == 'o' && l == 1)
		init_cone(g_current->origin, g_current->rot, g_current->h, g_current->rayon, g_current->effect);
	g_nobjs = tmp;
}

void	key_translation(int keycode)
{
	int			tmp;
	int			l;
	t_vector	temp;

	tmp = g_nobjs;
	l = 0;
	if (g_current->type == 'q' && g_current->composed == -2)
		g_current->origin = g_current->center;
	if (keycode == 126 && (l = 1))
		g_current->origin.y += 20;
	else if (keycode == 125 && (l = 1))
		g_current->origin.y -= 20;
	else if (keycode == 123 && (l = 1))
		g_current->origin.x -= 20;
	else if (keycode == 124 && (l = 1))
		g_current->origin.x += 20;
	else if (keycode == 78 && (l = 1))
		g_current->origin.z += 20;
	else if (keycode == 69 && (l = 1))
		g_current->origin.z -= 20;
	g_nobjs = g_current->nobjs;
	if (g_current->type == 'q' && g_current->composed > -2 && l == 1)
		init_square(g_current->origin, g_current->rot, g_current->h, g_current->effect);
	else if (g_current->type == 'q' && g_current->composed == -2 && l == 1)
		init_cube(g_current->origin, g_current->rot, g_current->h, g_current->effect);
	else if (g_current->type == 'q' && g_current->composed == -3 && l == 1)
	{
		init_square(g_current->origin, g_current->rot, g_current->h, g_current->effect);
		init_pyramid(g_o[g_nobjs - 1], g_o[g_nobjs - 1].s, g_current->effect);
	}
	else if (g_current->type == 'c' && l == 1)
		init_cylinder(g_current->origin, g_current->rot, g_current->h, g_current->rayon, g_current->effect);
	else if (g_current->type == 'o' && l == 1)
		init_cone(g_current->origin, g_current->rot, g_current->h, g_current->rayon, g_current->effect);
	else if (g_current->type == 't' && l == 1)
	{
		temp = min_v(g_current->origin, g_current->true_origin);
		g_current->s1 = add_v(g_current->s1, temp);
		g_current->s2 = add_v(g_current->s2, temp);
		init_triangle(g_current->origin, g_current->s1, g_current->s2, g_current->effect);
	}
	g_nobjs = tmp;
}

void	key_attribute(int keycode)
{
	int			tmp;
	int			l;
	double		add;
	double 		addb;

	tmp = g_nobjs;
	l = 0;
	add = 0;
	addb = 0;
	if (g_current->type == 'q' && g_current->composed == -2)
		g_current->origin = g_current->center;
	if (keycode == 30 && (l = 1))
		add = 5;
	else if (keycode == 33 && (l = 1))
		add = -5;
	else if (keycode == 39 && (l = 1))
		addb = 5;
	else if (keycode == 41 && (l = 1))
		addb = -5;
	g_nobjs = g_current->nobjs;
	if (g_current->type == 'q' && g_current->composed > -2 && l == 1)
		init_square(g_current->origin, g_current->rot, g_current->h + add, g_current->effect);
	else if (g_current->type == 'q' && g_current->composed == -2 && l == 1)
		init_cube(g_current->origin, g_current->rot, g_current->h + add, g_current->effect);
	else if (g_current->type == 'q' && g_current->composed == -3 && l == 1)
	{
		init_square(g_current->origin, g_current->rot, g_current->h + add, g_current->effect);
		init_pyramid(g_o[g_nobjs - 1], g_o[g_nobjs - 1].s + addb, g_current->effect);
	}
	else if (g_current->type == 'c' && l == 1)
		init_cylinder(g_current->origin, g_current->rot, g_current->h + add, g_current->rayon + addb, g_current->effect);
	else if (g_current->type == 'o' && l == 1)
		init_cone(g_current->origin, g_current->rot, g_current->h + add, g_current->rayon + addb, g_current->effect);
	else if (g_current->type == 's' && l == 1)
		init_sphere(g_current->origin, g_current->rayon + add, g_current->effect);
	g_nobjs = tmp;
}
