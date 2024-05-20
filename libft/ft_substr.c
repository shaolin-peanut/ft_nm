/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbars <marvin@42lausanne.ch>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 12:12:55 by sbars             #+#    #+#             */
/*   Updated: 2021/11/08 13:53:09 by sbars            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	unsigned int		real_len;
	int					i;
	char				*substring;

	real_len = ft_strlen(((char *) s));
	i = -1;
	if (ft_strlen((char *) s) == 0)
	{
		return (ft_calloc(1, 1));
	}
	else
	{
		if (start >= real_len)
			return (ft_calloc(1, 1));
		substring = malloc(sizeof(char) * len + 1);
		if (substring)
			while (++i < (int) len && i <= (int) real_len)
				substring[i] = s[start + i];
		else
			return (NULL);
	}
	substring[i] = '\0';
	return (substring);
}
