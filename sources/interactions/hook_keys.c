#include "minirt.h"

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
	else if (keycode == 116 && p->amb_int > -1)
		p->amb_int = fmin(1, p->amb_int + 0.05);
	else if (keycode == 121 && p->amb_int > -1)
		p->amb_int = fmax(0, p->amb_int - 0.05);
	return (keycode);
}

int 	key_count(int keycode, t_p *p)
{
	if (keycode == 24)
		p->count++;
	else if (keycode == 27 && p->count > 0)
		p->count--;
	else if (keycode == 8)
	{
		if (p->count >= p->nbcams)
			p->count = 0;
		p->current = p->r[p->count];
		p->fov = p->r[p->count].fov;
	}
	else if (keycode == 37)
	{
		if (p->count >= p->nblights)
			p->count = 0;
		p->current = p->l[p->count];
	}
	else if (keycode == 31)
	{
		while (p->count < p->nobjs && p->o[p->count].composed > -1)
			p->count++;
		if (p->count >= p->nobjs)
			p->count = 0;
		p->current = p->o[p->count];
	}
	return (keycode);
}

int 	key_normal(int keycode, void *param)
{
	t_p	*p;

	p = ((t_p *)param);
	if (keycode == 49 || (keycode >= 83 && keycode <= 88))
	{
		mlx_destroy_image(p->mlx_p, p->mlx_i);
		p->mlx_i = NULL;
		mlx_clear_window(p->mlx_p, p->mlx_w);
		make_image(p);
		mlx_put_image_to_window(p->mlx_p, p->mlx_w, p->mlx_i, 0, 0);
		return (-1);
	}
	return (keycode);
}

int 	key_hook(int keycode, void *param)
{
	t_p	*p;

	p = ((t_p *)param);
	if (keycode == 53)
		free_everything(p);
	key_count(keycode, p);
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
	if (key_normal(keycode, p) == -1)
		return (keycode);
	mlx_destroy_image(p->mlx_p, p->mlx_i);
	p->mlx_i = NULL;
	make_image_lite(p);
	mlx_put_image_to_window(p->mlx_p, p->mlx_w, p->mlx_i, 0, 0);
	printf("count = %d, curtype = %c\n", p->count, p->current.type);
	return (keycode);
}
