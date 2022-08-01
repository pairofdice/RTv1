/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaarine <jsaarine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 19:46:34 by jsaarine          #+#    #+#             */
/*   Updated: 2022/08/01 14:53:40 by jsaarine         ###   ########.fr       */
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
				int	*texture_data;
				int	texture_pitch;

				if (SDL_LockTexture(ctx.texture, NULL, (void **)&texture_data,
						&texture_pitch) < 0)
				{
					//ctx.ok = rt_false;
				}
				int x = 0;
				while (x < WIN_W)
				{
					int y = 0;
					while (y < WIN_H)
					{

						img_pixel_put(&ctx.frame_buffer, x, y, 8000000);
						y++;
					}
					x++;
				}
				img_pixel_put(&ctx.frame_buffer, 100, 100, 0xFFFFFF);
				img_pixel_put(&ctx.frame_buffer, 100, 101, 8000000);
				img_pixel_put(&ctx.frame_buffer, 100, 102, 8000000);
				ft_memcpy(texture_data, ctx.frame_buffer.data,
					ctx.frame_buffer.bits_per_pixel * 8);
				SDL_UnlockTexture(ctx.texture);
				//Render texture to screen
                SDL_RenderCopy( ctx.renderer, ctx.texture, NULL, NULL );
			
				//Update screen
                SDL_RenderPresent( ctx.renderer );
			}
		}
	}

	//Free resources and close SDL
	close(&ctx);

	return 0;
}