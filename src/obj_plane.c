/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_plane.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaarine <jsaarine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 16:24:39 by jsaarine          #+#    #+#             */
/*   Updated: 2022/08/20 14:47:59 by jsaarine         ###   ########.fr       */
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

	s.r = r;
	s.g = g;
	s.b = b;
	s.loc = plane_loc;
	s.rot = vec3_unit(rot);
	s.type = PLANE;
	return (s);
}
// get_normal(SPHERES[ctx->cam.closest_id].loc, ctx->ray, ctx->cam.closest_hit);
//*normal = vec3_unit( vec3_sub( vec3_add(ray->orig, vec3_scalar_mult(ray->dir, distance_to_intersection)), sphere->loc ) );

t_vec3 get_plane_normal(t_object plane, t_ray ray, double *distance)
{
	if (distance)
	{}
	if (vec3_dot(plane.rot, ray.dir) < 0)
		return (plane.rot);
	return (vec3_neg(plane.rot));
}


int	intersects_plane(t_ray *ray, t_object plane, double *distance, int debug)
{
	/* double	pn_dot_pc;
	double	pn_dot_rloc;
	double	pn_dot_rdir;


	pn_dot_rdir = vec3_dot(plane.rot, vec3_unit(ray->dir));
	if (fabs(pn_dot_rdir) < 1e-8)
		return (0);
	pn_dot_pc = vec3_dot(plane.rot, plane.loc);
	pn_dot_rloc = vec3_dot(plane.rot, ray->orig);
	*distance = (pn_dot_pc - pn_dot_rloc) / pn_dot_rdir;
	return (1); */

	if (debug)
	{}
	t_vec3	ray_obj;
	float	numerator;
	float	denominator;

	//vec3_unit(plane.rot);
	ray_obj = vec3_sub(ray->orig, plane.loc);
	numerator = vec3_dot(ray_obj, plane.rot);
	denominator = vec3_dot(ray->dir, plane.rot);
	if ((denominator < 0 && numerator > 0)
		|| (denominator > 0 && numerator < 0))
	{
		*distance = -numerator / denominator;
		return (1);
	}
	return (0);
}
/*
Po = plane origin
Lo = Line origin
n - the planes normal ray
Po = single point on the plane
L = the vector that represents the ray I am shooting
Lo = a point on the line
d = dot(Po-Lo,N)/dot(L,N)
*/
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
