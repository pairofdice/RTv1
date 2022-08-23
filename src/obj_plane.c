/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_plane.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaarine <jsaarine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 16:24:39 by jsaarine          #+#    #+#             */
/*   Updated: 2022/08/23 14:48:05 by jsaarine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/vec3.h"
#include "../inc/objects.h"
//#include <math.h>
#include <math.h>
#include <stdio.h>

t_object plane_new(t_vec3 plane_loc, t_vec3 rot, int r, int g, int b)
{
	t_object	s;
	t_vec3 c;


	s.r = r;
	s.g = g;
	s.b = b;
	s.loc = plane_loc;
	s.rot = vec3_unit(rot);
	s.type = PLANE;
	s.size = 1;
	c = s.rot;
	printf("In plane_new, normal is: %f %f %f \n ", c.x, c.y, c.z);
	return (s);
}

t_vec3 get_plane_normal(t_object plane, t_ray ray)
{
	t_vec3	normal;
	
	if (vec3_dot(plane.rot, ray.dir) > 0)
		normal = plane.rot;
	else
		normal = vec3_neg(plane.rot);
	return (normal);
}

/*
Ray and plane intersection
T = Taso, plane.loc
N = Plane normal, plane.rot
P = A point on the plane
R = ray with a start position, R.p, and a direction, R.d.

N • (P - T) = 0
N • P - N • T = 0
and
P = R.p + t * R.d
so
N • (R.p + t * R.d) - N • T = 0
N • (R.p + t * R.d) = N • T
N • R.p + t * (N • R.d) = N • T
t * (N • R.d) = N • T - N • R.p
t = (N • T - N • R.p) /  (N • R.d) 
t = (N • (T - R.p)) /  (N • R.d)
*/
int	intersects_plane(t_ray *ray, t_object *plane, double *distance)
{
	double	normal_dot_raydir;
	double	normal_dot_tr;
	t_vec3	tr;

	normal_dot_raydir = vec3_dot(plane->rot, ray->dir);
	if (normal_dot_raydir < EPSILON)
		return (0);
	tr = vec3_sub(plane->loc, ray->orig);
	normal_dot_tr = vec3_dot(plane->rot, tr);
	if (normal_dot_tr < EPSILON)
		return (0);
	*distance = normal_dot_tr / normal_dot_raydir;
	return (1);
}
