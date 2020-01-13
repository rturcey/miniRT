#include "minirt.h"

double		scal_v(t_vector v1, t_vector v2)
{
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

double		norm_v(t_vector v)
{
	return (v.x * v.x + v.y * v.y + v.z * v.z);
}

t_vector	normed(t_vector v)
{
	t_vector	result;
	double		norm;

	norm = sqrt(norm_v(v));
	if (norm <= 0)
		return (utd_v(0, 0, 0));
	result.x = v.x / norm;
	result.y = v.y / norm;
	result.z = v.z / norm;
	return (result);
}

t_vector	cross_v(t_vector v1, t_vector v2)
{
	t_vector	v;

	v.x = (v1.y * v2.z) - (v1.z * v2.y);
	v.y = (v1.z * v2.x) - (v1.x * v2.z);
	v.z = (v1.x * v2.y) - (v1.y * v2.x);
	return (v);
}

t_vector	div_each_v(t_vector v1, t_vector v2)
{
	t_vector	v3;

	v3.x = v1.x / v2.x;
	v3.y = v1.y / v2.y;
	v3.z = v1.z / v2.z;
	return (v3);
}
