/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_sphere.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaarine <jsaarine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 16:24:39 by jsaarine          #+#    #+#             */
/*   Updated: 2022/09/08 18:59:04 by jsaarine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec3.h"
#include "objects.h"
#include <math.h>
#include <stdio.h>

t_object sphere_new(t_vec3 loc, double radius, int r, int g, int b)
{
	t_object s;

	s.color.x = r;
	s.color.y = g;
	s.color.z = b;
	s.loc = loc;
	s.size = radius;
	s.type = SPHERE;
	return (s);
}
// get_normal(SPHERES[ctx->cam.closest_id].loc, ctx->ray, ctx->cam.closest_hit);
//*normal = vec3_unit( vec3_sub( vec3_add(ray->orig, vec3_scalar_mult(ray->dir, distance_to_intersection)), sphere->loc ) );

t_vec3 get_sphere_normal(t_vec3 sphere_loc, t_ray ray, double distance)
{
	t_vec3 result;

	result = vec3_scalar_mult(ray.dir, distance);
	result = vec3_add(ray.orig, result);
	result = vec3_sub(result, sphere_loc);
	result = vec3_unit(result);
	return (result);
}

int intersects_sphere(t_ray *ray, t_object *sphere, double *distance, int debug)
{
	t_vec3 ray_origin_to_sphere;
	double tc;
	double d;
	double tp;
	double distance_to_intersection;
	// t_vec3 c;

	ray_origin_to_sphere = vec3_sub(sphere->loc, ray->orig);
	
	// printf("AAAAAAAAA %f\n", sphere->r);
	// printf("AAAAAAAAA %f\n", sphere->size);
	// tc = distance along ray closest to sphere center
	tc = vec3_dot(ray_origin_to_sphere, ray->dir);
	// if tc is negative we're looking in the wrong direction
	if (tc < 0)
		return (0);
	// d = distance from sphere center to t
	d = sqrt(fabs(tc * tc - vec3_sqr(ray_origin_to_sphere)));
	// if d is greater than radius of sphere there is no intersection
	// printf("FINE?\n");
 	if (d > sphere->size)
		return (0);
		
	// we now know sphere radius and closest point to sphere center along
	// our ray, so one again pythagoras gives us the closest intersection

	// so, once again
	// tc = distance to closest point perpendicular to sphere center from ray origin
	// d = distance to ray from sphere center
	// tp = distance from d to sphere surface
	tp = sqrt(sphere->size * sphere->size - d * d);
	distance_to_intersection = tc - tp;
	// if intersection point behind projection plane
	if (debug == 1)
	{
		// c = sphere->loc;
		// printf("sphere->loc is: %f %f %f - ", c.x, c.y, c.z);
		// c = ray->dir;
		// printf("ray->dir is: %f %f %f \n", c.x, c.y, c.z);

		// c = ray_origin_to_sphere;
		/* printf("ray_origin_to_sphere is: %f %f %f \n", c.x, c.y, c.z);
		printf("tc is: %f \n", tc);
		printf("d is: %f \n", d);
		printf("tp is: %f \n", tp);
		printf("tctc is: %f \n", tc*tc);
		printf("vec3sqr is: %f \n", vec3_sqr(ray_origin_to_sphere));
		printf("tctc - vec3sqr is: %f \n", tc*tc - vec3_sqr(ray_origin_to_sphere)); */
	}
	if (distance_to_intersection < 0)
		return (0);
	*distance = distance_to_intersection;
	// sphere surface normal at intersection point, maybe shouldn't be here
	// *normal = vec3_unit( vec3_sub( vec3_add(ray->orig, vec3_scalar_mult(ray->dir, distance_to_intersection)), sphere->loc ) );

	//printf("No longer fine!\n");
	return (1);
}
