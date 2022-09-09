/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel_put_color.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaarine <jsaarine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 12:20:23 by jsaarine          #+#    #+#             */
/*   Updated: 2022/09/09 13:55:09 by jsaarine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"
#include "vec3.h"

void	img_pixel_put(t_frame_buffer *fb, unsigned long x,
	unsigned long y, unsigned int color)
{
	char	*dst;

	dst = fb->data + (y * WIN_W + x) * 4;
	*(unsigned int *)dst = color;
}

int	rgb_to_int(int r, int g, int b)
{
	return (r << 24 | g << 16 | b << 8);
}
