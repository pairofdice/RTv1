/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaarine <jsaarine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 16:09:56 by jsaarine          #+#    #+#             */
/*   Updated: 2022/09/23 16:54:09 by jsaarine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/RTv1.h"

int	is_valid_float(char *str)
{
	int	sign;

	sign = 0;
	if (*str == '-' || *str == '+')
		str++;
	while (*str != '\0' && ft_isdigit(*str))
	{
		str++;
	}
	if (*str != '.')
		return(0);
	str++;
	if (!ft_isdigit(*str))
		return (0);
	str++;
	while (*str != '\0')
	{
		if (!ft_isdigit(*str))
			return (0);
		str++;
	}
	return (1);
}

int	ft_atof(char *str, float *result) // return type to int/error and give pointer to float
{
	int		fraction;
	int		fraction_len;
	float	neg;
	int		i;

	i = 1;
	neg = 1.0;
	*result = 0.0;
	if (!str /* || !is_valid_float(str) */)
		return (0);
	if (*str == '-')
		neg = -1.0;
	*result = ft_abs(ft_atoi(str));
	str = ft_strchr(str, '.');
	str++;
	fraction = ft_abs(ft_atoi(str));
	fraction_len = ft_strlen(str);
	*result += ((float)fraction / pow(10, fraction_len));
	*result *= neg;
	printf("...%f...", *result);
	return (1);
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
	float	f;

	p.x = 0.0;
	p.y = 0.0;
	p.z = 0.0;
	if (!check_triple_length(++strs))
		return (p);
	printf("Hi _%s_\n", *strs);
	// while (*str != '\0')
	// 	str++;
/* 	if (!(ft_isdigit(strs[0]) && ft_isdigit(strs[0]) && ft_isdigit(strs[0])))
		return (p); */
	if (strs[0])
	// p.x = ft_atof(strs[0]);
	ft_atof(strs[0], &f);
	p.x = f;
	printf("p.x__%f___ %s\n", f, strs[0]);
	// p.y = ft_atof(strs[1]);
	ft_atof(strs[1], &f);
	p.y = f;
	ft_atof(strs[2], &f);
	p.z = f;
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
