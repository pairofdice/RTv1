/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaarine <jsaarine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 16:09:22 by jsaarine          #+#    #+#             */
/*   Updated: 2022/08/01 14:16:16 by jsaarine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/RTv1.h"

int	st_error()
{
	// TODO
    printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
	return (0);
}

int	init(t_context *ctx)
{
	//The window we'll be rendering to
	ctx->window = NULL;
	//The surface contained by the window
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
		return (st_error()); //printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
	ctx->window = SDL_CreateWindow( "RTv1", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_SHOWN );
	if( ctx->window == NULL )
		return (st_error()); //printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
	ctx->renderer = SDL_CreateRenderer(ctx->window, -1, 0);
	ctx->texture = SDL_CreateTexture(ctx->renderer, SDL_PIXELFORMAT_RGBA8888,
			SDL_TEXTUREACCESS_STREAMING, 640, 480);
	
	

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