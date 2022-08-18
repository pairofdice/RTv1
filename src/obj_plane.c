/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_plane.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaarine <jsaarine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 16:24:39 by jsaarine          #+#    #+#             */
/*   Updated: 2022/08/18 18:48:58 by jsaarine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec3.h"
#include "objects.h"
#include <math.h>
#include <stdio.h>

t_object plane_new(t_vec3 plane_loc, double side, int r, int g, int b)
{
	t_object	s;

	s.r = r;
	s.g = g;
	s.b = b;
	s.loc = plane_loc;
	s.size = side;
	return (s);
}
// get_normal(SPHERES[ctx->cam.closest_id].loc, ctx->ray, ctx->cam.closest_hit);
//*normal = vec3_unit( vec3_sub( vec3_add(ray->orig, vec3_scalar_mult(ray->dir, distance_to_intersection)), sphere->loc ) );

t_vec3 get_plane_normal(t_object plane, t_ray ray, double distance)
{
	return (plane.loc);
}


int	intersects_plane(t_ray ray, t_object plane, double *distance, int debug)
{
	t_vec3	result;
	double	perp;

	
	perp = vec3_dot(ray.dir, plane.rot);
	if (perp < 1e-7)

	return (1);
	
	
}