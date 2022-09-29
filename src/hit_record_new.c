/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_record_new.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaarine <jsaarine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 14:14:56 by jsaarine          #+#    #+#             */
/*   Updated: 2022/09/29 15:38:34 by jsaarine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/RTv1.h"

t_hit_record	hit_record_new(void)
{
	t_hit_record	hit;

	hit.closest_distance = INFINITY;
	hit.max_distance = INFINITY;
	hit.closest_id = -1;
	hit.is_hit = 0;
	return (hit);
}
