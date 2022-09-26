/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_rotate.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaarine <jsaarine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 16:14:47 by jsaarine          #+#    #+#             */
/*   Updated: 2022/09/26 15:18:29 by jsaarine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/RTv1.h"

static void	gg_vec_rotate_x(t_vec3 *v, double deg)
{
	t_vec3	temp;
	double	rad;

	rad = to_radians(deg);
	printf("x rads: %f\n", rad);
	temp.z = v->z;
	temp.y = v->y;
	v->z = temp.z * cos(rad) - temp.y * sin(rad);
	v->y = temp.z * sin(rad) + temp.y * cos(rad);
}

static void	gg_vec_rotate_y(t_vec3 *v, double deg)
{
	t_vec3	temp;
	double	rad;

	rad = to_radians(deg);
	printf("y rads: %f\n", rad);
	temp.x = v->x;
	temp.z = v->z;
	v->x = temp.x * cos(rad) - temp.z * sin(rad);
	v->z = temp.x * sin(rad) + temp.z * cos(rad);
}

static void	gg_vec_rotate_z(t_vec3 *v, double deg)
{
	t_vec3	temp;
	double	rad;

	rad = to_radians(deg);
	printf("z dir z rads: %f\n", rad);
	temp.y = v->y;
	temp.x = v->x;
	v->y = temp.y * cos(rad) - temp.x * sin(rad);
	v->x = temp.y * sin(rad) + temp.x * cos(rad);
}

t_vec3	vec3_rotate(t_vec3 dir, t_vec3 rot)
{
	t_vec3	result;

	result = dir;
	gg_vec_rotate_x(&result, rot.x);
	gg_vec_rotate_y(&result, rot.y);
	gg_vec_rotate_z(&result, rot.z);
	return (result);
}
/*

void	vec_rotate_x(t_v3 *vec, float rad)
{
	t_v3	temp;

	temp.z = vec->z;
	temp.y = vec->y;
	vec->z = temp.z * cos(rad) - temp.y * sin(rad);
	vec->y = temp.z * sin(rad) + temp.y * cos(rad);
}

t_v3	vec_rotate_xyz(t_v3 vec, t_v3 rot)
{
	t_v3	res;

	res = vec;
	vec_rotate_x(&res, to_radians(rot.x));
	vec_rotate_y(&res, to_radians(rot.y));
	vec_rotate_z(&res, to_radians(rot.z));
	return (res);
}
 */
