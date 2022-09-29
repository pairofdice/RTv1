/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_new.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaarine <jsaarine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 18:22:59 by jsaarine          #+#    #+#             */
/*   Updated: 2022/09/29 15:46:37 by jsaarine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/RTv1.h"

t_light	light_new(t_point loc, t_color color, double intensity)
{
	t_light	light;

	light.loc = loc;
	light.color = color;
	light.intensity = intensity;
	return (light);
}
