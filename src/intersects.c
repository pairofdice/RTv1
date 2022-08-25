/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersects.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaarine <jsaarine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 16:16:59 by jsaarine          #+#    #+#             */
/*   Updated: 2022/08/25 17:16:53 by jsaarine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/RTv1.h"

void	update_hit_record(t_hit_record *hit, double *distance, int i)
{
	hit->is_hit = 1;
	if (*distance < hit->closest_distance)
	{
		hit->closest_distance = *distance;
		hit->closest_id = i;
	}
}

void	intersects(t_context *ctx, double distance, int light)
{
	int i;

	i = 0;
	ctx->hit = hit_record_new();
	while (i < NUM_OBJECTS)
	{
		if (ctx->OBJECTS[i].type == SPHERE)
		{
			if (intersects_sphere(&ctx->ray, &ctx->OBJECTS[i], &distance, 0))
				update_hit_record(&ctx->hit, &distance, i);
		}
		else if (ctx->OBJECTS[i].type == PLANE)
		{
			if (intersects_plane(&ctx->ray, &ctx->OBJECTS[i], &distance))
				update_hit_record(&ctx->hit, &distance, i);
		}
		i++;
	}
}