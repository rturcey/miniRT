#include "minirt.h"

int 	motion_hook(int x, int y, void *param)
{
	t_p	*p;

	p = ((t_p *)param);
	if (p->mouse < 0)
		return (-1);
	if (p->current.type != 'r')
		p->current = p->r[0];
	if (x > p->w / 3 && x < p->w / 2)
		add_range(&p->current.rot.y, -0.01 * p->mouse);
	else if (x < p->w / 2 / 3)
		add_range(&p->current.rot.y, 0.01 * p->mouse);
	if (y > p->h / 3 && y < p->h / 2)
		add_range(&p->current.rot.x, -0.01 * p->mouse);
	else if (y < p->h / 2 / 3)
		add_range(&p->current.rot.x, 0.01 * p->mouse);
	mlx_destroy_image(p->mlx_p, p->mlx_i);
	p->mlx_i = NULL;
	make_image_lite(p);
	mlx_put_image_to_window(p->mlx_p, p->mlx_w, p->mlx_i, 0, 0);
	return (0);
}

int		motion_close(void *param)
{
	t_p	*p;

	p = ((t_p *)param);
	free_everything(p);
	return (0);
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
	p->mlx_i = NULL;
	make_image_lite(p);
	mlx_put_image_to_window(p->mlx_p, p->mlx_w, p->mlx_i, 0, 0);
	return (button);
}
