/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RTv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaarine <jsaarine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 16:16:55 by jsaarine          #+#    #+#             */
/*   Updated: 2022/08/18 18:13:12 by jsaarine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_H
# define RTV1_H
# include "../libsdl2/include/SDL.h"
#include "objects.h"
//# include "../sdl_include/SDL.h"

# define WIN_W 1024
# define WIN_H 768
# define NUM_SPHERES 12

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
	
	t_object		SPHERES[NUM_SPHERES];
}	t_context;

void	tests(void);


int			init(t_context *ctx);
void		close(t_context *ctx);
void		*ft_memcpy(void *dst, const void *src, size_t n);
void		*ft_memset(void *b, unsigned char c, size_t len);
int			intersects_sphere(t_ray *ray, t_object *sphere, double *distance, int debug);
t_object	sphere_new(t_vec3 sphere_loc, double radius, int r, int g, int b);
void		draw(t_context *ctx);
t_vec3		get_normal(t_vec3 sphere_loc, t_ray ray, double distance);
t_vec3		vec3_new(double x, double y, double z);
double		get_shading_diffuse(t_ray normal, t_point light, t_ray incoming, t_context *ctx, int id);
void		img_pixel_put(t_frame_buffer *fb, unsigned long x, unsigned long y, unsigned int color);


#endif
