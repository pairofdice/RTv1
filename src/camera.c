/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaarine <jsaarine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 14:53:37 by jsaarine          #+#    #+#             */
/*   Updated: 2022/09/26 12:34:46 by jsaarine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

void init_camera(t_cam *cam, t_point loc)
{

	cam->loc = loc;
	// cam->coi = (t_point){0.0, 0.0, -1.0};
	cam->scene_up = (t_point){0.0, 1.0, 0.0};
	cam->distance_to_proj = 0.1;
	cam->aspect = (float)WIN_W / WIN_H;
	// 1.4 radians is ~80 degrees
	// 1.05 radians is ~60 degrees
	cam->projection_plane_h = tan(1.05 / 2) * 2 * cam->distance_to_proj;
	cam->projection_plane_w = cam->projection_plane_h * cam->aspect;
	cam->scene_up = vec3_neg( vec3_unit(cam->scene_up));
	cam->dir = vec3_unit(vec3_sub(cam->coi, cam->loc));
	cam->n = vec3_neg(cam->dir);
	cam->right = vec3_cross(cam->scene_up, cam->n);
	cam->up = vec3_cross(cam->n, cam->right);
	cam->projection_plane_center = vec3_add(cam->loc, vec3_scalar_mult(cam->dir, cam->distance_to_proj));
	cam->cam_to_proj = vec3_sub(cam->loc, cam->projection_plane_center);
	cam->L = vec3_sub(cam->projection_plane_center, vec3_scalar_mult(cam->right, 0.5 * cam->projection_plane_w));
	cam->L = vec3_sub(cam->L, vec3_scalar_mult(cam->up, 0.5 * cam->projection_plane_h));
}

void	set_camera(t_context *ctx)
{
	// TODO
	init_camera(&
	ctx->cam, ctx->obj.loc);
	ctx->cam.loc = ctx->obj.loc;
	ctx->cam.coi = ctx->obj.coi;
}
