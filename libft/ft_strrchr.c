/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbars <marvin@42lausanne.ch>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 16:38:30 by sbars             #+#    #+#             */
/*   Updated: 2021/10/13 16:38:33 by sbars            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	chr;
	int		i;
	char	*string;

	chr = (char) c;
	string = (char *) s;
	i = ft_strlen(string);
	if (c == 0)
		return ((char *)(s + i));
	while (--i > -1)
		if (string[i] == chr)
			return (&string[i]);
	return (NULL);
}
