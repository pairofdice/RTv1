/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaarine <jsaarine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 19:46:34 by jsaarine          #+#    #+#             */
/*   Updated: 2022/07/28 18:45:09 by jsaarine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "../inc/RTv1.h"
#include "../inc/RTv1.h"
#include <stdbool.h>
#include <stdio.h>

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

//Loads media
bool loadMedia();

//The image we will load and show on the screen
SDL_Surface* img = NULL;

bool loadMedia()
{
	//Loading success flag
	bool success = true;

	//Load splash image
	img = SDL_LoadBMP( "hello_world.bmp" );
	if( img == NULL )
	{
		printf( "Unable to load image %s! SDL Error: %s\n", "03_event_driven_programming/x.bmp", SDL_GetError() );
		success = false;
	}

	return success;
}

void close(t_context *ctx)
{
	//Deallocate surface
	SDL_FreeSurface( img );
	img = NULL;

	//Destroy window
	SDL_DestroyWindow( ctx->window );
	ctx->window = NULL;

	//Quit SDL subsystems
	SDL_Quit();
}

int main( int argc, char* args[] )
{
	if (argc || args)
	{}
	//Start up SDL and create window
	t_context	ctx;
	if( !init(&ctx) )
	{
		printf( "Failed to initialize!\n" );
	}
	else
	{
		//Load media
		if( !loadMedia() )
		{
			printf( "Failed to load media!\n" );
		}
		else
		{			
			//Main loop flag
			bool quit = false;

			//Event handler
			SDL_Event e;

			//While application is running
			while( !quit )
			{
				//Handle events on queue
				while( SDL_PollEvent( &e ) != 0 )
				{
					//User requests quit
					if( e.type == SDL_QUIT )
					{
						quit = true;
					}
				}

				//Apply the image
				SDL_BlitSurface( img, NULL, ctx.screen_surface, NULL );
			
				//Update the surface
				SDL_UpdateWindowSurface( ctx.window );
			}
		}
	}

	//Free resources and close SDL
	close(&ctx);

	return 0;
}