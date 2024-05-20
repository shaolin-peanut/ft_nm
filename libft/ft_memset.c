/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbars <marvin@42lausanne.ch>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 14:44:13 by sbars             #+#    #+#             */
/*   Updated: 2021/10/12 18:17:07 by sbars            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned long int	i;
	unsigned char		a;
	char				*string;

	a = c;
	i = 0;
	string = b;
	while (i++ < len)
		string[i - 1] = a;
	return (b);
}
