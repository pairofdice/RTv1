/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaarine <jsaarine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 13:59:07 by jsaarine          #+#    #+#             */
/*   Updated: 2022/08/15 20:28:29 by jsaarine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"
#include "vec3.h"

void	draw(t_context *ctx)
{
	int	x;
	int	y;
	t_point	L;

	t_vec3 c;

	L =  vec3_sub(ctx->cam.projection_plane_center, vec3_scalar_mult(ctx->cam.right, 0.5 * ctx->cam.projection_plane_w)); 

	L =  vec3_sub(L, vec3_scalar_mult(ctx->cam.up, 0.5 * ctx->cam.projection_plane_h)); 
	c = L;
	printf("cam->L is: %f %f %f\n", c.x, c.y, c.z);

	y = 0;
	t_object	TEST_SPHERE_1;
	t_vec3		normal;
	TEST_SPHERE_1 = sphere_new(0.0, 0.0, -4.0, 1.0);
	int debug;
	debug = 0;
	int color;
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
			color = vec3_dot(ctx->cam.n, normal) * 255;
			if (intersects_sphere(&ctx->ray, &TEST_SPHERE_1, &normal, debug))
				img_pixel_put(&ctx->frame_buffer, x, y, rgb_to_int(color, color, color));
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