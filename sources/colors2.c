#include "includes/minirt.h"

t_color		*final_buffer(t_p *p)
{
	int	i;

	i = 0;
	while (i < p->w * p->h)
	{
		p->endbuffer[i] = final_color(p, p->buffer[i]);
		p->endbuffer[i].alpha = 0;
		i++;
	}
	free(p->buffer);
}

t_color_db	minmax_px(t_p *p, t_vector px)
{
	t_color_db	c;

	c.red = fmax(0, fmin(255, px.z)) / p->aa;
	c.green = fmax(0, fmin(255, px.y)) / p->aa;
	c.blue = fmax(0, fmin(255, px.x)) / p->aa;
	return (c);
}

t_color_db	minmax_px_lite(t_vector px)
{
	t_color_db	c;

	c.red = fmax(0, fmin(255, px.z));
	c.green = fmax(0, fmin(255, px.y));
	c.blue = fmax(0, fmin(255, px.x));
	return (c);
}

t_color		utd_colors(double x, double y, double z)
{
	t_color	color;

	color.red = z;
	color.green = y;
	color.blue = x;
	color.alpha = 0;
	return (color);
}
