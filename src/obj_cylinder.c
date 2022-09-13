/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_cylinder.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaarine <jsaarine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 16:24:39 by jsaarine          #+#    #+#             */
/*   Updated: 2022/09/13 16:52:39 by jsaarine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"
#include "objects.h"
#include <stdio.h>

t_abc static calc_abc_cylinder(t_vec3 raydir, t_vec3 cyldir, t_vec3 raycyl, double radius)
{
	t_abc abc;

	abc.a = 1 - vec3_dot(raydir, cyldir) * vec3_dot(raydir, cyldir);
	abc.b = 2 * (vec3_dot(raydir, raycyl) - vec3_dot(raydir, cyldir) * vec3_dot(raycyl, cyldir));
	abc.c = vec3_dot(raycyl, raycyl) - vec3_dot(raycyl, cyldir) * vec3_dot(raycyl, cyldir) - radius * radius;
	return (abc);
}

t_object cylinder_new(t_vec3 loc, t_vec3 rot, double radius, int r, int g, int b)
{
	t_object s;

	s.color.x = r;
	s.color.y = g;
	s.color.z = b;
	s.loc = loc;
	s.size = radius;
	s.rot = vec3_unit(rot);
	s.type = CYLINDER;
	return (s);
}
// get_normal(SPHERES[ctx->cam.closest_id].loc, ctx->ray, ctx->cam.closest_hit);
//*normal = vec3_unit( vec3_sub( vec3_add(ray->orig, vec3_scalar_mult(ray->dir, distance_to_intersection)), sphere->loc ) );

t_vec3 get_cylinder_normal(t_context *ctx)
{
	t_vec3 result;
	t_vec3 hit_loc;
	t_vec3 hypotenuse;
	t_vec3 hit_along_cyldir;

	hit_loc = vec3_ray_at(ctx->ray, ctx->hit.closest_distance);
	hypotenuse = vec3_sub(hit_loc, ctx->obj.loc);
	hit_along_cyldir = vec3_ray_at((t_ray){ctx->obj.loc, ctx->obj.rot}, vec3_dot(hypotenuse, ctx->obj.rot));
	result = vec3_sub(hit_loc, hit_along_cyldir);
	return (result);
}

int intersects_cylinder(t_ray *ray, t_object *cylinder, double *distance)
{
	t_vec3 ray_cyl;
	t_abc abc;
	double b2_4ac;

	ray_cyl = vec3_sub(ray->orig, cylinder->loc);
	abc = calc_abc_cylinder(ray->dir, cylinder->rot, ray_cyl, cylinder->size);
	b2_4ac = calc_b2_4ac(abc);
	if (b2_4ac <= 0)
		return (0);
	*distance = quadratic(abc, b2_4ac);
	if (*distance < 0)
		return (0);
	return (1);
}
