/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbars <marvin@42lausanne.ch>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 16:40:31 by sbars             #+#    #+#             */
/*   Updated: 2021/10/13 16:40:36 by sbars            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

/*void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t				i;
	unsigned char		*str;

	i = 0;
	str = (unsigned char *)s;
	while (i < n)
	{
		if (ft_isalnum(str[i]))
			return (&str[i]);
		else if (str[i] == (unsigned char) c)
			return (&str[i]);
		i++;
	}
	return (NULL);
}*/

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*str;

	str = (unsigned char *) s;
	while (n > 0)
	{
		if (*str == (unsigned char) c)
			return (str);
		str++;
		n--;
	}
	return (NULL);
}
