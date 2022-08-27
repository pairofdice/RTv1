/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaarine <jsaarine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 16:37:24 by jsaarine          #+#    #+#             */
/*   Updated: 2022/08/26 17:14:47 by jsaarine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECTS_H
#define OBJECTS_H

#include "vec3.h"
#define EPSILON 0.000001

enum
{
	SPHERE,
	PLANE,
	CYLINDER,
	NOT_LIGHT,
	LIGHT,
};

typedef struct s_object
{
	t_point loc;
	t_vec3 rot;
	double size;
	int r;
	int g;
	int b;
	int type;
} t_object;

typedef struct s_light
{
	t_point loc;
	t_color color;
	double intensity;
} t_light;

typedef struct s_abc
{
	double a;
	double b;
	double c;
} t_abc;

typedef struct s_cam
{

	t_point loc;
	t_vec3 dir;
	t_vec3 up;
	t_vec3 right;
	t_vec3 n;
	t_point coi;
	t_vec3 scene_up;
	// pp = projection plane
	double distance_to_proj;
	t_vec3 cam_to_proj;
	t_vec3 projection_plane_center;
	double projection_plane_h;
	double projection_plane_w;
	double aspect;
	// double	closest_hit;
	// int		is_hit;
	// int		closest_id;
} t_cam;

#endif
