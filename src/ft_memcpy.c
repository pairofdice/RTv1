/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaarine <jsaarine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 12:29:53 by jsaarine          #+#    #+#             */
/*   Updated: 2022/08/05 14:42:54 by jsaarine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char	*d;

	d = dst;
	if (!dst && !src)
		return (NULL);
	while (n--)
		*d++ = *(unsigned char *)src++;
	return (dst);
}
