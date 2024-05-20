/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbars <marvin@42lausanne.ch>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 12:03:21 by sbars             #+#    #+#             */
/*   Updated: 2021/10/19 12:03:22 by sbars            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*concatenated;
	int		i1;
	int		i2;
	int		i;

	if (s1 && s2)
	{
		i1 = ft_strlen((char *) s1);
		i2 = ft_strlen((char *) s2);
		i = -1;
		concatenated = malloc(sizeof(*concatenated) * (i2 + i1) + 1);
		if (concatenated)
		{
			while (++i < i1)
				concatenated[i] = s1[i];
			i = -1;
			while (++i < i2)
				concatenated[i + i1] = s2[i];
			concatenated[i + i1] = '\0';
			return (concatenated);
		}
	}
	else
		return (0);
	return (concatenated);
}
