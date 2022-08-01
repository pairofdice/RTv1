/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaarine <jsaarine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 19:46:34 by jsaarine          #+#    #+#             */
/*   Updated: 2022/08/01 18:03:52 by jsaarine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "../inc/RTv1.h"
#include "../inc/RTv1.h"
#include <stdbool.h>
#include <stdio.h>

void close(t_context *ctx)
{
	//Deallocate surface
/* 	SDL_FreeSurface( img );
	img = NULL; */

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
		int	texture_pitch;
			int	*texture_data;
			SDL_LockTexture(ctx.texture, NULL, (void **)&texture_data,	&texture_pitch);
			ctx.frame_buffer.data = malloc(WIN_H * WIN_W * 4);
			ft_memset( ctx.frame_buffer.data, 0,  WIN_H * WIN_W * 4);
		printf("%d\n", texture_pitch);

			// t_color c = (t_color) {255, 255, 255};
			// int color = rgb_to_int(c);
 			/* int y = 0;
			while (y < WIN_H)
			{
				int x = 0;
				while (x < WIN_W)
				{
					img_pixel_put(&ctx.frame_buffer, x, y, 0xFFFFFF00);
					x++;
				}
				y++;
			}  */
			img_pixel_put(&ctx.frame_buffer, WIN_W / 2, WIN_H /2, 0xFFFFFFFF);

			//buffer_copy(texture_data, ctx.frame_buffer.data, ctx.frame_buffer.bits_per_pixel);
			ft_memcpy(texture_data, ctx.frame_buffer.data, WIN_H * WIN_W * 4);
			SDL_UnlockTexture(ctx.texture);
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