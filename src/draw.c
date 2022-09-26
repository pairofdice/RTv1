/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaarine <jsaarine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 13:59:07 by jsaarine          #+#    #+#             */
/*   Updated: 2022/09/26 15:01:00 by jsaarine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/RTv1.h"
#include "../inc/vec3.h"

static void	find_normal(t_context *ctx)
{
	ctx->obj = *(t_object *)vec_get(&ctx->scene, ctx->hit.closest_id);
	if (ctx->obj.type == SPHERE)
		ctx->hit.normal = get_sphere_normal(ctx);
	else if (ctx->obj.type == PLANE)
		ctx->hit.normal = get_plane_normal(ctx);
	else if (ctx->obj.type == CYLINDER)
		ctx->hit.normal = get_cylinder_normal(ctx);
	else if (ctx->obj.type == CONE)
		ctx->hit.normal = get_cone_normal(ctx);
}

	// create a ray for this pixel. origin is the virtual pixel
	// on the projection plane
	// direction is location of virtual pixel minus location of camera
	// c = debug_shading(normal);

void	draw(t_context *ctx)
{
	double	distance;
	int		x;
	int		y;
	double	light_level;

	y = 0;
	while (y < WIN_H)
	{
		x = 0;
		while (x < WIN_W)
		{
			calc_current_ray(ctx, x, y);
			distance = 1.0 / 0.0;
			intersects(ctx, distance, NOT_LIGHT);
			if (ctx->hit.is_hit && ctx->hit.closest_id >= 0)
			{
				find_normal(ctx);
				light_level = get_light_level((t_ray){vec3_ray_at(ctx->ray, ctx->hit.closest_distance), ctx->hit.normal}, ctx->ray, ctx, ctx->hit.closest_id);
				t_color c;
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
	if (render == RENDER)
	{

	}
		ft_memset(ctx->frame_buffer.data, 0, WIN_H * WIN_W * 4);
		draw(ctx);
		printf("Rendered!\n");
	printf("Exposed!\n");

	ft_memcpy(texture_data, ctx->frame_buffer.data, WIN_H * WIN_W * 4);
	SDL_UnlockTexture(ctx->texture);
}
