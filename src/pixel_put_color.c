/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel_put_color.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaarine <jsaarine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 12:20:23 by jsaarine          #+#    #+#             */
/*   Updated: 2022/08/01 17:16:03 by jsaarine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/RTv1.h"

void	img_pixel_put(t_frame_buffer *fb, unsigned long x, 
	unsigned long y, unsigned int color)
{
	char	*dst;

	dst = fb->data + (y * WIN_W + x );
	*(unsigned int *)dst = color;
}

int	rgb_to_int(t_color c)
{
	return ((int)c.x << 16 | (int)c.y << 8 | (int)c.z);
}
