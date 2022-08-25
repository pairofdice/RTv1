/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_record_new.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaarine <jsaarine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 14:14:56 by jsaarine          #+#    #+#             */
/*   Updated: 2022/08/25 16:56:45 by jsaarine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/RTv1.h"

t_hit_record	hit_record_new()
{
	t_hit_record	hit;

	hit.closest_distance = 1.0/0.0;
	hit.max_distance = 1.0/0.0;
	hit.closest_id = -1;
	hit.is_hit = 0;
/* 	hit.loc;
	hit.normal; */
	return (hit);
}