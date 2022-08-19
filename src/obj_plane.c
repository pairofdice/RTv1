/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_plane.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaarine <jsaarine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 16:24:39 by jsaarine          #+#    #+#             */
/*   Updated: 2022/08/19 15:18:38 by jsaarine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec3.h"
#include "objects.h"
#include <math.h>
#include <stdio.h>

t_object plane_new(t_vec3 plane_loc, int r, int g, int b)
{
	t_object	s;

	s.r = r;
	s.g = g;
	s.b = b;
	s.loc = plane_loc;
	return (s);
}
// get_normal(SPHERES[ctx->cam.closest_id].loc, ctx->ray, ctx->cam.closest_hit);
//*normal = vec3_unit( vec3_sub( vec3_add(ray->orig, vec3_scalar_mult(ray->dir, distance_to_intersection)), sphere->loc ) );

t_vec3 get_plane_normal(t_object plane, t_ray ray, double *distance)
{
	(void) distance;
	if (vec3_dot(plane.rot, ray.dir) , 0)
		return (plane.rot);
	return (vec3_neg(plane.rot));
}


int	intersects_plane(t_ray ray, t_object plane, double *distance, int debug)
{
	double	N_dot_raydir;
	double	N_dot_plane_to_cam;

	if (debug)
	{}

	plane.rot = get_plane_normal(plane, ray, distance);
	N_dot_raydir = vec3_dot(plane.rot, ray.dir);
	if (N_dot_raydir < 1e-7)
		return (0);
	N_dot_plane_to_cam = vec3_dot(plane.rot, vec3_sub(plane.loc, ray.orig));
	
	*distance = - N_dot_raydir / N_dot_plane_to_cam;
	return (1);
}