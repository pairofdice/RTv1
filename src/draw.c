/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaarine <jsaarine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 13:59:07 by jsaarine          #+#    #+#             */
/*   Updated: 2022/09/09 18:33:09 by jsaarine         ###   ########.fr       */
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

	light = vec3_new(6.0, 2.0, -1.0);
	L = vec3_sub(ctx->cam.projection_plane_center, vec3_scalar_mult(ctx->cam.right, 0.5 * ctx->cam.projection_plane_w));
	L = vec3_sub(L, vec3_scalar_mult(ctx->cam.up, 0.5 * ctx->cam.projection_plane_h));
	c = L;
	//printf("cam->L is: %f %f %f\n", c.x, c.y, c.z);

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

			distance = 1.0 / 0.0;
			intersects(ctx, distance, NOT_LIGHT);

			if (ctx->hit.is_hit && ctx->hit.closest_id >= 0)
			{
				ctx->obj = *(t_object *)vec_get(&ctx->scene, ctx->hit.closest_id);
				if (ctx->obj.type  == SPHERE)
					normal = get_sphere_normal(ctx->obj.loc, ctx->ray, ctx->hit.closest_distance);
 				
				else if (ctx->obj.type == PLANE)
					normal = get_plane_normal(ctx->obj, ctx->ray);
				else if (ctx->obj.type == CYLINDER)
					normal = get_cylinder_normal(ctx->obj, ctx->ray, ctx->hit.closest_distance);
				else if (ctx->obj.type == CONE)
					normal = get_cone_normal(ctx->obj, ctx->ray, ctx->hit.closest_distance); 
				double light_level;
				light_level = get_light_level((t_ray){vec3_ray_at(ctx->ray, ctx->hit.closest_distance), normal}, light, ctx->ray, ctx, ctx->hit.closest_id);
				t_color c;
				// c = debug_shading(normal);
				c = shade(ctx->obj, light_level, &ctx->ambient);
				img_pixel_put(&ctx->frame_buffer, x, y, rgb_to_int(c.x, c.y, c.z));
			}
			else
				img_pixel_put(&ctx->frame_buffer, x, y, 0x00000000);


			x++;
		}
		y++;
	}
}

void write_buffer(t_context *ctx, int *texture_data, int *texture_pitch, int render)
{
	SDL_LockTexture(ctx->texture, NULL, (void *)&texture_data, texture_pitch);
	ctx->frame_buffer.data = malloc(WIN_H * WIN_W * 4);

/* 	if (render == RENDER)
	{
		// What was I doing here?
	} */
	ft_memset(ctx->frame_buffer.data, 0, WIN_H * WIN_W * 4);
	draw(ctx);

	ft_memcpy(texture_data, ctx->frame_buffer.data, WIN_H * WIN_W * 4);
	SDL_UnlockTexture(ctx->texture);
}
