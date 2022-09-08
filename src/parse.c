/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaarine <jsaarine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 16:09:56 by jsaarine          #+#    #+#             */
/*   Updated: 2022/09/08 16:27:41 by jsaarine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/RTv1.h"


void	check_type(char **str, t_context *ctx) 
{
	char *temp;
	temp = *(++str);
	printf("\nChecking type? -%s-", temp);

	if (ft_strcmp(*str, "light") == 0)
		ctx->obj.type = LIGHT;
	else if (ft_strcmp(*str, "cone") == 0)
		ctx->obj.type = CONE;
	else if (ft_strcmp(*str, "plane") == 0)
		ctx->obj.type = PLANE;
	else if (ft_strcmp(*str, "cylinder") == 0)
		ctx->obj.type = CYLINDER;
	else if (ft_strcmp(*str, "sphere") == 0)
		ctx->obj.type = SPHERE;
}
