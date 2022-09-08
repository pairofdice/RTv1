/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaarine <jsaarine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 13:59:07 by jsaarine          #+#    #+#             */
/*   Updated: 2022/09/08 18:40:18 by jsaarine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/RTv1.h"
#include "../inc/vec3.h"

void draw(t_context *ctx)
{
	//t_object o;
	t_vec3 normal;
	t_point L;
	t_point light;
	t_vec3 c;
	double distance;
	int x;
	int y;
	// int i;

/* 	ctx->OBJECTS[0] = sphere_new((t_vec3){0.0, 0.0, -10.0}, 5.0, 255, 223, 196);
	ctx->OBJECTS[1] = sphere_new((t_vec3){-2.0, -1.0, -7.0}, 2.0, 255, 255, 255);
	ctx->OBJECTS[2] = sphere_new((t_vec3){2.0, -1.0, -7.0}, 2.0, 255, 255, 255);
	ctx->OBJECTS[3] = sphere_new((t_vec3){0.0, 1.5, -7.0}, 2.0, 255, 255, 255);
	ctx->OBJECTS[4] = sphere_new((t_vec3){-2.0, -1.0, -5.45}, 0.6, 0, 0, 0);
	ctx->OBJECTS[5] = sphere_new((t_vec3){2.0, -1.0, -5.45}, 0.6, 0, 0, 0);
	ctx->OBJECTS[6] = sphere_new((t_vec3){-0.5, 1.65, -5.35}, 0.3, 0, 0, 0);

	ctx->OBJECTS[7] = sphere_new((t_vec3){0.5, 1.65, -5.35}, 0.3, 0, 0, 0);
	ctx->OBJECTS[8] = sphere_new((t_vec3){-10.0, 4.0, -7.0}, 1.0, 255, 0, 0);
	ctx->OBJECTS[9] = sphere_new((t_vec3){0.0, 4.0, -3.0}, 1.0, 0, 255, 0);
	ctx->OBJECTS[10] = sphere_new((t_vec3){10.0, 4.0, -7.0}, 1.0, 0, 0, 255);
	ctx->OBJECTS[11] = plane_new((t_vec3){0.0, 5.0, 0.0}, (t_vec3){0.0, -1.5, 0.0}, 200, 200, 255);
	ctx->OBJECTS[12] = plane_new((t_vec3){11.0, 0.0, 0.0}, (t_vec3){-1.0, 0.0, 0.0}, 255, 0, 0);
	ctx->OBJECTS[13] = plane_new((t_vec3){-11.0, 0.0, 0.0}, (t_vec3){1.0, 0.0, 0.0}, 0, 0, 255);
	ctx->OBJECTS[14] = plane_new((t_vec3){0.0, 0.0, -24.0}, (t_vec3){0.0, 0.0, 1.0}, 255, 111, 33);
	ctx->OBJECTS[15] = plane_new((t_vec3){0.0, -9.0, 0.0}, (t_vec3){0.0, 1.0, 0.0}, 0, 255, 0);*/

	
	//ctx->OBJECTS[0] = cone_new((t_vec3){0.0, 8.0, 0.0}, (t_vec3){0.0, 0.0, 1.0}, 0.2, /* (t_vec3){0.0, 1.0, 0.0}, */ 255, 255, 0);

	// int debug;

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

	light = vec3_new(6.0, 2.0, -1.0);
	L = vec3_sub(ctx->cam.projection_plane_center, vec3_scalar_mult(ctx->cam.right, 0.5 * ctx->cam.projection_plane_w));
	L = vec3_sub(L, vec3_scalar_mult(ctx->cam.up, 0.5 * ctx->cam.projection_plane_h));
	c = L;
	printf("cam->L is: %f %f %f\n", c.x, c.y, c.z);

	y = 0;
	while (y < WIN_H)
	{
		x = 0;
		while (x < WIN_W)
		{

			// create a ray for this pixel. origin is the virtual pixel on the projection plane
			// direction is location of virtual pixel minus location of camera
			ctx->ray.orig = vec3_add(L, vec3_scalar_mult(ctx->cam.right, x * ctx->cam.projection_plane_w / WIN_W));
			ctx->ray.orig = vec3_add(ctx->ray.orig, vec3_scalar_mult(ctx->cam.up, y * ctx->cam.projection_plane_h / WIN_H));

			ctx->ray.dir = vec3_sub(ctx->ray.orig, ctx->cam.loc);
			ctx->ray.dir = vec3_unit(ctx->ray.dir);
			// check collision
			// i = 0;

			
			// intersects(t_context *ctx, double distance)
			distance = 1.0 / 0.0;
			intersects(ctx, distance, NOT_LIGHT);

			if (ctx->hit.is_hit && ctx->hit.closest_id >= 0)
			{
				//printf("Scene len %d\n", ctx->scene.len, ctx->hit.closest_id);
			//printf("Scene len %d\n", ctx->scene.len);
				ctx->obj = *(t_object *)vec_get(&ctx->scene, ctx->hit.closest_id);
				if (ctx->obj.type /* ctx->OBJECTS[ctx->hit.closest_id].type */ == SPHERE)
					normal = get_sphere_normal(ctx->obj.loc, ctx->ray, ctx->hit.closest_distance);
 				
				else if (ctx->obj.type == PLANE)
					normal = get_plane_normal(ctx->obj, ctx->ray);
				else if (ctx->obj.type == CYLINDER)
					normal = get_cylinder_normal(ctx->obj, ctx->ray, ctx->hit.closest_distance);
				else if (ctx->obj.type == CONE)
					normal = get_cone_normal(ctx->obj, ctx->ray, ctx->hit.closest_distance); 
				//	normal = ctx->OBJECTS[ctx->hit.closest_id].rot;
				// get_cylinder_normal(t_object cylinder, t_ray ray, double distance)
				// normal = get_cylinder_normal(ctx->OBJECTS[ctx->hit.closest_id].loc, ctx->ray, ctx->hit.closest_distance);
				double light_level;
				light_level = get_light_level((t_ray){vec3_ray_at(ctx->ray, ctx->hit.closest_distance), normal}, light, ctx->ray, ctx, ctx->hit.closest_id);
				t_color c;
				// c = debug_shading(normal);
				c = shade(ctx->obj, light_level, &ctx->ambient);
				img_pixel_put(&ctx->frame_buffer, x, y, rgb_to_int(c.x, c.y, c.z));
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

void write_buffer(t_context *ctx, int *texture_data, int *texture_pitch, int render)
{
	SDL_LockTexture(ctx->texture, NULL, (void *)&texture_data, texture_pitch);
	ctx->frame_buffer.data = malloc(WIN_H * WIN_W * 4);

	if (render == RENDER)
	{
	}
	ft_memset(ctx->frame_buffer.data, 0, WIN_H * WIN_W * 4);
	draw(ctx);

	ft_memcpy(texture_data, ctx->frame_buffer.data, WIN_H * WIN_W * 4);
	SDL_UnlockTexture(ctx->texture);
}
