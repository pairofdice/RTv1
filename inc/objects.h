/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaarine <jsaarine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 16:37:24 by jsaarine          #+#    #+#             */
/*   Updated: 2022/08/09 20:56:47 by jsaarine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef OBJECTS_H
# define OBJECTS_H

# include "vec3.h"

typedef struct s_object
{
	t_point	o;
	t_vec3	rot;
	double size;
}	t_object;

typedef struct s_cam
{
	t_point	loc;
	t_vec3	dir;
	t_vec3	up;
	t_vec3	right;
	t_vec3	n;
} t_cam;




#endif
