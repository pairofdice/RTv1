/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaarine <jsaarine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 16:37:24 by jsaarine          #+#    #+#             */
/*   Updated: 2022/08/10 15:08:03 by jsaarine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef VEC3_H
# define VEC3_H

typedef struct s_vec3
{
	double	x;
	double	y;
	double	z;
}	t_vec3;

typedef t_vec3	t_color;
typedef t_vec3	t_point;

typedef struct s_ray
{
	t_point	orig;
	t_vec3	dir;
}	t_ray;

int		rgb_to_int(t_color c);
t_vec3	vec3_add(t_vec3 i, t_vec3 j);
double	vec3_mag(t_vec3 i);
t_vec3	vec3_scalar_mult(t_vec3 u, double x);
t_vec3	vec3_cross(t_vec3 u, t_vec3 v);
t_vec3	vec3_unit(t_vec3 u);
t_vec3	vec3_sub(t_vec3 u, t_vec3 v);
t_vec3	vec3_neg(t_vec3 u);




#endif
