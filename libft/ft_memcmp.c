/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbars <marvin@42lausanne.ch>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 18:22:49 by sbars             #+#    #+#             */
/*   Updated: 2021/10/15 18:22:51 by sbars            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	int				i;
	unsigned char	*string1;
	unsigned char	*string2;

	i = 0;
	string1 = (unsigned char *) s1;
	string2 = (unsigned char *) s2;
	while (i++ < (int) n)
	{
		if (string1[i - 1] != string2[i - 1])
			return (((int) *(string1 + i - 1)) - ((int) *(string2 + i - 1)));
	}
	return (0);
}
