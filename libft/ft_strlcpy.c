/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbars <marvin@42lausanne.ch>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 14:33:39 by sbars             #+#    #+#             */
/*   Updated: 2021/10/12 16:14:09 by sbars            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	unsigned long int		srcsize;

	srcsize = ft_strlen((char *) src);
	if (dstsize < 1)
		return (srcsize);
	if (srcsize < dstsize)
	{
		ft_memcpy(dst, src, srcsize);
		dst[srcsize] = '\0';
		return (srcsize);
	}
	else
	{
		ft_memcpy(dst, src, dstsize - 1);
		dst[dstsize - 1] = '\0';
		return (srcsize);
	}
	return (0);
}
