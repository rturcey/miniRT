#include "minirt.h"

void	init_cube(t_vector o, t_vector r, double h, char effect)
{
	t_vector	c;

	g_o[g_nobjs].center = o;
	c = add_v(o, rot_xyz(utd_v(0, -h / 2, 0), r));
	init_square(c, r, h, effect);
	g_o[g_nobjs - 1].composed = -2;
	g_o[g_nobjs].col = g_o[g_nobjs - 1].col;
	c = add_v(o, rot_xyz(utd_v(0, h / 2, 0), r));
	init_square(c, r, h, effect);
	g_o[g_nobjs - 1].composed = g_nobjs - 2;
	g_o[g_nobjs].col = g_o[g_nobjs - 1].col;
	c = add_v(o, rot_xyz(utd_v(-h / 2, 0, 0), r));
	init_square_fb(c, r, h, effect);
	g_o[g_nobjs].col = g_o[g_nobjs - 1].col;
	c = add_v(o, rot_xyz(utd_v(h / 2, 0, 0), r));
	init_square_fb(c, r, h, effect);
	g_o[g_nobjs].col = g_o[g_nobjs - 1].col;
	c = add_v(o, rot_xyz(utd_v(0, 0, h / 2), r));
	init_square_lr(c, r, h, effect);
	g_o[g_nobjs].col = g_o[g_nobjs - 1].col;
	c = add_v(o, rot_xyz(utd_v(0, 0, -h / 2), r));
	init_square_lr(c, r, h, effect);
}

void	init_pyramid(t_object sq, double d, char effect)
{
	t_vector	o;

	g_o[g_nobjs - 1].s = d;
	o = utd_v(0, d, 0);
	o = add_v(sq.origin, rot_xyz(o, sq.rot));
	g_o[g_nobjs - 1].composed = -3;
	g_o[g_nobjs].col = sq.col;
	g_o[g_nobjs].rb = -1;
	init_triangle(o, sq.origin1, sq.s1, effect);
	g_o[g_nobjs - 1].composed = g_nobjs - 2;
	g_o[g_nobjs].col = sq.col;
	init_triangle(o, sq.s1, sq.origin2, effect);
	g_o[g_nobjs - 1].composed = g_o[g_nobjs - 2].composed;
	g_o[g_nobjs].col = sq.col;
	init_triangle(o, sq.origin2, sq.s2, effect);
	g_o[g_nobjs - 1].composed = g_o[g_nobjs - 2].composed;
	g_o[g_nobjs].col = sq.col;
	init_triangle(o, sq.s2, sq.origin1, effect);
	g_o[g_nobjs - 1].composed = g_o[g_nobjs - 2].composed;
}

void	init_square_fb(t_vector o, t_vector r, double h, char effect)
{
	g_o[g_nobjs].origin = o;
	g_o[g_nobjs].rot = r;
	g_o[g_nobjs].origin1 = add_v(o, rot_xyz(utd_v(0, -h / 2, h / 2), r));
	g_o[g_nobjs].origin2 = add_v(o, rot_xyz(utd_v(0, h / 2, -h / 2), r));
	g_o[g_nobjs].s1 = add_v(o, rot_xyz(utd_v(0, h / 2, h / 2), r));
	g_o[g_nobjs].s2 = add_v(o, rot_xyz(utd_v(0, -h / 2, -h / 2), r));
	g_o[g_nobjs].effect = effect;
	g_o[g_nobjs].type = 'q';
	g_o[g_nobjs].composed = g_o[g_nobjs - 1].composed;
	g_o[g_nobjs].nobjs = g_nobjs;
	g_o[g_nobjs].rb = -1;
	g_nobjs++;
}

void	init_square_lr(t_vector o, t_vector r, double h, char effect)
{
	g_o[g_nobjs].origin = o;
	g_o[g_nobjs].rot = r;
	g_o[g_nobjs].origin1 = add_v(o, rot_xyz(utd_v(-h / 2, -h / 2, 0), r));
	g_o[g_nobjs].origin2 = add_v(o, rot_xyz(utd_v(h / 2, h / 2, 0), r));
	g_o[g_nobjs].s1 = add_v(o, rot_xyz(utd_v(-h / 2, h / 2, 0), r));
	g_o[g_nobjs].s2 = add_v(o, rot_xyz(utd_v(h / 2, -h / 2, 0), r));
	g_o[g_nobjs].effect = effect;
	g_o[g_nobjs].type = 'q';
	g_o[g_nobjs].composed = g_o[g_nobjs - 1].composed;
	g_o[g_nobjs].nobjs = g_nobjs;
	g_o[g_nobjs].rb = -1;
	g_nobjs++;
}
