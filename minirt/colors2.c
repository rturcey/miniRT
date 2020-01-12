#include "minirt.h"

t_color		*final_buffer(t_color *buffer)
{
	int	i;

	i = 0;
	while (i < g_w * g_h)
	{
		buffer[i] = final_color(g_buffer[i]);
		buffer[i].alpha = 0;
		i++;
	}
	free(g_buffer);
	return (buffer);
}

t_color_db	minmax_px(t_vector px)
{
	t_color_db	c;

	c.red = fmax(0, fmin(255, px.z)) / g_al;
	c.green = fmax(0, fmin(255, px.y)) / g_al;
	c.blue = fmax(0, fmin(255, px.x)) / g_al;
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
