/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbars <marvin@42lausanne.ch>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 13:51:24 by sbars             #+#    #+#             */
/*   Updated: 2021/12/09 13:08:48 by sbars            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	ft_putchar(char c, int f)
{
	write(f, &c, 1);
}

void	ft_putnbr_fd(int n, int fd)
{
	char	num;

	if (n == -2147483648)
	{
		write(fd, "-2147483648", 11);
	}
	else if (n < 0)
	{
		ft_putchar('-', fd);
		ft_putnbr_fd(-n, fd);
	}
	else
	{
		if (n > 9)
			ft_putnbr_fd(n / 10, fd);
		num = n % 10;
		ft_putchar(num + 48, fd);
	}
}
