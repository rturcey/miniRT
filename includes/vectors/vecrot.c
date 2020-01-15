/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vecrot.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rturcey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 14:48:35 by rturcey           #+#    #+#             */
/*   Updated: 2020/01/15 14:48:36 by rturcey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vector	rot_x(t_vector v, double r)
{
	t_vector	result;

	result.x = v.x;
	result.y = v.y * cos(r) - v.z * sin(r);
	result.z = v.y * sin(r) + v.z * cos(r);
	return (result);
}

t_vector	rot_y(t_vector v, double r)
{
	t_vector	result;

	result.y = v.y;
	result.x = v.x * cos(r) + v.z * sin(r);
	result.z = -v.x * sin(r) + v.z * cos(r);
	return (result);
}

t_vector	rot_z(t_vector v, double r)
{
	t_vector	result;

	result.z = v.z;
	result.x = v.x * cos(r) - v.y * sin(r);
	result.y = v.x * sin(r) + v.y * cos(r);
	return (result);
}

t_vector	rotv(t_vector v, t_vector r)
{
	t_vector	result;

	result = v;
	result = rot_x(result, r.x * M_PI);
	result = rot_y(result, r.y * M_PI);
	result = rot_z(result, r.z * M_PI);
	return (result);
}
