#include "minirt.h"

int		key_effects(int keycode)
{
	if (keycode >= 83 && keycode <= 88)
		g_al = pow(keycode - 82, 2);
	if (keycode == 15)
		g_filter = (g_filter == 'r') ? '\0' : 'r';
	else if (keycode == 5)
		g_filter = (g_filter == 'g') ? '\0' : 'g';
	else if (keycode == 11)
		g_filter = (g_filter == 'b') ? '\0' : 'b';
	else if (keycode == 45)
		g_filter = (g_filter == 'n') ? '\0' : 'n';
	else if (keycode == 35)
		g_filter = (g_filter == 'p') ? '\0' : 'p';
	return (keycode);
}

int 	key_hook(int keycode, void *param)
{
	(void)param;
	if (keycode == 53)
	{
		mlx_destroy_image(g_ptr, g_image);
		mlx_destroy_window(g_ptr, g_window);
		exit(0);
	}
	if (keycode == 24)
		g_count++;
	else if (keycode == 27 && g_count > 0)
		g_count--;
	else if (keycode == 8)
	{
		g_camcount = g_count;
		if (g_camcount >= g_nbcams)
		{
			g_camcount = 0;
			g_count = 0;
		}
		g_current = &g_r[g_camcount];
	}
	else if (keycode == 37)
	{
		if (g_count >= g_nblights)
			g_count = 0;
		g_current = &g_l[g_count];
	}
	else if (keycode == 31)
	{
		while (g_o[g_count].composed > -1 && g_count <= g_nobjs)
			g_count++;
		if (g_count > g_nobjs)
			g_count = 0;
		g_current = &g_o[g_count];
	}
	else if (keycode == 116)
		g_amb = fmin(1, g_amb + 0.05);
	else if (keycode == 121)
		g_amb = fmax(0, g_amb - 0.05);
	printf("g_count = %d\n", g_count);
	printf("Current type = '%c'\n", g_current->type);
	key_rotation(keycode);
	key_rotation_bis(keycode);
	key_translation(keycode);
	key_attribute(keycode);
	key_effects(keycode);
	if (keycode == 82)
	{
		if (g_threads != 1)
			g_threads = 1;
		else
			g_threads = 8;
	}
	if (keycode == 49 || (keycode >= 83 && keycode <= 88))
	{
		mlx_destroy_image(g_ptr, g_image);
		mlx_clear_window(g_ptr, g_window);
		go_image(g_w, g_h, 70);
		printf("keycode = %d\n", keycode);
		return (keycode);
	}
	mlx_destroy_image(g_ptr, g_image);
	mlx_clear_window(g_ptr, g_window);
	go_image_lite(g_w, g_h, 70);
	printf("keycode = %d\n", keycode);
	return (keycode);
}

int 	motion_hook(int x, int y, void *param)
{
	(void)param;
	if (g_mouse < 0)
		return (-1);
	if (x > g_w / 3 && x < g_w / 2)
		add_range(&g_r[g_camcount].rot.y, -0.01 * g_mouse);
	else if (x < g_w / 2 / 3)
		add_range(&g_r[g_camcount].rot.y, 0.01 * g_mouse);
	if (y > g_h / 3 && y < g_h / 2)
		add_range(&g_r[g_camcount].rot.x, -0.01 * g_mouse);
	else if (y < g_h / 2 / 3)
		add_range(&g_r[g_camcount].rot.x, 0.01 * g_mouse);
	mlx_destroy_image(g_ptr, g_image);
	go_image_lite(g_w, g_h, 70);
	return (0);
}

int		motion_close(void *param)
{
	(void)param;
	mlx_destroy_image(g_ptr, g_image);
	mlx_destroy_window(g_ptr, g_window);
	exit(0);
}

int		mouse_hook(int button, int x, int y, void *param)
{
	double	d;

	d = 0;
	(void)param;
	if (button == 4)
		g_r[g_camcount].origin.z -= 20;
	else if (button == 5)
		g_r[g_camcount].origin.z += 20;
	else if (button == 3)
		g_mouse *= -1;
	else if (button == 1 && g_mouse > 0)
		g_mouse++;
	else if (button == 2 && g_mouse > 1)
		g_mouse--;
	printf("button = %d, x = %d, y = %d\n", button, x, y);
	mlx_destroy_image(g_ptr, g_image);
	go_image_lite(g_w, g_h, 70);
	return (button);
}
