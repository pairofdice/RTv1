/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_sphere.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaarine <jsaarine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 16:24:39 by jsaarine          #+#    #+#             */
/*   Updated: 2022/08/11 19:10:18 by jsaarine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec3.h"
#include "objects.h"
#include <math.h>

t_object sphere_new(double x, double y, double z, double radius)
{
	t_object	s;
	t_point		loc;

	loc.x = x;
	loc.y = y;
	loc.z = z;
	s.loc = loc;
	s.size = radius;
	return (s);
}

int	intersects_sphere(t_ray *ray, t_object *sphere, t_vec3 *normal)
{
	t_vec3	ray_origin_to_sphere;
	double	tc;
	double	d;
	double	tp;
	double	distance_to_intersection;

	ray_origin_to_sphere = vec3_sub(sphere->loc, ray->orig);
	// tc = distance along ray closest to sphere center
	tc = vec3_dot(ray_origin_to_sphere, ray->dir);
	// if tc is negative we're looking in the wrong direction
	if (tc < 0)
		return (0);
	// d = distance from sphere center to t
	d = sqrt(tc * tc - vec3_sqr(ray_origin_to_sphere));
	// if d is greater than radius of sphere there is no intersection
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
	if (distance_to_intersection < 0)
		return (0);
	;
	// sphere surface normal at intersection point, maybe shouldn't be here
	*normal = vec3_unit( vec3_sub( vec3_add(ray->orig, vec3_scalar_mult(ray->dir, distance_to_intersection)), sphere->loc ) );

	return (1);
	
	
}