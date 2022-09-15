/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_cone.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaarine <jsaarine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 16:24:39 by jsaarine          #+#    #+#             */
/*   Updated: 2022/09/15 16:42:04 by jsaarine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"
#include "objects.h"

t_abc static	
	calc_abc_cone(t_vec3 raydir, t_vec3 conedir, t_vec3 raycyl, double radius)
{
	t_abc	abc;
	double	rr;

	rr = radius * radius;
	abc.a = 1 - rr * vec3_dot(raydir, conedir) * vec3_dot(raydir, conedir)
		- vec3_dot(raydir, conedir) * vec3_dot(raydir, conedir);
	abc.b = 2 * (vec3_dot(raydir, raycyl) - rr * vec3_dot(raydir, conedir)
			* vec3_dot(raycyl, conedir) - vec3_dot(raydir, conedir)
			* vec3_dot(raycyl, conedir));
	abc.c = vec3_dot(raycyl, raycyl) - rr * vec3_dot(raycyl, conedir)
		* vec3_dot(raycyl, conedir) - vec3_dot(raycyl, conedir)
		* vec3_dot(raycyl, conedir);
	return (abc);
}

/* t_object	cone_new(t_vec3 loc, t_vec3 rot, double radius, t_color c)
{
	t_object	s;

	s.color.x = c.x;
	s.color.y = c.y;
	s.color.z = c.z;
	s.loc = loc;
	s.size = radius;
	s.rot = vec3_unit(rot);
	s.type = CONE;
	return (s);
}
 */
t_vec3	get_cone_normal(t_context *ctx)
{
	t_vec3	result;
	t_vec3	hit_loc;
	t_vec3	hypotenuse;

	hit_loc = vec3_ray_at(ctx->ray, ctx->hit.closest_distance);
	hypotenuse = vec3_sub(hit_loc, ctx->obj.loc);
	result = vec3_unit(vec3_cross(hypotenuse,
				vec3_cross(hypotenuse, ctx->obj.rot)));
	if (vec3_dot(ctx->ray.dir, result) > 0)
		result = vec3_neg(result);
	return (result);
}

int	intersects_cone(t_ray *ray, t_object *cone, double *distance)
{
	t_vec3	ray_cone;
	t_abc	abc;
	double	b2_4ac;

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
