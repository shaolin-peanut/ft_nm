/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbars <marvin@42lausanne.ch>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 14:40:04 by sbars             #+#    #+#             */
/*   Updated: 2021/10/15 14:40:07 by sbars            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char	*dest;
	char	*source;
	int		i;

	dest = (char *) dst;
	source = (char *) src;
	i = 0;
	if (!dst && !src)
		return (dest);
	if (dst > src)
	{
		while (len--)
		{
			dest[len] = source[len];
		}
	}
	else
	{
		while (i < (int) len)
		{
			dest[i] = source[i];
			i++;
		}
	}
	return (dest);
}
