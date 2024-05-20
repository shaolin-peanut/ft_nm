/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_hex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbars <marvin@42lausanne.ch>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 11:15:11 by sbars             #+#    #+#             */
/*   Updated: 2024/05/13 19:12:13 by sbars            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	rev_print(char *string)
{
	int	i;
	int	count;

	count = 0;
	i = ft_strlen(string);
	while (--i >= 0)
		count += write(1, &string[i], 1);
	return (count);
}

int	print_hex(t_info *tab)
{
	unsigned int	remainder;
	unsigned int	num;
	int				i;
	char			output[100];

	i = 0;
	remainder = 0;
	num = va_arg(tab->args, int);
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
			output[i++] = 55 + remainder;
		num = num / 16;
	}
	output[i++] = '\0';
	tab->tlen += rev_print(output);
	return (1);
}

int	print_lower_hex(t_info *tab)
{
	unsigned int	remainder;
	unsigned int	num;
	int				i;
	char			output[100];

	i = 0;
	remainder = 0;
	num = va_arg(tab->args, int);
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
		num = num / 16;
	}
	output[i] = '\0';
	tab->tlen += rev_print(output);
	return (1);
}
