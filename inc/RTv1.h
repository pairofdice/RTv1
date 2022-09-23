/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RTv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaarine <jsaarine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 16:16:55 by jsaarine          #+#    #+#             */
/*   Updated: 2022/09/23 15:31:46 by jsaarine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_H
#define RTV1_H

#include "../libft/libft.h"
#include <unistd.h>
#include <fcntl.h>
# include <stdlib.h>
#include "objects.h"
# include "../libsdl2/include/SDL.h"
// #include "../sdl_include/SDL.h"

#define WIN_W 1601
#define WIN_H 1043
#define NUM_OBJECTS 1
#define GAMMA 2.2
#define AMBIENT 0.0001
#define RENDER 1
#define NO_RENDER 0
#define TRUE 1
#define FALSE 0

// #define BUFF_SIZE 110
//# define MAX_FD 8192


typedef struct s_hit_record
{
	t_point loc;
	t_vec3 normal;
	int is_hit;
	double max_distance;
	double closest_distance;
	int closest_id;
	t_color color;
} t_hit_record;

typedef struct s_frame_buffer
{
	// void	*img;
	// int		endian;
	char *data;
	size_t bits_per_pixel;
	unsigned long line_length;
	int height;

} t_frame_buffer;

typedef struct s_context
{
	SDL_Window		*window;
	SDL_Renderer	*renderer;
	// SDL_Surface		*screen_surface;
	SDL_Texture		*texture;
	t_frame_buffer	frame_buffer;
	t_cam			cam;
	t_ray			ray;
	t_light			ambient;
	t_light			light;
	t_ray			normal;
	// t_object		OBJECTS[NUM_OBJECTS];
	t_hit_record	hit;
	t_vec			scene;
	int				parse_state;
	t_object		obj;
	char			**words;
	char			**temp;
	char			*line;
	int				render;
	int 			quit;
	int				gnl; // if gnl fails, error handling

} t_context;

void tests(void);

void close_rtv1(t_context *ctx);
int		init(t_context *ctx);
void	close_rtv1(t_context *ctx);


void	draw(t_context *ctx);
void	write_buffer(t_context *ctx, int *texture_data, int *texture_pitch, int render);

t_vec3	vec3_new(double x, double y, double z);
double	get_light_level(t_ray normal, t_point light, t_ray ray, t_context *ctx, size_t id);
t_color	debug_shading(t_vec3 normal);
t_color	shade(t_object obj, double shading, t_light *ambient);
void	init_camera(t_cam *cam, t_point loc);
void	img_pixel_put(t_frame_buffer *fb, unsigned long x, unsigned long y, unsigned int color);
t_light	light_new(t_point loc, t_color color, double intensity);
t_hit_record	hit_record_new();
void	intersects(t_context *ctx, double distance, int light);
t_object	sphere_new(t_vec3 sphere_loc, double radius, int r, int g, int b);
t_object	plane_new(t_vec3 plane_loc, t_vec3 plane_rot, int r, int g, int b);
t_object	cylinder_new(t_vec3 loc, t_vec3 rot, double radius, int r, int g, int b);
t_object	cone_new(t_vec3 loc, t_vec3 rot, double radius, t_color c);
int		intersects_sphere(t_ray *ray, t_object *sphere, double *distance);
int		intersects_plane(t_ray *ray, t_object *plane, double *distance);
int		intersects_cylinder(t_ray *ray, t_object *cylinder, double *distance);
int		intersects_cone(t_ray *ray, t_object *cone, double *distance);
// t_vec3		get_plane_normal(t_vec3 plane_loc, t_ray ray, double distance);
t_vec3	get_sphere_normal(t_context *ctx);
t_vec3	get_plane_normal(t_context *ctx);
t_vec3	get_cylinder_normal(t_context *ctx);
t_vec3	get_cone_normal(t_context *ctx);
int		handle_args(int argc, char **argv, t_context *ctx);
int		load_scene(int fd, t_context *ctx);
void	check_type(char **str, t_context *ctx);
//char *skip_whitespace(char *str);
t_point read_triple(t_context *ctx, char **strs);
int	ft_atof(char *str, float *result);
void init_camera(t_cam *cam, t_point loc);
void	calc_current_ray(t_context *ctx, int x, int y);





#endif
