/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaarine <jsaarine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 13:59:07 by jsaarine          #+#    #+#             */
/*   Updated: 2022/08/10 15:53:24 by jsaarine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"
#include "vec3.h"

void	draw(t_context *ctx)
{
	int	x;
	int	y;
	t_point	L;
	double aspect;

	aspect = WIN_W/(float)WIN_H;
	// projection_plane width & aspect ratio setup somewhere
	L =  vec3_sub(ctx->cam.projection_plane_center, vec3_scalar_mult(ctx->cam.right, 0.05)); 
	L =  vec3_sub(L, vec3_scalar_mult(ctx->cam.up, 0.05/aspect)); 

	y = 0;
	while (y < WIN_H)
	{
		x = 0;
		while (x , WIN_W)
		{
			// create a ray for this pixel
			ctx->ray.orig = ctx->cam.loc;
			ctx->ray.dir = ctx->cam.projection_plane_center
			// check collision
			// which collision is closest
			// calculate color
			x++;
		}
		y++;
	}
}