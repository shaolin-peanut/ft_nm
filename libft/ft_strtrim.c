/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbars <marvin@42lausanne.ch>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 14:10:40 by sbars             #+#    #+#             */
/*   Updated: 2021/11/02 14:10:46 by sbars            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	int		j;
	char	*output;

	i = 0;
	j = ft_strlen((char *) s1) - 1;
	while (i < j && ft_strchr(set, s1[i]))
		i++;
	while (j > -1 && ft_strchr(set, s1[j]))
		j--;
	if (i >= j)
		return (ft_calloc(1, 1));
	output = (char *) malloc(sizeof(char) * ((j - i) + 10));
	if (!output)
		return (NULL);
	ft_strlcpy(output, (s1 + i), j - i + 2);
	return (output);
}
