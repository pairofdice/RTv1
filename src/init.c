/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaarine <jsaarine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 16:09:22 by jsaarine          #+#    #+#             */
/*   Updated: 2022/09/28 17:12:03 by jsaarine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"
#include "objects.h"

int st_error()
{
	// TODO
	printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
	return (0);
}

t_vec3 new_vec3()
{
	t_vec3 v;

	v.x = 0.0;
	v.y = 0.0;
	v.z = 0.0;
	return (v);
}

t_object default_object()
{
	t_object o;

	o.type = NOTHING;
	o.loc = new_vec3();
	o.rot = new_vec3();
	o.color = new_vec3();
	o.brightness = 100.0;
	o.size = 1.0;
	return (o);
}

int init(t_context *ctx)
{
	t_cam cam;
	//ctx->OBJECTS[0] = sphere_new((t_vec3){0.0, 0.0, -10.0}, 5.0, 255, 223, 196);
	//
	ctx->parse_state = NOTHING;
	//ctx->parse_obj.type = NOTHING;
	ctx->obj = default_object();
	ctx->hit = hit_record_new();
	printf("id in init? %d \n", ctx->obj.type);
	cam.scene_up = (t_point){0.0, 1.0, 0.0};
	//cam.scene_up = vec3_neg(vec3_unit(cam.scene_up));
	init_camera(&cam, (t_point){0.0, 0.0, 7.0});
	ctx->ambient = light_new((t_point){0, 0, 0}, (t_color){0.1, 0.1, 0.2}, 0.001);
	ctx->cam = cam;
	// The window we'll be rendering to
	ctx->window = NULL;
	// The surface contained by the window
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
		close_rtv1(ctx); // printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
	ctx->window = SDL_CreateWindow("RTv1", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIN_W, WIN_H, SDL_WINDOW_ALLOW_HIGHDPI);
	if (ctx->window == NULL)
		close_rtv1(ctx); // printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
	ctx->renderer = SDL_CreateRenderer(ctx->window, -1, 0);
	if (ctx->renderer == NULL)
		close_rtv1(ctx);
	ctx->texture = SDL_CreateTexture(ctx->renderer, SDL_PIXELFORMAT_RGBA8888,
									 SDL_TEXTUREACCESS_STREAMING, WIN_W, WIN_H);
	if (ctx->texture == NULL)
		close_rtv1(ctx);
	ctx->frame_buffer.data = (char *)malloc(WIN_H * WIN_W * 4);
	if (!ctx->frame_buffer.data)
		close_rtv1(ctx);
	ctx->frame_buffer.texture_data = NULL;
	ctx->quit = FALSE;
	
	//handle_args(int argc, char **argv, t_context *ctx)
	return (1);
}
