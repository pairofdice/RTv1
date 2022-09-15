/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersects.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaarine <jsaarine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 16:16:59 by jsaarine          #+#    #+#             */
/*   Updated: 2022/09/15 19:18:03 by jsaarine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/RTv1.h"

void update_hit_record(t_hit_record *hit, double *distance, int i)
{
	hit->is_hit = 1;
	if (*distance < hit->closest_distance)
	{
		hit->closest_distance = *distance;
		hit->closest_id = i;
		
	}
}

void intersects(t_context *ctx, double distance, int light)
{
	size_t	i;

	i = 0;
	ctx->hit = hit_record_new();
	while (i < ctx->scene.len)
	{
	
		ctx->obj = *(t_object *)vec_get(&ctx->scene, i);
		if (ctx->obj.type == SPHERE)
		{
 			
			if (intersects_sphere(&ctx->ray, &ctx->obj, &distance))
			{
				
				if (light)
				{
				}
				update_hit_record(&ctx->hit, &distance, i); 
			}
		}
		else if (ctx->obj.type == PLANE)
		{
			if (intersects_plane(&ctx->ray, &ctx->obj, &distance))
				update_hit_record(&ctx->hit, &distance, i);
		}
		else if (ctx->obj.type == CYLINDER)
		{
			if (intersects_cylinder(&ctx->ray, &ctx->obj, &distance))
			{
				update_hit_record(&ctx->hit, &distance, i);
				
			}
		}
		else if (ctx->obj.type == CONE)
		{
			if (intersects_cone(&ctx->ray, &ctx->obj, &distance))
				update_hit_record(&ctx->hit, &distance, i);
		} 
		i++;
	}
}
