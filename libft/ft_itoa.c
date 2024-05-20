/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbars <marvin@42lausanne.ch>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 15:53:03 by sbars             #+#    #+#             */
/*   Updated: 2021/11/10 15:55:05 by sbars            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static int	intlen(int num)
{
	int	i;

	i = 0;
	if (num > 9)
	{
		while (num > 9)
		{
			num = num / 10;
			i++;
		}
		i++;
	}
	else
		i = 1;
	return (i);
}

static char	*errorcheck(char *s1, int num)
{
	if (num == 0)
	{
		ft_strlcpy(s1, "0", 2);
		return (s1);
	}
	if (num == -2147483648)
	{	
		ft_strlcpy(s1, "-2147483648", 12);
		return (s1);
	}
	return (s1);
}

static void	turn2min(int *stat, int *num)
{
	*num = *num * -1;
	*stat = 1;
}

char	*ft_itoa(int n)
{
	char	*number;
	int		destlen;
	int		state;

	state = 0;
	number = malloc (sizeof(char) * 12);
	if (number)
	{
		if (n == 0 || n == -2147483648)
			return (errorcheck(number, n));
		else if (n < 0)
			turn2min(&state, &n);
		destlen = (intlen(n) - 1) + state;
		number[destlen + 1] = '\0';
		while (n > 9)
		{
			number[destlen--] = (n % 10) + 48;
			n /= 10;
		}
		if (state == 1)
			number[0] = '-';
		number[state] = (n % 10) + 48;
	}
	return (number);
}
