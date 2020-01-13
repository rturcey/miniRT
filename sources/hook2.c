#include "includes/minirt.h"

int		key_effects(int keycode, t_p *p)
{
	if (keycode >= 83 && keycode <= 88)
		p->aa = pow(keycode - 82, 2);
	if (keycode == 15)
		p->filter = (p->filter == 'r') ? '\0' : 'r';
	else if (keycode == 5)
		p->filter = (p->filter == 'g') ? '\0' : 'g';
	else if (keycode == 11)
		p->filter = (p->filter == 'b') ? '\0' : 'b';
	else if (keycode == 45)
		p->filter = (p->filter == 'n') ? '\0' : 'n';
	else if (keycode == 35)
		p->filter = (p->filter == 'p') ? '\0' : 'p';
	return (keycode);
}

int 	key_hook(int keycode, void *param)
{
	t_p	*p;

	p = ((t_p *)param);
	if (keycode == 53)
	{
		free_everything(p, 0);
		exit(0);
	}
	if (keycode == 24)
		p->count++;
	else if (keycode == 27 && p->count > 0)
		p->count--;
	else if (keycode == 8)
	{
		if (p->count >= p->nbcams)
			p->count = 0;
		p->current = p->r[p->count];
		p->fov = p->r[p->count]->fov;
	}
	else if (keycode == 37)
	{
		if (p->count >= p->nblights)
			p->count = 0;
		p->current = &p->l[p->count];
	}
	else if (keycode == 31)
	{
		while (p->count < p->nobjs && p->o[p->count].composed > -1)
			p->count++;
		if (p->count >= p->nobjs)
			p->count = 0;
		p->current = &p->o[p->count];
	}
	else if (keycode == 116 && p->amb_int > -1)
		p->amb_int = fmin(1, p->amb_int + 0.05);
	else if (keycode == 121 && p->amb_int > -1)
		p->amb_int = fmax(0, p->amb_int - 0.05);
	printf("p->count = %d\n", p->count);
	printf("Current type = '%c'\n", p->current->type);
	key_rotation(keycode, p);
	key_rotation_bis(keycode, p);
	key_translation(keycode, p);
	key_attribute(keycode, p);
	key_effects(keycode, p);
	if (keycode == 82)
	{
		if (p->threads != 1)
			p->threads = 1;
		else
			p->threads = 8;
	}
	if (keycode == 49 || (keycode >= 83 && keycode <= 88))
	{
		mlx_destroy_image(p->mlx_p, p->mlx_i);
		mlx_clear_window(p->mlx_p, p->mlx_w);
		go_image(p->w, p->h, 70);
		printf("keycode = %d\n", keycode);
		return (keycode);
	}
	mlx_destroy_image(p->mlx_p, p->mlx_i);
	mlx_clear_window(p->mlx_p, p->mlx_w);
	go_image_lite(p->w, p->h, 70);
	printf("keycode = %d\n", keycode);
	return (keycode);
}

int 	motion_hook(int x, int y, void *param)
{
	t_p	*p;

	p = ((t_p *)param);
	if (p->mouse < 0)
		return (-1);
	if (x > p->w / 3 && x < p->w / 2)
		add_range(&p->r[p->count].rot.y, -0.01 * p->mouse);
	else if (x < p->w / 2 / 3)
		add_range(&p->r[p->count].rot.y, 0.01 * p->mouse);
	if (y > p->h / 3 && y < p->h / 2)
		add_range(&p->r[p->count].rot.x, -0.01 * p->mouse);
	else if (y < p->h / 2 / 3)
		add_range(&p->r[p->count].rot.x, 0.01 * p->mouse);
	mlx_destroy_image(p->mlx_p, p->mlx_i);
	go_image_lite(p->w, p->h, 70);
	return (0);
}

int		motion_close(void *param)
{
	t_p	*p;

	p = ((t_p *)param);
	mlx_destroy_image(p->mlx_p, p->mlx_i);
	mlx_destroy_window(p->mlx_p, p->mlx_w);
	exit(0);
}

int		mouse_hook(int button, int x, int y, void *param)
{
	t_p	*p;

	p = ((t_p *)param);
	if (button == 4)
		p->r[p->count].origin.z -= 20;
	else if (button == 5)
		p->r[p->count].origin.z += 20;
	else if (button == 3)
		p->mouse *= -1;
	else if (button == 1 && p->mouse > 0)
		p->mouse++;
	else if (button == 2 && p->mouse > 1)
		p->mouse--;
	printf("button = %d, x = %d, y = %d\n", button, x, y);
	mlx_destroy_image(p->mlx_p, p->mlx_i);
	go_image_lite(p->w, p->h, 70);
	return (button);
}
