/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaarine <jsaarine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 16:09:56 by jsaarine          #+#    #+#             */
/*   Updated: 2022/09/05 18:56:32 by jsaarine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/RTv1.h"


char *skip_whitespace(char *str)
{
	
	while (*str && *str == ft_iswhitespace(*str))
	{

		str++;
	}
	return (str);
}

void	check_type(char **str, t_context *ctx) 
{
	char *temp;
	temp = *(++str);
	printf("Checking type? -%s-", temp);

	if (ft_strcmp(*str, "light") == 0)
		ctx->parse_obj.type = LIGHT;
	else if (ft_strcmp(*str, "cone") == 0)
		ctx->parse_obj.type = CONE;
	else if (ft_strcmp(*str, "plane") == 0)
		ctx->parse_obj.type = PLANE;
	else if (ft_strcmp(*str, "cylinder") == 0)
		ctx->parse_obj.type = CYLINDER;
	else if (ft_strcmp(*str, "sphere") == 0)
		ctx->parse_obj.type = SPHERE;
}
