/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_plane.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaarine <jsaarine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 16:24:39 by jsaarine          #+#    #+#             */
/*   Updated: 2022/09/08 18:51:41 by jsaarine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/vec3.h"
#include "../inc/objects.h"
//#include <math.h>
#include <math.h>
#include <stdio.h>

t_object	plane_new(t_vec3 plane_loc, t_vec3 rot, int r, int g, int b) 
{
	// fix rgb with maybe union, maybe struct, maybe 0xFFFFFF00(hex) colors
	t_object	s;


	s.color.x = r;
	s.color.y = g;
	s.color.z = b;
	s.loc = plane_loc;
	s.rot = vec3_unit(rot);
	s.type = PLANE;
	s.size = 1;
	return (s);
}


t_vec3	get_plane_normal(t_object plane, t_ray cam_to_plane)
{
	if (vec3_dot(plane.rot, cam_to_plane.dir) > 0)
		return (vec3_neg(plane.rot));
	return (plane.rot);
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
	tr = vec3_sub(plane->loc, ray->orig);
	normal_dot_tr = vec3_dot(plane->rot, tr);
	if ((normal_dot_tr < 0 && normal_dot_raydir > 0)
		|| (normal_dot_tr > 0 && normal_dot_raydir < 0))
		return (0);
	*distance = normal_dot_tr / normal_dot_raydir;
	return (1);
}
