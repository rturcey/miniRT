#include "includes/minirt.h"

t_vector	utd_v(double x, double y, double z)
{
	t_vector	vector;

	vector.x = x;
	vector.y = y;
	vector.z = z;
	return (vector);
}

t_vector	add_v(t_vector v1, t_vector v2)
{
	t_vector	result;

	result.x = v1.x + v2.x;
	result.y = v1.y + v2.y;
	result.z = v1.z + v2.z;
	return (result);
}

t_vector	min_v(t_vector v1, t_vector v2)
{
	t_vector	result;

	result.x = v1.x - v2.x;
	result.y = v1.y - v2.y;
	result.z = v1.z - v2.z;
	return (result);
}

t_vector	mult_v(double mult, t_vector v)
{
	t_vector	result;

	result.x = v.x * mult;
	result.y = v.y * mult;
	result.z = v.z * mult;
	return (result);
}

t_vector	div_v(double mult, t_vector v)
{
	t_vector	result;

	result.x = v.x / mult;
	result.y = v.y / mult;
	result.z = v.z / mult;
	return (result);
}
