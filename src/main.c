/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaarine <jsaarine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 19:46:34 by jsaarine          #+#    #+#             */
/*   Updated: 2022/09/28 17:37:19 by jsaarine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"
#include <stdbool.h>
#include <stdio.h>

void	close_rtv1(t_context *ctx)
{
	vec_free(&ctx->scene);
	ft_memdel((void **)&ctx->frame_buffer.data);
	SDL_DestroyWindow(ctx->window);
	ctx->window = NULL;
	SDL_DestroyTexture(ctx->texture);
	ctx->texture = NULL;
	SDL_DestroyRenderer(ctx->renderer);
	ctx->window = NULL;
	SDL_Quit();
	exit(0);
}

void	move_cam(t_context *ctx, t_vec3 dir)
{
	t_point loc = ctx->cam.loc;
	loc = vec3_add(loc, dir);
	init_camera(&ctx->cam, loc);
	draw(ctx);
	write_buffer(ctx, ctx->frame_buffer.texture_data, &ctx->frame_buffer.texture_pitch);
}

void	handle_events(t_context *ctx)
{
	if (ctx->e.key.keysym.sym == SDLK_ESCAPE)
		ctx->quit = true;
	if (ctx->e.key.keysym.sym == SDLK_w)
		move_cam(ctx, ctx->cam.dir);
	if (ctx->e.key.keysym.sym == SDLK_a)
		move_cam(ctx, vec3_neg(ctx->cam.right));
	if (ctx->e.key.keysym.sym == SDLK_s)
		move_cam(ctx, vec3_neg(ctx->cam.dir));
	if (ctx->e.key.keysym.sym == SDLK_d)
		move_cam(ctx, ctx->cam.right);
}

void	run_rtv1(t_context *ctx)
{
	while (!ctx->quit)
	{
		if (SDL_WaitEvent(&ctx->e) != 0)
		{
			if (ctx->e.type == SDL_QUIT)
				ctx->quit = true;
			else if (ctx->e.type == SDL_WINDOWEVENT)
			{
				if (ctx->e.window.event == SDL_WINDOWEVENT_EXPOSED)
					write_buffer(ctx, ctx->frame_buffer.texture_data, &  ctx->frame_buffer.texture_pitch);
			}
			else if (ctx->e.type == SDL_KEYDOWN)
				handle_events(ctx);
		}
	}
}

int	main(int argc, char **argv)
{
	t_context ctx;

	init(&ctx);
	handle_args(argc, argv, &ctx);	
	draw(&ctx);
	run_rtv1(&ctx);
	close_rtv1(&ctx);
	return 0;
}
