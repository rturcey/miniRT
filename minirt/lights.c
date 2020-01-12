#include "minirt.h"

void	init_light(t_vector origin, t_color_db color, double intensity)
{
	t_object	l;

	l.origin = origin;
	l.intensity = intensity * 100;
	l.color = color;
	l.type = 'l';
	g_l[g_nblights++] = l;
}
