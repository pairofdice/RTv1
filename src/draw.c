/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaarine <jsaarine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 13:59:07 by jsaarine          #+#    #+#             */
/*   Updated: 2022/08/17 17:50:21 by jsaarine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"
#include "vec3.h"

void	draw(t_context *ctx)
{
	t_object	TEST_SPHERE_1;
	int num_spheres = 8;
	t_object	SPHERES[num_spheres];
	t_vec3		normal;
	t_point	L;
	t_point	light;
	t_vec3 c;
	double	distance;
	int	x;
	int	y;
	int i;

	light = vec3_new(0.0, 22.2, 11.1);

	L =  vec3_sub(ctx->cam.projection_plane_center, vec3_scalar_mult(ctx->cam.right, 0.5 * ctx->cam.projection_plane_w)); 

	L =  vec3_sub(L, vec3_scalar_mult(ctx->cam.up, 0.5 * ctx->cam.projection_plane_h)); 
	c = L;
	printf("cam->L is: %f %f %f\n", c.x, c.y, c.z);

	y = 0;
	TEST_SPHERE_1 = sphere_new(0.0, 0.0, -10.0, 5.0);
	SPHERES[0] = sphere_new(0.0, 0.0, -10.0, 5.0);
	SPHERES[1] = sphere_new(-2.0, -1.0, -7.0, 2.0);
	SPHERES[2] = sphere_new(2.0, -1.0, -7.0, 2.0);
	SPHERES[3] = sphere_new(0.0, 1.5, -7.0, 2.0);
	SPHERES[4] = sphere_new(-2.0, -1.0, -5.5, 0.6);
	SPHERES[5] = sphere_new(2.0, -1.0, -5.5, 0.6);
	SPHERES[6] = sphere_new(-0.5, 1.65, -5.35, 0.3);
	SPHERES[7] = sphere_new(0.5, 1.65, -5.35, 0.3);

	
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
	 		while (i < num_spheres)
			{
				if (intersects_sphere(&ctx->ray, &SPHERES[i], &distance, debug))
				{
					ctx->cam.is_hit = 1;
					if (distance < ctx->cam.closest_hit)
					{
						ctx->cam.closest_hit = distance;
						ctx->cam.closest_id = i;
					}
				}
				i++;
			} 
	//*normal = vec3_unit( vec3_sub( vec3_add(ray->orig, vec3_scalar_mult(ray->dir, distance_to_intersection)), sphere->loc ) );
//	t_vec3	get_normal(t_vec3 sphere_loc, t_ray ray, double distance)
	 		
			if (ctx->cam.is_hit)
			{
				normal = get_normal(SPHERES[ctx->cam.closest_id].loc, ctx->ray, ctx->cam.closest_hit);
				double	shading;
				shading = 100.0;
				shading = get_shading((t_ray){ vec3_ray_at(ctx->ray, ctx->cam.closest_hit), normal }, light, ctx->ray) * 50;
				int color = 255;
				color = vec3_dot(ctx->cam.n, normal) * 255;
				//img_pixel_put(&ctx->frame_buffer, x, y, rgb_to_int(shading, shading, shading));
				// img_pixel_put(&ctx->frame_buffer, x, y, rgb_to_int(color, color, color));
				
				img_pixel_put(&ctx->frame_buffer, x, y, rgb_to_int(shading, shading, shading));
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