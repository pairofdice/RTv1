/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaarine <jsaarine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 19:46:37 by jsaarine          #+#    #+#             */
/*   Updated: 2022/08/26 18:32:42 by jsaarine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
//#include "../libsdl2/include/SDL.h"
#include "RTv1.h"
#include "objects.h"
#include "vec3.h"

void vector_math()
{
	t_vec3 a;
	t_vec3 b;
	t_vec3 c;
	t_vec3 e;
	double d;

	a.x = 1.0;
	a.y = 2.0;
	a.z = 3.0;
	b.x = 4.0;
	b.y = 5.0;
	b.z = 6.0;
	e.x = -0.4;
	e.y = -0.5;
	e.z = -0.6;
	c = vec3_add(a, b);
	printf("%f %f %f\n", c.x, c.y, c.z);
	c = vec3_sub(a, b);
	printf("%f %f %f\n", c.x, c.y, c.z);
	c = vec3_scalar_mult(a, 0.5);
	printf("%f %f %f\n", c.x, c.y, c.z);
	c = vec3_unit(a);
	printf("%f %f %f\n", c.x, c.y, c.z);
	c = vec3_unit(b);
	printf("%f %f %f\n", c.x, c.y, c.z);
	c = vec3_cross(a, b);
	printf("cross Should be -3, 6, -3, is: %f %f %f\n", c.x, c.y, c.z);
	c = vec3_cross(b, a);
	printf("cross Should be 3, -6, 3, is: %f %f %f\n", c.x, c.y, c.z);
	d = vec3_dot(a, b);
	printf("dot Should be 32, is: %f \n", d);
	d = vec3_dot(e, b);
	printf("dot Should be -7.7, is: %f \n", d);
	d = vec3_mag(a);
	printf("1, 2, 3 mag should be 3.74, is: %f \n", d);
	d = vec3_mag(e);
	printf("-0.4, -0.5, -0.6 mag should be 0.87749, is: %f \n", d);
	c = vec3_neg(a);
	printf("neg Should be -1, -2, -3, is: %f %f %f\n", c.x, c.y, c.z);
	c = vec3_unit(a);
	printf("unit Should be 0.26726, 0.53452, 0.80178, is: %f %f %f\n", c.x, c.y, c.z);
	c = vec3_unit(b);
	printf("unit Should be 0.45584, 0.5698, 0.68376, is: %f %f %f\n", c.x, c.y, c.z);
	c = vec3_unit(e);
	printf("unit Should be -0.455864, -0.5698, -0.68376, is: %f %f %f\n", c.x, c.y, c.z);
}

double t_calc_b2_4ac(t_abc abc)
{
	return (abc.b * abc.b - 4 * abc.a * abc.c);
}
void test_discriminant()
{
	t_abc abc;
	abc.a = 2;
	abc.b = 6;
	abc.c = 4;
	printf("discriminant Should be 4, is: %f\n", t_calc_b2_4ac(abc));
	abc.a = 2.5;
	abc.b = 7.6;
	abc.c = 4.1;
	printf("discriminant Should be 16.76, is: %f\n", t_calc_b2_4ac(abc));
	abc.a = -2.9;
	abc.b = 11.1;
	abc.c = 3.99;
	printf("discriminant Should be 169.494, is: %f\n", t_calc_b2_4ac(abc));
}

double t_quadratic(t_abc abc, double b2_4ac)
{
	double result_m;
	double result_p;
	double denominator;

	denominator = -(abc.b) - sqrt(b2_4ac);
	result_m = denominator / (2 * abc.a);
	denominator = -(abc.b) + sqrt(b2_4ac);
	result_p = denominator / (2 * abc.a);
	if (result_p < result_m)
		return (result_p);
	return (result_m);
}

void tests()
{
	// vector_math();
	// test_discriminant();
	t_abc abc;
	double b2_4ac;
	abc.a = -2.9;
	abc.b = 11.1;
	abc.c = 3.99;
	b2_4ac = t_calc_b2_4ac(abc);
	printf("discriminant Should be -0.330860, is: %f\n", t_quadratic(abc, b2_4ac));
	abc.a = 2.9;
	abc.b = 16.1;
	abc.c = 5.55;
	b2_4ac = t_calc_b2_4ac(abc);
	printf("discriminant Should be -5.18244, is: %f\n", t_quadratic(abc, b2_4ac));

	printf("ALL TESTS PASS!\n");
}
