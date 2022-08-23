/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RTv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaarine <jsaarine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 16:16:55 by jsaarine          #+#    #+#             */
/*   Updated: 2022/08/23 15:50:02 by jsaarine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_H
# define RTV1_H
#include "objects.h"
# include "../libsdl2/include/SDL.h"
// # include "../sdl_include/SDL.h"

# define WIN_W 1999
# define WIN_H 1234
# define NUM_OBJECTS 16

typedef struct s_frame_buffer
{
	//void	*img;
	//int		endian;
	char	*data;
	size_t	bits_per_pixel;
	unsigned long		line_length;
	int		height;

}	t_frame_buffer;

typedef struct s_context
{
	SDL_Window		*window;
	SDL_Renderer	*renderer;
	// SDL_Surface		*screen_surface;
	SDL_Texture		*texture;
	t_frame_buffer	frame_buffer;
	t_cam			cam;
	t_ray			ray;
	t_ray			normal;

	t_object		OBJECTS[NUM_OBJECTS];
}	t_context;

void	tests(void);


int		init(t_context *ctx);
void	close(t_context *ctx);
void	*ft_memcpy(void *dst, const void *src, size_t n);
void	*ft_memset(void *b, unsigned char c, size_t len);
int		intersects_sphere(t_ray *ray, t_object *sphere, double *distance, int debug);
int		intersects_plane(t_ray *ray, t_object *plane, double *distance);
t_object	sphere_new(t_vec3 sphere_loc, double radius, int r, int g, int b);
t_object	plane_new(t_vec3 plane_loc, t_vec3 plane_rot, int r, int g, int b);
void	draw(t_context *ctx);
t_vec3	get_sphere_normal(t_vec3 sphere_loc, t_ray ray, double distance);
// t_vec3	get_plane_normal(t_vec3 plane_loc, t_ray ray, double distance);
t_vec3	get_plane_normal(t_object plane, t_vec3 cam_to_plane);

t_vec3	vec3_new(double x, double y, double z);
double	get_light_level(t_ray normal, t_point light, t_ray ray, t_context *ctx, int id);
t_color debug_shading(t_vec3 normal);
t_color	shade(t_object obj, double shading);
void	init_camera(t_cam *cam, t_point loc);


void	img_pixel_put(t_frame_buffer *fb, unsigned long x, unsigned long y, unsigned int color);


#endif
