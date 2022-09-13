/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_shading.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaarine <jsaarine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 15:23:03 by jsaarine          #+#    #+#             */
/*   Updated: 2022/09/13 16:41:00 by jsaarine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// get_shading(normal, light, &SPHERES,ctx->cam.closest_id);

//#include "vec3.h"
//#include "objects.h"
#include "RTv1.h"

t_color debug_shading(t_vec3 normal)
{
	t_color c;

	c.x = normal.x * 100 + 127;
	c.y = normal.y * 100 + 127;
	c.z = normal.z * 100 + 127;
	return (c);
}

t_color shade(t_object obj, double shading, t_light *ambient)
{
	t_color c;

	shading += AMBIENT;
	if (ambient->color.x < 100)
	{
	}
	c.x = obj.color.x * shading * 100 * 255;
	c.x += shading * 1000.0;
	c.x = pow(c.x, 1 / GAMMA) * 15;
	if (c.x >= 255)
		c.x = 255;
	c.y = obj.color.y * shading * 100 * 255;
	c.y += shading * 1000.0;
	c.y = pow(c.y, 1 / GAMMA) * 15;

	if (c.y >= 255)
		c.y = 255;
	c.z = obj.color.z * shading * 100 * 255;
	c.z += shading * 1000.0;
	c.z = pow(c.z, 1 / GAMMA) * 15;

	if (c.z >= 255)
		c.z = 255;
	return (c);
}

double get_light_level(t_ray normal, t_point light, t_ray ray, t_context *ctx, size_t id)
{
	// t_vec3 temp;
	t_vec3 to_light;
	double distance;
	// t_ray test;
	t_object o;

	double dot;
	size_t i;

	to_light = vec3_sub(light, normal.orig);
	i = 0;
	distance = vec3_mag(to_light);

	if (fabs(ctx->obj.size - 0.3) < 0.001)
				printf(" obj.color %.0f %.0f %.0f\n", ctx->obj.color.x, ctx->obj.color.y, ctx->obj.color.z);
	 while (i < ctx->scene.len)
	{
		if (i == id)
		{
			i++;
			continue;
		}
		o = *(t_object *)vec_get(&ctx->scene, i);
		if (o.type == SPHERE)
		{
			if (intersects_sphere(&(t_ray){normal.orig, vec3_unit(to_light)}, &ctx->obj, &distance))
			{
				if (distance < vec3_mag(to_light))
					return (0);
			}
		}
		if (o.type == PLANE)
		{
			if (intersects_plane(&(t_ray){normal.orig, vec3_unit(to_light)}, &ctx->obj, &distance))
			{
				if (distance < vec3_mag(to_light))
					return (0);
			}
		}
		if (o.type == CYLINDER)
		{
			if (intersects_cylinder(&(t_ray){normal.orig, vec3_unit(to_light)}, &ctx->obj, &distance))
			{
				if (distance < vec3_mag(to_light))
					return (0);
			}
		}
		if (o.type == CONE)
		{
			if (intersects_cone(&(t_ray){normal.orig, vec3_unit(to_light)}, &ctx->obj, &distance))
			{
				if (distance < vec3_mag(to_light))
					return (0);
			}
		}

		i++;
	} 

	dot = vec3_dot(normal.dir, vec3_unit(to_light));
	vec3_dot(vec3_neg(ray.dir), normal.dir);
	if (dot < 0)
		dot = 0;
	dot = dot / (vec3_mag(to_light) * vec3_mag(to_light));
	// printf("Segfault DB?%d\n", NUM_OBJECTS);
	return (dot);
}
