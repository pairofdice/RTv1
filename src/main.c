/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaarine <jsaarine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 19:46:34 by jsaarine          #+#    #+#             */
/*   Updated: 2022/09/26 20:41:59 by jsaarine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"
#include <stdbool.h>
#include <stdio.h>

void	close_rtv1(t_context *ctx)
{
	vec_free(&ctx->scene);
	free(ctx->frame_buffer.data);
	SDL_DestroyWindow(ctx->window);
	SDL_DestroyTexture(ctx->texture);
	SDL_DestroyRenderer(ctx->renderer);
	ctx->window = NULL;
	SDL_Quit();
	exit(0);
}

/* void test_load(t_context * ctx)
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
 */
void	handle_events(SDL_Event e);

int	main(int argc, char **argv)
{
	t_context ctx;

	if (!init(&ctx))
	{
		printf("Failed to initialize!\n");
		close_rtv1(&ctx);
	}
	else
	{
		handle_args(argc, argv, &ctx);
		ctx.quit = FALSE;
		SDL_Event e;
		int texture_pitch;
		int *texture_data;
		texture_data = NULL;
		write_buffer(&ctx, texture_data, &texture_pitch, RENDER);
		while (!ctx.quit)
		{
			// handle_events();
			if (SDL_WaitEvent(&e) != 0)
			{
				if (e.type == SDL_QUIT)
					ctx.quit = true;
				else if (e.type == SDL_WINDOWEVENT)
				{
					
					if (e.window.event == SDL_WINDOWEVENT_EXPOSED)
						write_buffer(&ctx, texture_data, &texture_pitch, NO_RENDER);
				}
				else if (e.type == SDL_KEYDOWN)
				{
					if (e.key.keysym.sym == SDLK_ESCAPE)
						ctx.quit = true;
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
			SDL_RenderCopy(ctx.renderer, ctx.texture, NULL, NULL);
			SDL_RenderPresent(ctx.renderer);
		}
	}
	close_rtv1(&ctx);
	return 0;
}
