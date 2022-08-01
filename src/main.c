/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaarine <jsaarine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 19:46:34 by jsaarine          #+#    #+#             */
/*   Updated: 2022/08/01 15:20:55 by jsaarine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "../inc/RTv1.h"
#include "../inc/RTv1.h"
#include <stdbool.h>
#include <stdio.h>

//The image we will load and show on the screen
SDL_Surface* img = NULL;


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
			SDL_LockTexture(ctx.texture, NULL, (void **)&texture_data,	&texture_pitch);

			t_color c = (t_color) {255, 255, 255};
			int color = rgb_to_int(c);
			int x = 0;
			while (x < WIN_W)
			{
				int y = 0;
				while (y < WIN_H)
				{
					img_pixel_put(&ctx.frame_buffer, x, y, color);
					y++;
				}
				x++;
			}

			//buffer_copy(texture_data, ctx.frame_buffer.data, ctx.frame_buffer.bits_per_pixel);
			ft_memcpy(texture_data, ctx.frame_buffer.data, ctx.frame_buffer.bits_per_pixel * 8);
			SDL_UnlockTexture(ctx.texture);

			//Render texture to screen
			SDL_RenderCopy( ctx.renderer, ctx.texture, NULL, NULL );
		
			//Update screen
			SDL_RenderPresent( ctx.renderer );
		}
	}

	//Free resources and close SDL
	close(&ctx);

	return 0;
}