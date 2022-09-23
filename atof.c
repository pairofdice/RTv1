/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atof.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaarine <jsaarine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 15:16:20 by jsaarine          #+#    #+#             */
/*   Updated: 2022/09/23 17:31:28 by jsaarine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <math.h>
#include "libft/libft.h"

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

// 1 = 1
// 2 = 10
// 4 = 100
// 8 = 1000

// return type to int/error and give pointer to float
int	ft_atof(char *str, float *result)
{
	int		fraction;
	int		fraction_len;
	float	neg;
	int		i;

	i = 1;
	neg = 1.0;
	*result = 0.0;
	if (!str || !is_valid_float(str))
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
	return (1);
}




static double    get_desimal_div(int count)
{
    double    ret;

    ret = 1.0;
    while (count != 0)
    {
        ret *= 10;
        count--;
    }
    return (ret);
}

double    ft_atofjj(char *line_arg_r)
{
    int        i;
    int        count;
    double    r;
    double    negative;

    negative = 1.0f;
    r = 0.0;
    i = 0;
    count = 1;
    if (line_arg_r[i] == '-')
    {
        negative = -1.0f;
        i++;
    }
    while (line_arg_r[i] >= '0' && line_arg_r[i] <= '9')
    {
        r += ((double)line_arg_r[i] - '0');
        if ((double)line_arg_r[++i] >= '0' && (double)line_arg_r[i] <= '9')
            r *= 10.0;
    }
    if (line_arg_r[i++] == '.')
        while (line_arg_r[i] >= '0' && line_arg_r[i] <= '9')
            r += ((double)line_arg_r[i++] - '0') / get_desimal_div(count++);
    return (r * (double)negative);
}
int	main(void)
{
	float	f;

	ft_atof("3asd.0", &f);
	printf("oma: 3asd.0 = %f\n", f);
	// printf("3asd.0 = %f\n", ft_atofjj(NULL));
	ft_atof("-1.2345", &f);
	printf("oma: -1.2345 = %f\n", f);
	ft_atof("--1.2345", &f);
	printf("oma: --1.2345 = %f\n", f);
	ft_atof("+-1.2345", &f);
	printf("oma: +-1.2345 = %f\n", f);
	ft_atof("1000.00", &f);
	printf("oma: 1000.00 = %f\n", f);
	ft_atof(".001", &f);
	printf("oma: .001 = %f\n", f);
	ft_atof(".04", &f);
	printf("oma: .04 = %f\n", f);
	ft_atof(".000099", &f);
	printf("oma: .000099 = %f\n", f);
	ft_atof("1000..00", &f);
	printf("oma: 1000..00 = %f\n", f);
	ft_atof("10.00.00", &f);
	printf("oma: 10.00.00 = %f\n", f);
	ft_atof(".001", &f);
	printf("oma: .001 = %f\n", f);
	ft_atof("1.65", &f);
	printf("oma: 1.65 = %f\n", f);

	printf("jj: 3asd.0 = %f\n", ft_atofjj("3asd.0"));
	// printf("3asd.0 = %f\n", ft_atofjj(NULL));
	printf("jj: -1.2345 = %f\n", ft_atofjj("-1.2345"));
	printf("jj: --1.2345 = %f\n", ft_atofjj("--1.2345"));
	printf("jj: +-1.2345 = %f\n", ft_atofjj("+-1.2345"));
	printf("jj: 1000.00 = %f\n", ft_atofjj("1000.00"));
	printf("jj: .001 = %f\n", ft_atofjj(".001"));
	printf("jj: 1000..00 = %f\n", ft_atofjj("1000..00"));
	printf("jj: 10.00.00 = %f\n", ft_atofjj("10.00.00"));
	printf("jj: .001 = %f\n", ft_atofjj(".001"));
}
