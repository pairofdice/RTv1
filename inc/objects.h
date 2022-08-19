/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaarine <jsaarine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 16:37:24 by jsaarine          #+#    #+#             */
/*   Updated: 2022/08/19 14:56:57 by jsaarine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef OBJECTS_H
# define OBJECTS_H

# include "vec3.h"
# define SPHERE 1
# define PLANE 2

typedef struct s_object
{
	t_point	loc;
	t_vec3	rot;
	double size;
	int		r;
	int		g;
	int		b;
	int		type;
}	t_object;

typedef struct s_cam
{
	
	t_point	loc;
	t_vec3	dir;
	t_vec3	up;
	t_vec3	right;
	t_vec3	n;
	t_point	coi;
	t_vec3	scene_up;
	// pp = projection plane
	double	distance_to_proj;
	t_vec3	cam_to_proj;
	t_vec3	projection_plane_center;
	double	projection_plane_h;
	double	projection_plane_w;
	double	aspect;
	double	closest_hit;
	int		is_hit;
	int		closest_id;
} t_cam;




#endif
