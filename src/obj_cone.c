/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_cone.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaarine <jsaarine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 16:24:39 by jsaarine          #+#    #+#             */
/*   Updated: 2022/09/08 18:51:55 by jsaarine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec3.h"
#include "objects.h"

t_abc static	calc_abc_cone(t_vec3 raydir, t_vec3 conedir, t_vec3 raycyl, double radius)
{
	t_abc abc;
	double rr;

	rr = radius * radius;
	abc.a = 1 - rr * vec3_dot(raydir, conedir) * vec3_dot(raydir, conedir) - vec3_dot(raydir, conedir) * vec3_dot(raydir, conedir);
	abc.b = 2 * (vec3_dot(raydir, raycyl) - rr * vec3_dot(raydir, conedir) * vec3_dot(raycyl, conedir) - vec3_dot(raydir, conedir) * vec3_dot(raycyl, conedir));
	abc.c = vec3_dot(raycyl, raycyl) - rr * vec3_dot(raycyl, conedir) * vec3_dot(raycyl, conedir) - vec3_dot(raycyl, conedir) * vec3_dot(raycyl, conedir);
	return (abc);
}

t_object	cone_new(t_vec3 loc, t_vec3 rot, double radius, int r, int g, int b)
{
	t_object s;

	s.color.x = r;
	s.color.y = g;
	s.color.z = b;
	s.loc = loc;
	s.size = radius;
	s.rot = vec3_unit(rot);
	s.type = CONE;
	return (s);
}
// get_normal(SPHERES[ctx->cam.closest_id].loc, ctx->ray, ctx->cam.closest_hit);
//*normal = vec3_unit( vec3_sub( vec3_add(ray->orig, vec3_scalar_mult(ray->dir, distance_to_intersection)), sphere->loc ) );

t_vec3	get_cone_normal(t_object cone, t_ray ray, double distance)
{
	t_vec3 result;
	t_vec3 hit_loc;
	t_vec3 hypotenuse;

	hit_loc = vec3_ray_at(ray, distance);
	hypotenuse = vec3_sub(hit_loc, cone.loc);
	result = vec3_unit(vec3_cross(hypotenuse, vec3_cross(hypotenuse, cone.rot)));
	if (vec3_dot(ray.dir, result) > 0)
		result = vec3_neg(result);
	return (result);
}

int	intersects_cone(t_ray *ray, t_object *cone, double *distance)
{
	t_vec3 ray_cone;
	t_abc abc;
	double b2_4ac;

	ray_cone = vec3_sub(ray->orig, cone->loc);
	abc = calc_abc_cone(ray->dir, cone->rot, ray_cone, cone->size);
	b2_4ac = calc_b2_4ac(abc);
	if (b2_4ac <= 0)
		return (0);
	*distance = quadratic(abc, b2_4ac);
	if (*distance < 0)
		return (0);
	return (1);
}
