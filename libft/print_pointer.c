/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_pointer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbars <marvin@42lausanne.ch>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 11:16:09 by sbars             #+#    #+#             */
/*   Updated: 2024/05/13 19:12:32 by sbars            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	print_pointer_hex(t_info *tab)
{
	unsigned long	num;
	unsigned long	remainder;
	int				i;
	char			output[100];

	i = 0;
	remainder = 0;
	num = va_arg(tab->args, long);
	if (num == 0)
	{
		tab->tlen++;
		return (write(1, "0", 1));
	}
	while (num != 0)
	{
		remainder = num % 16;
		if (remainder < 10)
			output[i++] = 48 + remainder;
		else
			output[i++] = 87 + remainder;
		num /= 16;
	}
	output[i] = '\0';
	tab->tlen += rev_print(output);
	return (1);
}

int	print_pointer(t_info *tab)
{
	tab->tlen += write(1, "0x", 2);
	print_pointer_hex(tab);
	return (1);
}
