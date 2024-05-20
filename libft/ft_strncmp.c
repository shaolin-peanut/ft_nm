/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbars <marvin@42lausanne.ch>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 11:24:59 by sbars             #+#    #+#             */
/*   Updated: 2021/10/18 11:25:01 by sbars            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned char	*string1;
	unsigned char	*string2;
	int				i;

	i = -1;
	string1 = (unsigned char *) s1;
	string2 = (unsigned char *) s2;
	while (++i < (int) n && (string1[i] || string2[i]))
	{
		if (string1[i] > string2[i])
			return (1);
		else if (string1[i] < string2[i])
			return (-1);
	}
	return (0);
}
