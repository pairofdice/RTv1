/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaarine <jsaarine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 19:46:37 by jsaarine          #+#    #+#             */
/*   Updated: 2022/08/15 15:27:45 by jsaarine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "../libsdl2/include/SDL.h"
#include "RTv1.h"
#include "objects.h"
#include "vec3.h"


void	tests()
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


	
	printf("ALL TESTS PASS!\n");
}