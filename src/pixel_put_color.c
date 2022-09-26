/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel_put_color.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaarine <jsaarine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 12:20:23 by jsaarine          #+#    #+#             */
/*   Updated: 2022/09/26 17:05:23 by jsaarine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"
#include "vec3.h"

void	img_pixel_put(t_frame_buffer *fb, unsigned long x,
	unsigned long y, t_color color)
{
	char			*dst;
	unsigned int	color_int;

	color_int = rgb_to_int(color.x, color.y, color.z);
	dst = fb->data + (y * WIN_W + x) * 4;
	*(unsigned int *)dst = color_int;
}

int	rgb_to_int(int r, int g, int b)
{
	return (r << 24 | g << 16 | b << 8);
}
