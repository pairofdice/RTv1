/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_cylinder.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaarine <jsaarine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 16:24:39 by jsaarine          #+#    #+#             */
/*   Updated: 2022/08/26 19:08:41 by jsaarine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec3.h"
#include "objects.h"
#include <math.h>
#include <stdio.h>

static double calc_b2_4ac(t_abc abc)
{
	return (abc.b * abc.b - 4 * abc.a * abc.c);
}

t_abc static calc_abc(t_vec3 raydir, t_vec3 cyldir, t_vec3 raycyl, double radius)
{
	t_abc abc;

	abc.a = 1 - vec3_dot(raydir, cyldir) * vec3_dot(raydir, cyldir);
	abc.b = 2 * (vec3_dot(raydir, raycyl) - vec3_dot(raydir, cyldir) * vec3_dot(raycyl, cyldir));
	abc.c = vec3_dot(raycyl, raycyl) - vec3_dot(raycyl, cyldir) * vec3_dot(raycyl, cyldir) - radius * radius;
	return (abc);
}

double quadratic(t_abc abc, double b2_4ac)
{
	double result_m;
	double result_p;
	double denominator;

	if (b2_4ac < 0)
		b2_4ac *= -1;
	denominator = -abc.b - sqrt(b2_4ac);
	result_m = denominator / (2 * abc.a);
	denominator = -abc.b + sqrt(b2_4ac);
	result_p = denominator / (2 * abc.a);
	if (result_p < result_m)
		return (result_p);
	return (result_m);
}

t_object cylinder_new(t_vec3 loc, t_vec3 rot, double radius, int r, int g, int b)
{
	t_object s;

	s.r = r;
	s.g = g;
	s.b = b;
	s.loc = loc;
	s.size = radius;
	s.rot = vec3_unit(rot);
	s.type = CYLINDER;
	return (s);
}
// get_normal(SPHERES[ctx->cam.closest_id].loc, ctx->ray, ctx->cam.closest_hit);
//*normal = vec3_unit( vec3_sub( vec3_add(ray->orig, vec3_scalar_mult(ray->dir, distance_to_intersection)), sphere->loc ) );

t_vec3 get_cylinder_normal(t_object cylinder, t_ray ray, double distance)
{
	t_vec3 result;
	t_vec3 hit_loc;
	t_vec3 hypotenuse;
	t_vec3 hit_along_cyldir;

	hit_loc = vec3_ray_at(ray, distance);
	hypotenuse = vec3_sub(hit_loc, cylinder.loc);
	hit_along_cyldir = vec3_ray_at((t_ray){cylinder.loc, cylinder.rot}, vec3_dot(hypotenuse, cylinder.rot));
	result = vec3_sub(hit_loc, hit_along_cyldir);
	return (result);
}

int intersects_cylinder(t_ray *ray, t_object *cylinder, double *distance)
{
	t_vec3 w;
	t_abc abc;
	double b2_4ac;

	w = vec3_sub(ray->orig, cylinder->loc);
	abc = calc_abc(ray->dir, cylinder->rot, w, cylinder->size);
	b2_4ac = calc_b2_4ac(abc);
	if (b2_4ac <= 0)
		return (0);
	*distance = quadratic(abc, b2_4ac);
	if (*distance < 0)
		return (0);
	return (1);
}
