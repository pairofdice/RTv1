/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaarine <jsaarine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 16:09:22 by jsaarine          #+#    #+#             */
/*   Updated: 2022/08/18 14:25:58 by jsaarine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"
#include "objects.h"

int	st_error()
{
	// TODO
    printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
	return (0);
}

void	init_camera(t_cam *cam)
{
	t_vec3 c;
	cam->loc = (t_point) {0.0, 0.0, 10.0};
	cam->coi = (t_point) {0.0, 0.0, -1.0};
	cam->scene_up = (t_point) {0.0, 1.0, 0.0};
	cam->distance_to_proj = 0.1;
	cam->aspect = (float)WIN_W/WIN_H;
	// 1.4 radians is ~80 degrees
	// 1.05 radians is ~60 degrees
	cam->projection_plane_h = tan(1.05/2) * 2 * cam->distance_to_proj;
	printf("pp h: %f\n", cam->projection_plane_h);
	cam->projection_plane_w = cam->projection_plane_h * cam->aspect;
	printf("pp w: %f\n", cam->projection_plane_w);
	cam->scene_up = vec3_unit(cam->scene_up);
	c = cam->scene_up;
	printf("cam->scene_up is: %f %f %f\n", c.x, c.y, c.z);
	cam->dir = vec3_unit(vec3_sub(cam->coi, cam->loc));
	c = cam->dir;
	printf("cam->dir is: %f %f %f\n", c.x, c.y, c.z);
	cam->n = vec3_neg(cam->dir);
	c = cam->n;
	printf("cam->n is: %f %f %f\n", c.x, c.y, c.z);
	cam->right = vec3_cross(cam->scene_up, cam->n);
	c = cam->right;
	printf("cam->right is: %f %f %f\n", c.x, c.y, c.z);
	cam->up = vec3_cross(cam->n, cam->right);
	c = cam->up;
	printf("cam->up is: %f %f %f\n", c.x, c.y, c.z);
	cam->projection_plane_center = vec3_add(cam->loc, vec3_scalar_mult(cam->dir, cam->distance_to_proj));
	c = cam->projection_plane_center;
	printf("cam->projection_plane_center is: %f %f %f\n", c.x, c.y, c.z);
	c = cam->loc;
	printf("cam->loc is: %f %f %f\n", c.x, c.y, c.z);
	cam->cam_to_proj = vec3_sub(cam->loc, cam->projection_plane_center);
	c = cam->cam_to_proj;
	printf("cam->cam_to_proj is: %f %f %f\n", c.x, c.y, c.z);
}

int	init(t_context *ctx)
{
	t_cam	cam;

	init_camera(&cam);
	ctx->cam = cam;
	//The window we'll be rendering to
	ctx->window = NULL;
	//The surface contained by the window
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
		return (st_error()); //printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
	ctx->window = SDL_CreateWindow( "RTv1", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIN_W, WIN_H, SDL_WINDOW_ALLOW_HIGHDPI );
	if( ctx->window == NULL )
		return (st_error()); //printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
	ctx->renderer = SDL_CreateRenderer(ctx->window, -1, 0);
	ctx->texture = SDL_CreateTexture(ctx->renderer, SDL_PIXELFORMAT_RGBA8888,
			SDL_TEXTUREACCESS_STREAMING, WIN_W, WIN_H);
	



	return (1);
}

