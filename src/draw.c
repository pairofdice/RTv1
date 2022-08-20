/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaarine <jsaarine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 13:59:07 by jsaarine          #+#    #+#             */
/*   Updated: 2022/08/20 14:16:18 by jsaarine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/RTv1.h"
#include "../inc/vec3.h"

void	draw(t_context *ctx)
{
	//t_object	TEST_SPHERE_1;
	// int num_spheres = 8;
	// t_object	SPHERES[num_spheres];
	t_vec3		normal;
	t_point	L;
	t_point	light;
	t_vec3 c;
	double	distance;
	int	x;
	int	y;
	int i;

	light = vec3_new(0.0, -2.0, 2.5);

	L =  vec3_sub(ctx->cam.projection_plane_center, vec3_scalar_mult(ctx->cam.right, 0.5 * ctx->cam.projection_plane_w));

	L =  vec3_sub(L, vec3_scalar_mult(ctx->cam.up, 0.5 * ctx->cam.projection_plane_h));
	c = L;
	printf("cam->L is: %f %f %f\n", c.x, c.y, c.z);

	y = 0;

	ctx->OBJECTS[0] = sphere_new((t_vec3){0.0, 0.0, -10.0}, 5.0	, 	255, 223, 196);
	ctx->OBJECTS[1] = sphere_new((t_vec3){-2.0, -1.0, -7.0}, 2.0, 	255, 255, 255);
	ctx->OBJECTS[2] = sphere_new((t_vec3){2.0, -1.0, -7.0}, 2.0	, 	255, 255, 255);
	ctx->OBJECTS[3] = sphere_new((t_vec3){0.0, 1.5, -7.0}, 2.0	, 	255, 255, 255);
	ctx->OBJECTS[4] = sphere_new((t_vec3){-2.0, -1.0, -5.45}, 0.6, 	0, 0, 0);
	ctx->OBJECTS[5] = sphere_new((t_vec3){2.0, -1.0, -5.45}, 0.6, 	0, 0, 0);
	ctx->OBJECTS[6] = sphere_new((t_vec3){-0.5, 1.65, -5.35}, 0.3, 	0, 0, 0);
	//printf("Segfault A?\n");
	ctx->OBJECTS[7] = sphere_new((t_vec3){0.5, 1.65, -5.35}, 0.3, 	0, 0, 0);
	ctx->OBJECTS[8] = sphere_new((t_vec3){-5.0, 3.5, -1.0}, 1.0	,	255, 0, 0);
	ctx->OBJECTS[9] = sphere_new((t_vec3){0.0, 3.5, -1.0}, 1.0	,	0, 255, 0);
	ctx->OBJECTS[10] = sphere_new((t_vec3){5.0, 3.5, -1.0},  1.0	,	0, 0, 255);
	ctx->OBJECTS[11] = plane_new((t_vec3){0.0, 5.0, -0.0}, (t_vec3){0.1, -1.5, 0.0},	200, 200, 255);
	ctx->OBJECTS[12] = plane_new((t_vec3){0.0, 0.0, 0.0}, (t_vec3){1.0, 1.0, 1.0},	200, 200, 255);
	ctx->OBJECTS[13] = plane_new((t_vec3){0.0, -5.0, -0.0}, (t_vec3){0.1, -1.5, 0.0},	200, 200, 255);
	//printf("Segfault B?\n");


	int debug;
	debug = 0;
	//int color;
	while (y < WIN_H)
	{
		x = 0;
		while (x < WIN_W)
		{
			// create a ray for this pixel. origin is the virtual pixel on the projection plane
			// direction is location of virtual pixel minus location of camera
			ctx->ray.orig = vec3_add(L, vec3_scalar_mult(ctx->cam.right, x * ctx->cam.projection_plane_w/WIN_W));
			ctx->ray.orig = vec3_add(ctx->ray.orig, vec3_scalar_mult(ctx->cam.up, y * ctx->cam.projection_plane_h/WIN_H));
			debug = 0;
 			if ((x == WIN_W/2 && y == WIN_H/2) ||
			(x + 3 == WIN_W/2 && y == WIN_H/2) ||
			(x + 6 == WIN_W/2 && y == WIN_H/2)||
			(x + 9 == WIN_W/2 && y == WIN_H/2)
			)
			{
				debug = 1;
				c = ctx->ray.orig;
				printf("ray->orig is: %f %f %f - ", c.x, c.y, c.z);
				c = ctx->ray.dir;
				printf("ray->dir is: %f %f %f\n", c.x, c.y, c.z);

			}
			ctx->ray.dir = vec3_sub(ctx->ray.orig, ctx->cam.loc);
			ctx->ray.dir = vec3_unit(ctx->ray.dir);
			// check collision
			i = 0;
			ctx->cam.closest_hit = 1.0/0.0;
			ctx->cam.is_hit = 0;
			ctx->cam.closest_id = 0;
	 		while (i < NUM_OBJECTS)
			{
				if (ctx->OBJECTS[ctx->cam.closest_id].type == SPHERE)
				{
					if (intersects_sphere(&ctx->ray, &ctx->OBJECTS[i], &distance, debug))
					{
						ctx->cam.is_hit = 1;
						if (distance < ctx->cam.closest_hit)
						{
							ctx->cam.closest_hit = distance;
							ctx->cam.closest_id = i;
						}
					}
				}
				else if (ctx->OBJECTS[ctx->cam.closest_id].type == PLANE)
				{
					if (intersects_plane(&ctx->ray, &ctx->OBJECTS[i], &distance, debug))
					{
						//img_pixel_put(&ctx->frame_buffer, x, y, 0xFFFFFFFF  );

						ctx->cam.is_hit = 1;
						if (distance < ctx->cam.closest_hit)
						{
							ctx->cam.closest_hit = distance;
							ctx->cam.closest_id = i;
						}
					}
				}
				i++;
			}
	//*normal = vec3_unit( vec3_sub( vec3_add(ray->orig, vec3_scalar_mult(ray->dir, distance_to_intersection)), sphere->loc ) );
//	t_vec3	get_normal(t_vec3 sphere_loc, t_ray ray, double distance)

				//printf("Segfault C?\n");
			if (ctx->cam.is_hit)
			{
				if (ctx->OBJECTS[ctx->cam.closest_id].type == SPHERE)
				{
					normal = get_sphere_normal(ctx->OBJECTS[ctx->cam.closest_id].loc, ctx->ray, ctx->cam.closest_hit);
				}
				else if (ctx->OBJECTS[ctx->cam.closest_id].type == PLANE)
				{
					normal = get_plane_normal(ctx->OBJECTS[ctx->cam.closest_id].loc, ctx->ray, ctx->cam.closest_hit);
				}
				double	shading;
				// shading = 100.0;
				//printf("Segfault D?\n");
				shading = get_shading((t_ray){ vec3_ray_at(ctx->ray, ctx->cam.closest_hit), normal }, light, ctx->ray, ctx, ctx->cam.closest_id);
				//printf("Segfault E?\n");
				//shading = get_shading_specular
				int r;
				int g;
				int b;
				r = ctx->OBJECTS[ctx->cam.closest_id].r * shading * 35;
				r += shading * 6000.0;
				if (r >= 255)
					r = 255;
				g = ctx->OBJECTS[ctx->cam.closest_id].g * shading * 35 ;
				g += shading * 6000.0;
				if (g >= 255)
					g = 255;
				b = ctx->OBJECTS[ctx->cam.closest_id].b * shading * 35 ;
				b += shading * 6000.0;
				if (b >= 255)
					b = 255;
				// int color = 255;
				// color = vec3_dot(ctx->cam.n, normal) * 255;
				//img_pixel_put(&ctx->frame_buffer, x, y, rgb_to_int(shading, shading, shading));
				// img_pixel_put(&ctx->frame_buffer, x, y, rgb_to_int(color, color, color));
				img_pixel_put(&ctx->frame_buffer, x, y, rgb_to_int(r, g, b)  );

			}
			else
				img_pixel_put(&ctx->frame_buffer, x, y, 0x00000000);




			// which collision is closest
				// ???
			// calculate color
				// ???
			x++;
/* 			if (y == WIN_H/2 && x % 10 == 0)
			{
				c = ctx->ray.orig;
				printf("ray->orig is: %f %f %f - ", c.x, c.y, c.z);
				c = ctx->ray.dir;
				printf("ray->dir is: %f %f %f\n", c.x, c.y, c.z);

			} */
		}
		y++;
	}
}
