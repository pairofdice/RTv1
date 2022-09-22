/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaarine <jsaarine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 16:09:56 by jsaarine          #+#    #+#             */
/*   Updated: 2022/09/22 14:59:22 by jsaarine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/RTv1.h"

int	ft_atof(char *str, float *result) // return type to int/error and give pointer to float
{
	int		fraction;
	int		fraction_len;
	float	neg;
	int		i;

	neg = 1.0;
	if (!str)
		return (0);
	while (st)
	if (*str == '-')
	{
		neg = -1.0;
	}
	*result = ft_abs(ft_atoi(str));
	str = ft_strchr(str, '.');
	str++;
	fraction = ft_abs(ft_atoi(str));
	fraction_len = ft_nbrlen(fraction);
	*result += (float)fraction / pow(10, fraction_len);
	return (*result * neg);
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

t_point	read_triple(t_context *ctx, char **strs) // return type to int/error and give pointer to values isnum
{
	t_point	p;

	p.x = 0.0;
	p.y = 0.0;
	p.z = 0.0;
	if (!check_triple_length(++strs))
		return (p);
	if (!(ft_isdigit(strs[0]) && ft_isdigit(strs[0]) && ft_isdigit(strs[0])))
		return (p);
	if (strs[0])
	p.x = ft_atof(strs[0]);
	p.y = ft_atof(strs[1]);
	p.z = ft_atof(strs[2]);
	return (p);
}

void	check_type(char **str, t_context *ctx)
{
	char	*temp;

	ctx->parse_state = PROCESSING;
	temp = *(++str);
	if (ft_strncmp(*str, "light", 5) == 0)
		ctx->obj.type = LIGHT;
	else if (ft_strncmp(*str, "cone", 4) == 0)
		ctx->obj.type = CONE;
	else if (ft_strncmp(*str, "plane", 5) == 0)
		ctx->obj.type = PLANE;
	else if (ft_strncmp(*str, "cylinder", 8) == 0)
		ctx->obj.type = CYLINDER;
	else if (ft_strncmp(*str, "sphere", 6) == 0)
		ctx->obj.type = SPHERE;
	else if (ft_strncmp(*str, "camera", 6) == 0)
		ctx->obj.type = CAMERA;
}
