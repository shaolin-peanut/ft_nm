/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbars <marvin@42lausanne.ch>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 10:22:51 by sbars             #+#    #+#             */
/*   Updated: 2021/10/14 10:22:53 by sbars            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int		i;
	char	*str;
	char	chr;

	i = 0;
	str = (char *) s;
	chr = (char) c;
	if (chr == '\0')
	{
		while (str[i++])
			;
		return (&str[i - 1]);
	}
	while (str[i])
	{
		if (*(str + i) == chr)
			return (&str[i]);
		i++;
	}
	return (NULL);
}
