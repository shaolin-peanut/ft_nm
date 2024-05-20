/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbars <marvin@42lausanne.ch>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 16:39:57 by sbars             #+#    #+#             */
/*   Updated: 2021/10/13 16:39:59 by sbars            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char	*dest;
	char	*source;

	if (!dst && !src)
		return (NULL);
	if (n-- > 0)
	{
		dest = (char *) dst;
		source = (char *) src;
		while (n)
		{
			dest[n] = source[n];
			n--;
		}
		dest[n] = source[n];
	}
	return (dst);
}
