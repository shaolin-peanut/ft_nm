/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_int.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbars <marvin@42lausanne.ch>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 11:09:32 by sbars             #+#    #+#             */
/*   Updated: 2024/05/13 19:12:19 by sbars            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putuint(unsigned int n)
{
	unsigned int	num;
	int				count;

	count = 1;
	if (n > 9)
		ft_putuint(n / 10);
	num = n % 10;
	ft_printf("%d", num);
	return (count++);
}

int	int_len(int num)
{
	int	count;

	count = 1;
	if (num == -2147483648)
		return (11);
	if (num < 0)
	{
		num = num * -1;
		count += 1;
	}
	while (num > 9)
	{
		num /= 10;
		count++;
	}
	return (count);
}

int	uint_len(unsigned int num)
{
	int	count;

	count = 1;
	while (num > 9)
	{
		num /= 10;
		count++;
	}
	return (count);
}

int	print_int(t_info *tab, char flag)
{
	int				num;
	unsigned long	unum;

	num = va_arg(tab->args, int);
	unum = num;
	if (flag == 'u')
	{
		ft_putuint(unum);
		tab->tlen += uint_len(unum);
	}
	else
	{
		ft_putnbr_fd(num, 1);
		tab->tlen += int_len(num);
	}
	return (1);
}
