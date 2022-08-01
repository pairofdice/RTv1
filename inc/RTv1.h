/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RTv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaarine <jsaarine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 16:16:55 by jsaarine          #+#    #+#             */
/*   Updated: 2022/08/01 18:03:23 by jsaarine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_H
# define RTV1_H
//#include "../libsdl2/include/SDL.h"
# include "SDL.h"

# define WIN_W 1024
# define WIN_H 768

typedef struct s_frame_buffer
{
	//void	*img;
	//int		endian;
	char	*data;
	size_t	bits_per_pixel;
	unsigned long		line_length;
	int		height;

}	t_frame_buffer;

typedef struct s_vec_3d
{
	double	x;
	double	y;
	double	z;
}	t_vec_3d;

typedef t_vec_3d	t_color;

typedef struct s_context
{
	SDL_Window		*window;
	SDL_Renderer	*renderer;
	// SDL_Surface		*screen_surface;
	SDL_Texture		*texture;
	t_frame_buffer	frame_buffer;
}	t_context;

void	tests(void);
int		init(t_context *ctx);
void	close(t_context *ctx);
void	*ft_memcpy(void *dst, const void *src, size_t n);
void	*ft_memset(void *b, unsigned char c, size_t len);

int		rgb_to_int(t_color c);
void	img_pixel_put(t_frame_buffer *fb, unsigned long x, unsigned long y, unsigned int color);


#endif
