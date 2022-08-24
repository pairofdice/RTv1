/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaarine <jsaarine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 13:59:07 by jsaarine          #+#    #+#             */
/*   Updated: 2022/08/24 19:58:44 by jsaarine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/RTv1.h"
#include "../inc/vec3.h"

void	draw(t_context *ctx)
{
	t_vec3	normal;
	t_point	L;
	t_point	light;
	t_vec3	c;
	double	distance;
	int		x;
	int		y;
	int		i;

	light = vec3_new(0.1, -4.0, 2.0);

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

	ctx->OBJECTS[7] = sphere_new((t_vec3){0.5, 1.65, -5.35}, 0.3, 	0, 0, 0);
	ctx->OBJECTS[8] = sphere_new((t_vec3){-10.0, 4.0, -7.0}, 1.0,	255, 0, 0);
	ctx->OBJECTS[9] = sphere_new((t_vec3){0.0, 4.0, -3.0}, 1.0	,	0, 255, 0);
	ctx->OBJECTS[10] = sphere_new((t_vec3){10.0, 4.0, -7.0},  1.0,	0, 0, 255);
	ctx->OBJECTS[11] = plane_new((t_vec3){0.0, 5.0, 0.0}, (t_vec3){0.0, -1.5, 0.0},	200, 200, 255);
	ctx->OBJECTS[12] = plane_new((t_vec3){11.0, 0.0, 0.0}, (t_vec3){-1.0, 0.0, 0.0},	255, 0, 0);
	ctx->OBJECTS[13] = plane_new((t_vec3){-11.0, 0.0, 0.0}, (t_vec3){1.0, 0.0, 0.0},	0, 0, 255);
	ctx->OBJECTS[14] = plane_new((t_vec3){0.0, 0.0, -24.0}, (t_vec3){0.0, 0.0, 1.0},	255, 111, 33);
	ctx->OBJECTS[15] = plane_new((t_vec3){0.0, -9.0, 0.0}, (t_vec3){0.0, 1.0, 0.0},	0, 255, 0);

	//int debug;

/* 	c = ctx->OBJECTS[11].rot;
	printf("normal is: %f %f %f \n ", c.x, c.y, c.z);
	c = ctx->OBJECTS[12].rot;
	printf("normal is: %f %f %f \n ", c.x, c.y, c.z);
	c = ctx->OBJECTS[13].rot;
	printf("normal is: %f %f %f \n ", c.x, c.y, c.z);
	c = ctx->OBJECTS[14].rot;
	printf("normal is: %f %f %f \n ", c.x, c.y, c.z);
	c = ctx->OBJECTS[15].rot;
	printf("normal is: %f %f %f \n ", c.x, c.y, c.z); */
	
	while (y < WIN_H)
	{
		x = 0;
		while (x < WIN_W)
		{

			// create a ray for this pixel. origin is the virtual pixel on the projection plane
			// direction is location of virtual pixel minus location of camera
			ctx->ray.orig = vec3_add(L, vec3_scalar_mult(ctx->cam.right, x * ctx->cam.projection_plane_w/WIN_W));
			ctx->ray.orig = vec3_add(ctx->ray.orig, vec3_scalar_mult(ctx->cam.up, y * ctx->cam.projection_plane_h/WIN_H));
	
			ctx->ray.dir = vec3_sub(ctx->ray.orig, ctx->cam.loc);
			ctx->ray.dir = vec3_unit(ctx->ray.dir);
			// check collision
			i = 0;
			ctx->cam.closest_hit = 1.0/0.0;
			ctx->cam.is_hit = 0;
			ctx->cam.closest_id = 0;
	 		while (i < NUM_OBJECTS)
			{
				// printf("Do we get into checking plane?\n");
				if (ctx->OBJECTS[i].type == SPHERE)
				{
					if (intersects_sphere(&ctx->ray, &ctx->OBJECTS[i], &distance, 0))
					{
						ctx->cam.is_hit = 1;
						if (distance < ctx->cam.closest_hit)
						{
							ctx->cam.closest_hit = distance;
							ctx->cam.closest_id = i;
						}
					}
				}
				else if (ctx->OBJECTS[i].type == PLANE)
				{
					if (intersects_plane(&ctx->ray, &ctx->OBJECTS[i], &distance))
					{
					
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

			if (ctx->cam.is_hit)
			{

				if (ctx->OBJECTS[ctx->cam.closest_id].type == SPHERE)
					normal = get_sphere_normal(ctx->OBJECTS[ctx->cam.closest_id].loc, ctx->ray, ctx->cam.closest_hit);
				else if (ctx->OBJECTS[ctx->cam.closest_id].type == PLANE)
					normal = get_plane_normal(ctx->OBJECTS[ctx->cam.closest_id], ctx->ray);
				double	light_level;
				light_level = get_light_level((t_ray){ vec3_ray_at(ctx->ray, ctx->cam.closest_hit), normal }, light, ctx->ray, ctx, ctx->cam.closest_id);				t_color c;
				// c = debug_shading(normal);
				c = shade(ctx->OBJECTS[ctx->cam.closest_id], light_level, &ctx->ambient);
				img_pixel_put(&ctx->frame_buffer, x, y,rgb_to_int(c.x, c.y, c.z));
			}
			else
				img_pixel_put(&ctx->frame_buffer, x, y, 0x00000000);



			

/* 			if ((x == WIN_W/2 && y == 100) ||
				(x == WIN_W - 100 && y == WIN_H/2) ||
				(x  == WIN_W/2 && y == WIN_H - 100)||
				(x == 100 && y == WIN_H/2)
				)
				{
					
					printf("After plane intersect.\n");
					c = ctx->OBJECTS[ctx->cam.closest_id].rot;
					printf("normal is: %f %f %f \n ", c.x, c.y, c.z);
					//c = ctx->ray.dir;
					//printf("ray->dir is: %f %f %f\n", c.x, c.y, c.z);

				}  */
			x++;
		}
		y++;
	}
}
