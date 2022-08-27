/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_shading.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaarine <jsaarine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 15:23:03 by jsaarine          #+#    #+#             */
/*   Updated: 2022/08/26 17:34:51 by jsaarine         ###   ########.fr       */
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
	c.x = obj.r * shading * 100;
	c.x += shading * 1000.0;
	c.x = pow(c.x, 1 / GAMMA) * 15;
	if (c.x >= 255)
		c.x = 255;
	c.y = obj.g * shading * 100;
	c.y += shading * 1000.0;
	c.y = pow(c.y, 1 / GAMMA) * 15;

	if (c.y >= 255)
		c.y = 255;
	c.z = obj.b * shading * 100;
	c.z += shading * 1000.0;
	c.z = pow(c.z, 1 / GAMMA) * 15;

	if (c.z >= 255)
		c.z = 255;
	return (c);
}

double get_light_level(t_ray normal, t_point light, t_ray ray, t_context *ctx, int id)
{
	// t_vec3 temp;
	t_vec3 to_light;
	double distance;
	// t_ray test;

	double dot;
	int i;

	to_light = vec3_sub(light, normal.orig);
	i = 0;
	distance = vec3_mag(to_light);

	while (i < NUM_OBJECTS)
	{
		if (i == id)
		{
			i++;
			continue;
		}
		if (ctx->OBJECTS[i].type == SPHERE)
		{
			if (intersects_sphere(&(t_ray){normal.orig, vec3_unit(to_light)}, &ctx->OBJECTS[i], &distance, 0))
			{
				if (distance < vec3_mag(to_light))
					return (0);
			}
		}
		if (ctx->OBJECTS[i].type == PLANE)
		{
			if (intersects_plane(&(t_ray){normal.orig, vec3_unit(to_light)}, &ctx->OBJECTS[i], &distance))
			{
				if (distance < vec3_mag(to_light))
					return (0);
			}
		}
		if (ctx->OBJECTS[i].type == CYLINDER)
		{
			if (intersects_cylinder(&(t_ray){normal.orig, vec3_unit(to_light)}, &ctx->OBJECTS[i], &distance))
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
