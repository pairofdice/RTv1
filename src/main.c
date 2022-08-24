/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaarine <jsaarine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 19:46:34 by jsaarine          #+#    #+#             */
/*   Updated: 2022/08/24 17:42:53 by jsaarine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "../inc/RTv1.h"
#include "RTv1.h"
#include <stdbool.h>
#include <stdio.h>

void close(t_context *ctx)
{
	//Destroy window
	SDL_DestroyWindow( ctx->window );
	ctx->window = NULL;
	//Quit SDL subsystems
	SDL_Quit();
}

int main( int argc, char* args[] )
{
	// tests();
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

		draw(&ctx);

		//buffer_copy(texture_data, ctx.frame_buffer.data, ctx.frame_buffer.bits_per_pixel);
		ft_memcpy(texture_data, ctx.frame_buffer.data, WIN_H * WIN_W * 4);
		SDL_UnlockTexture(ctx.texture);
		while( !quit )
		{
			//Handle events on queue
			if( SDL_WaitEvent( &e ) != 0 )
			{
				//User requests quit
				if( e.type == SDL_QUIT)
				{
					quit = true;
				}
				if (e.type == SDL_WINDOWEVENT)
				{
					if (e.window.event == SDL_WINDOWEVENT_EXPOSED)
					{
						// TODO
						// printf("Exposed!\n");
					}
				}
				if (e.type == SDL_KEYDOWN)
				{	
					if(e.key.keysym.sym == SDLK_ESCAPE)
					{
						quit = true;
					}
					if(e.key.keysym.sym == SDLK_w)
					{
						printf("W!\n");
						t_point loc = ctx.cam.loc;
						t_vec3 dir = ctx.cam.dir;
						loc = vec3_add(loc, dir);
						init_camera(&ctx.cam, loc);
						SDL_LockTexture(ctx.texture, NULL, (void **)&texture_data,	&texture_pitch);
						ctx.frame_buffer.data = malloc(WIN_H * WIN_W * 4);
						ft_memset( ctx.frame_buffer.data, 0,  WIN_H * WIN_W * 4);

						draw(&ctx);
						ft_memcpy(texture_data, ctx.frame_buffer.data, WIN_H * WIN_W * 4);
						SDL_UnlockTexture(ctx.texture);
						SDL_RenderCopy( ctx.renderer, ctx.texture, NULL, NULL );
						SDL_RenderPresent( ctx.renderer );
						
					}
					if(e.key.keysym.sym == SDLK_a)
					{
						printf("A!\n");
						t_point loc = ctx.cam.loc;
						t_vec3 dir = vec3_neg(ctx.cam.right);
						loc = vec3_add(loc, dir);
						init_camera(&ctx.cam, loc);
						SDL_LockTexture(ctx.texture, NULL, (void **)&texture_data,	&texture_pitch);
						ctx.frame_buffer.data = malloc(WIN_H * WIN_W * 4);
						ft_memset( ctx.frame_buffer.data, 0,  WIN_H * WIN_W * 4);

						draw(&ctx);
						ft_memcpy(texture_data, ctx.frame_buffer.data, WIN_H * WIN_W * 4);
						SDL_UnlockTexture(ctx.texture);
						SDL_RenderCopy( ctx.renderer, ctx.texture, NULL, NULL );
						SDL_RenderPresent( ctx.renderer );
						
					}
					if(e.key.keysym.sym == SDLK_s)
					{
						printf("Q!\n");
						t_point loc = ctx.cam.loc;
						t_vec3 dir = vec3_neg(ctx.cam.dir);
						loc = vec3_add(loc, dir);
						init_camera(&ctx.cam, loc);
						SDL_LockTexture(ctx.texture, NULL, (void **)&texture_data,	&texture_pitch);
						ctx.frame_buffer.data = malloc(WIN_H * WIN_W * 4);
						ft_memset( ctx.frame_buffer.data, 0,  WIN_H * WIN_W * 4);

						draw(&ctx);
						ft_memcpy(texture_data, ctx.frame_buffer.data, WIN_H * WIN_W * 4);
						SDL_UnlockTexture(ctx.texture);
						SDL_RenderCopy( ctx.renderer, ctx.texture, NULL, NULL );
						SDL_RenderPresent( ctx.renderer );
						
					}
					if(e.key.keysym.sym == SDLK_d)
					{
						printf("Q!\n");
						t_point loc = ctx.cam.loc;
						t_vec3 dir = ctx.cam.right;
						loc = vec3_add(loc, dir);
						init_camera(&ctx.cam, loc);
						SDL_LockTexture(ctx.texture, NULL, (void **)&texture_data,	&texture_pitch);
						ctx.frame_buffer.data = malloc(WIN_H * WIN_W * 4);
						ft_memset( ctx.frame_buffer.data, 0,  WIN_H * WIN_W * 4);

						draw(&ctx);
						ft_memcpy(texture_data, ctx.frame_buffer.data, WIN_H * WIN_W * 4);
						SDL_UnlockTexture(ctx.texture);
						SDL_RenderCopy( ctx.renderer, ctx.texture, NULL, NULL );
						SDL_RenderPresent( ctx.renderer );
						
					}
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
