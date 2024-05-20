/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbars <marvin@42lausanne.ch>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 14:58:07 by sbars             #+#    #+#             */
/*   Updated: 2021/10/12 16:11:00 by sbars            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

/*static int	ft_min(int given_size, int real_size)
{
	if (given_size < real_size)
		return (given_size);
	else
		return (real_size);
}*/

int	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	dstlen;
	size_t	j;

	dstlen = ft_strlen(dst);
	j = 0;
	if (dstsize < dstlen)
	{
		while (src[j])
			j++;
		return (dstsize + j);
	}
	while (dstsize > 0 && dstlen < dstsize - 1 && src[j])
		dst[dstlen++] = src[j++];
	dst[dstlen] = '\0';
	while (src[j++])
		dstlen++;
	return (dstlen);
}
