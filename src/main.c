/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaarine <jsaarine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 19:46:34 by jsaarine          #+#    #+#             */
/*   Updated: 2022/09/08 14:43:34 by jsaarine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "../inc/RTv1.h"
#include "RTv1.h"
#include <stdbool.h>
#include <stdio.h>

void close_rtv1(t_context *ctx) 
{
	// Destroy window
	SDL_DestroyWindow(ctx->window);
	ctx->window = NULL;
	// Quit SDL subsystems
	SDL_Quit();
}

void test_load(t_context * ctx)
{
	size_t i;
	t_object o;

	printf("\n--- ctx->scene contents:\n");
	i = 0;
	while (i < ctx->scene.len)
	{
		o = *(t_object *) vec_get(&ctx->scene, i);
		printf("obj type: %d\n", o.type);
		printf("obj loc:  %f %f %f\n", o.loc.x, o.loc.y, o.loc.z);
		printf("obj color:  %f %f %f\n", o.color.x, o.color.y, o.color.z);

		i++;
	}
}

int main(int argc, char **argv)
{
	t_context ctx;

	//tests();
	// Start up SDL and create window



	
	if (!init(&ctx))
	{
		printf("Failed to initialize!\n");
		close_rtv1(&ctx);
	}
	else
	{
		//handle_args(int argc, char **argv, t_context *ctx)
		handle_args(argc, argv, &ctx);
		test_load(&ctx);
		// Main loop flag
		bool quit = false;
		// Event handler
		SDL_Event e;

		// While application is running
		int texture_pitch;
		int *texture_data;
		texture_data = NULL;
		write_buffer(&ctx, texture_data, &texture_pitch, RENDER);
		while (!quit)
		{
			// Handle events on queue
			if (SDL_WaitEvent(&e) != 0)
			{
				// User requests quit
				if (e.type == SDL_QUIT)
				{
					quit = true;
				}
				if (e.type == SDL_WINDOWEVENT)
				{
					if (e.window.event == SDL_WINDOWEVENT_EXPOSED)
						//printf("Exposed!\n");
						write_buffer(&ctx, texture_data, &texture_pitch, NO_RENDER);
				}
				if (e.type == SDL_KEYDOWN)
				{
					if (e.key.keysym.sym == SDLK_ESCAPE)
					{
						quit = true;
					}
					if (e.key.keysym.sym == SDLK_w)
					{
						printf("W!\n");
						t_point loc = ctx.cam.loc;
						t_vec3 dir = ctx.cam.dir;
						loc = vec3_add(loc, dir);
						init_camera(&ctx.cam, loc);
						write_buffer(&ctx, texture_data, &texture_pitch, RENDER);
					}
					if (e.key.keysym.sym == SDLK_a)
					{
						printf("A!\n");
						t_point loc = ctx.cam.loc;
						t_vec3 dir = vec3_neg(ctx.cam.right);
						loc = vec3_add(loc, dir);
						init_camera(&ctx.cam, loc);
						write_buffer(&ctx, texture_data, &texture_pitch, RENDER);
					}
					if (e.key.keysym.sym == SDLK_s)
					{
						printf("Q!\n");
						t_point loc = ctx.cam.loc;
						t_vec3 dir = vec3_neg(ctx.cam.dir);
						loc = vec3_add(loc, dir);
						init_camera(&ctx.cam, loc);
						write_buffer(&ctx, texture_data, &texture_pitch, RENDER);
					}
					if (e.key.keysym.sym == SDLK_d)
					{
						printf("Q!\n");
						t_point loc = ctx.cam.loc;
						t_vec3 dir = ctx.cam.right;
						loc = vec3_add(loc, dir);
						init_camera(&ctx.cam, loc);
						write_buffer(&ctx, texture_data, &texture_pitch, RENDER);
					}
				}
			}
			// Render texture to screen
			SDL_RenderCopy(ctx.renderer, ctx.texture, NULL, NULL);
			// Update screen
			SDL_RenderPresent(ctx.renderer);
		}
	}
	// Free resources and close SDL
	close_rtv1(&ctx);
	return 0;
}
