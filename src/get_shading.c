/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_shading.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaarine <jsaarine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 15:23:03 by jsaarine          #+#    #+#             */
/*   Updated: 2022/08/17 18:04:09 by jsaarine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// get_shading(normal, light, &SPHERES,ctx->cam.closest_id);
 
//#include "vec3.h"
//#include "objects.h"
#include "RTv1.h"


double	get_shading(t_ray normal, t_point light, t_ray incoming/* , t_object *SPHERES[6], int id */)
{
	// t_vec3 temp;
	t_vec3	to_light;
	double	dot;

	//temp = vec3_reflect(vec3_unit(incoming.dir), normal);
	to_light = vec3_sub(light, normal.orig);
	if (incoming.orig.x == 0)
	{}
	dot = vec3_dot(normal.dir, vec3_unit(to_light));
	if (dot < 0)
		dot = 0;
	dot = dot * sqrt(vec3_mag(to_light));
	return (dot);
}