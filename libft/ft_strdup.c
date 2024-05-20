/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbars <marvin@42lausanne.ch>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 13:22:42 by sbars             #+#    #+#             */
/*   Updated: 2021/10/19 13:22:47 by sbars            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strdup(const char *s1)
{
	char	*copy;
	int		i;

	i = -1;
	copy = malloc (sizeof(char) * ft_strlen((char *)s1) + 1);
	if (copy)
	{
		while (s1[++i])
			copy[i] = s1[i];
		copy[i] = '\0';
	}
	return (copy);
}
