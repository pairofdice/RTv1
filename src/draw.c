/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaarine <jsaarine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 13:59:07 by jsaarine          #+#    #+#             */
/*   Updated: 2022/08/15 16:20:22 by jsaarine         ###   ########.fr       */
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
	TEST_SPHERE_1 = sphere_new(0.0, 0.0, -10.0, 1.0);
	while (y < WIN_H)
	{
		x = 0;
		while (x < WIN_W)
		{
			// create a ray for this pixel. origin is the virtual pixel on the projection plane
			// direction is location of virtual pixel minus location of camera
			ctx->ray.orig = vec3_add(L, vec3_scalar_mult(ctx->cam.right, x * ctx->cam.projection_plane_w));
			ctx->ray.orig = vec3_add(ctx->ray.orig, vec3_scalar_mult(ctx->cam.up, y * ctx->cam.projection_plane_h));
			ctx->ray.dir = vec3_sub(ctx->ray.orig, ctx->cam.loc);
			ctx->ray.dir = vec3_unit(ctx->ray.dir);
			// check collision
int	intersects_sphere(t_ray *ray, t_object *sphere, t_vec3 *normal);

			if (intersects_sphere(&ctx->ray, &TEST_SPHERE_1, &normal))
				img_pixel_put(&ctx->frame_buffer, x, y, 0xFFFFFF00);
			else
				img_pixel_put(&ctx->frame_buffer, x, y, 0x00000000);
			//if (x == 200)
			//	img_pixel_put(&ctx->frame_buffer, x, y, 0xFFFFFF00);
				
				
				

			// which collision is closest
				// ???
			// calculate color
				// ???
			x++;
		}
		y++;
	}
}