/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbars <marvin@42lausanne.ch>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 11:51:49 by sbars             #+#    #+#             */
/*   Updated: 2021/10/19 11:51:51 by sbars            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* REMOVED LINE BELOW TO KEEP FUNCTION AT 25 LINES, HANDLES -1 AS INPUT, 
PLACED AT BEGINNING
	if ((int) len == -1)
		len = ft_strlen((char *)haystack); */

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	int		i;
	int		j;
	int		counter;

	i = -1;
	j = -1;
	(void) len;
	counter = 0;
	if (haystack == needle || (ft_strlen((char *)needle) == 0))
		return ((char *) haystack);
	while (haystack[++i] || i < (int) len)
	{
		while (needle[++j] && (i + j) < (int) len)
		{
			if (haystack[i + j] == needle[j])
				++counter;
			if (i + j >= ft_strlen((char *)haystack))
				return (NULL);
			if (counter == ft_strlen((char *)needle))
				return ((char *)(haystack + i));
		}
		j = -1;
		counter = 0;
	}
	return (NULL);
}
