/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_reflect.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaarine <jsaarine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 16:14:47 by jsaarine          #+#    #+#             */
/*   Updated: 2022/08/17 17:40:13 by jsaarine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec3.h"
#include "stdio.h"


t_vec3	vec3_reflect(t_vec3 incoming, t_ray normal)
{
	t_vec3	result;
	//t_vec3	c;
	
	// c = incoming;
	//printf("1: %f %f %f", c.x, c.y, c.z);
	// c = normal.d;
	//printf("2: %f %f %f", c.x, c.y, c.z);
	// c = normal;
	//printf("2: %f ", vec3_dot(incoming, normal.dir));
	result = vec3_ray_at(normal, vec3_dot(incoming, normal.dir));
	result = vec3_add(result, result);
	result = vec3_add(result, incoming);
	return (result);
}