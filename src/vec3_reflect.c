/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_reflect.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaarine <jsaarine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 16:14:47 by jsaarine          #+#    #+#             */
/*   Updated: 2022/09/09 13:53:07 by jsaarine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec3.h"
#include "stdio.h"

t_vec3	vec3_reflect(t_vec3 incoming, t_ray normal)
{
	t_vec3	result;

	result = vec3_ray_at(normal, vec3_dot(incoming, normal.dir));
	result = vec3_add(result, result);
	result = vec3_add(result, incoming);
	return (result);
}
