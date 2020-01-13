#include "includes/minirt.h"

void	rot_p_z(t_vector *axes, double val)
{
	if (axes->x < 0)
		axes->y += val;
	else
		axes->y -= val;
	if (axes->y < 0)
		axes->x -= val;
	else
		axes->x += val;
	axes->y = (axes->y < -1) ? -1 : axes->y;
	axes->y = (axes->y > 1) ? 1 : axes->y;
	axes->x = (axes->x < -1) ? -1 : axes->x;
	axes->x = (axes->x > 1) ? 1 : axes->x;
}

void	rot_p_x(t_vector *axes, double val)
{
	if (axes->z < 0)
		axes->y -= val;
	else
		axes->y += val;
	if (axes->y < 0)
		axes->z += val;
	else
		axes->z -= val;
	axes->y = (axes->y < -1) ? -1 : axes->y;
	axes->y = (axes->y > 1) ? 1 : axes->y;
	axes->z = (axes->z < -1) ? -1 : axes->z;
	axes->z = (axes->z > 1) ? 1 : axes->z;
}

void	rot_p_y(t_vector *axes, double val)
{
	if (axes->z < 0)
		axes->x += val;
	else
		axes->x -= val;
	if (axes->x < 0)
		axes->z -= val;
	else
		axes->z += val;
	axes->z = (axes->z < -1) ? -1 : axes->z;
	axes->z = (axes->z > 1) ? 1 : axes->z;
	axes->x = (axes->x < -1) ? -1 : axes->x;
	axes->x = (axes->x > 1) ? 1 : axes->x;
}

void	rot_p(t_vector *axes, double val, int axis)
{
	if (axis == 2)
		rot_p_z(axes, val);
	else if (axis == 0)
		rot_p_x(axes, val);
	else
		rot_p_y(axes, val);
}
