/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quadratic.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaarine <jsaarine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 10:49:20 by jsaarine          #+#    #+#             */
/*   Updated: 2022/09/26 13:11:56 by jsaarine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "../inc/objects.h"

double	calc_b2_4ac(t_abc abc)
{
	return (abc.b * abc.b - 4 * abc.a * abc.c);
}

double	quadratic(t_abc abc, double b2_4ac)
{
	double	result_m;
	double	result_p;
	double	denominator;

	if (b2_4ac < 0)
		b2_4ac *= -1;
	denominator = -abc.b - sqrt(b2_4ac);
	result_m = denominator / (2 * abc.a);
	denominator = -abc.b + sqrt(b2_4ac);
	result_p = denominator / (2 * abc.a);
	if (result_p < result_m)
		return (result_p);
	return (result_m);
}
