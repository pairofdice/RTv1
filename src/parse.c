/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaarine <jsaarine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 16:09:56 by jsaarine          #+#    #+#             */
/*   Updated: 2022/09/09 14:07:12 by jsaarine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/RTv1.h"

float	ft_atof(char *str)
{
	float	result;
	int		fraction;
	int		fraction_len;
	float	neg;

	neg = 1.0;
	if (!str)
		return (0.0);
	if (*str == '-')
	{
		neg = -1.0;
	}
	result = ft_abs(ft_atoi(str));
	str = ft_strchr(str, '.');
	if (!str)
		return (0.0);
	str++;
	fraction = ft_abs(ft_atoi(str));
	fraction_len = ft_nbrlen(fraction);
	result += (float)fraction / pow(10, fraction_len);
	return (result * neg);
}

int	check_triple_length(char **strs)
{
	int	c;

	c = 0;
	while (strs[c] != 0)
		c++;
	if (c != 3)
		return (0);
	return (1);
}

t_point	read_triple(t_context *ctx, char **strs)
{
	t_point	p;
	int		valid;

	valid = 0;
	if (!check_triple_length(++strs))
		close_rtv1(ctx);
	if (strs[0])
	p.x = ft_atof(strs[0]);
	p.y = ft_atof(strs[1]);
	p.z = ft_atof(strs[2]);
	return (p);
}

void	check_type(char **str, t_context *ctx)
{
	char	*temp;

	temp = *(++str);
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
