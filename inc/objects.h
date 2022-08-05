/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaarine <jsaarine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 16:37:24 by jsaarine          #+#    #+#             */
/*   Updated: 2022/08/04 17:40:28 by jsaarine         ###   ########.fr       */
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




#endif
