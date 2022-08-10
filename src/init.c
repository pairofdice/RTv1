/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaarine <jsaarine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 16:09:22 by jsaarine          #+#    #+#             */
/*   Updated: 2022/08/10 15:56:35 by jsaarine         ###   ########.fr       */
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
	cam->scene_up = vec3_unit(cam->scene_up);
	cam->dir = vec3_unit(vec3_sub(cam->coi, cam->loc));
	cam->n = vec3_neg(cam->dir);
	cam->right = vec3_cross(cam->scene_up, cam->n);
	cam->up = vec3_cross(cam->n, cam->right);
	cam->projection_distance = 0.1; // eventually from scene file maybe?
	cam->projection_plane_offset = vec3_sub(cam->loc, vec3_scalar_mult(cam->n,cam->projection_distance ));
	
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

/* {

	bool success = true;
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
		success = false;
	}
	else
	{
		gWindow = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if( gWindow == NULL )
		{
			printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
			success = false;
		}
		else
		{
			//Get window surface
			gScreenSurface = SDL_GetWindowSurface( gWindow );
		}
	}

	return success;
}  */
