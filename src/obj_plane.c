/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_plane.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaarine <jsaarine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 16:24:39 by jsaarine          #+#    #+#             */
/*   Updated: 2022/08/19 18:04:05 by jsaarine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec3.h"
#include "objects.h"
//#include <math.h>
#include <stdio.h>

t_object plane_new(t_vec3 plane_loc, t_vec3 rot, int r, int g, int b)
{
	t_object	s;

	s.r = r;
	s.g = g;
	s.b = b;
	s.loc = plane_loc;
	s.rot = rot;
	s.type = PLANE;
	return (s);
}
// get_normal(SPHERES[ctx->cam.closest_id].loc, ctx->ray, ctx->cam.closest_hit);
//*normal = vec3_unit( vec3_sub( vec3_add(ray->orig, vec3_scalar_mult(ray->dir, distance_to_intersection)), sphere->loc ) );

t_vec3 get_plane_normal(t_object plane, t_ray ray, double *distance)
{
	(void) distance;
	if (vec3_dot(plane.rot, ray.dir) < 0)
		return (plane.rot);
	return (vec3_neg(plane.rot));
}


int	intersects_plane(t_ray *ray, t_object plane, double *distance, int debug)
{
	double	N_dot_cam_to_plane;
	double	N_dot_raydir;

	if (debug)
	{}

	plane.rot = get_plane_normal(plane, *ray, distance);
	plane.rot = vec3_unit(plane.rot);
	ray->dir = vec3_unit(ray->dir);
	
	N_dot_raydir = vec3_dot(plane.rot, ray->dir);
	if (N_dot_raydir < 0.001)
		return (0);
	N_dot_cam_to_plane = vec3_dot(plane.rot, vec3_sub(ray->orig, plane.loc));
	if (N_dot_cam_to_plane < 0.001)
		return (0);
	
	
	*distance = - N_dot_raydir / N_dot_cam_to_plane;
	printf("plane intersect? \n");

	return (1);
}

/*
t_bool	intersect_plane(t_v3 ray_dir, t_v3 ray_start, t_object *obj, t_t2 *res)
{
	t_v3	ray_obj;
	float	numerator;
	float	denominator;

	vec_normalize(&obj->dir);
	ray_obj = vec_sub(ray_start, obj->pos);
	numerator = vec_dot(ray_obj, obj->dir);
	denominator = vec_dot(ray_dir, obj->dir);
	if ((denominator < 0 && numerator > 0)
		|| (denominator > 0 && numerator < 0))
	{
		res->t0 = -numerator / denominator;
		res->t1 = -1;
		return (rt_true);
	}
	return (rt_false);
}

*/