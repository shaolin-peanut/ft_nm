/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbars <marvin@42lausanne.ch>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 12:33:54 by sbars             #+#    #+#             */
/*   Updated: 2021/11/08 13:52:38 by sbars            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	char			*string;

	i = -1;
	if (ft_strlen((char *) s) == 0)
		return (ft_calloc(1, 1));
	string = (char *) malloc(sizeof(char) * ft_strlen((char *) s) + 1);
	if (!string)
		return (NULL);
	while (s[++i])
		string[i] = f(i, *(s + i));
	string[i] = '\0';
	return (string);
}
