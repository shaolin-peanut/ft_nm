/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_string.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbars <marvin@42lausanne.ch>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 11:10:21 by sbars             #+#    #+#             */
/*   Updated: 2024/05/13 19:12:41 by sbars            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_putstr(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		write(1, &str[i], 1);
}

int	print_string(t_info *tab)
{
	char	*str;

	str = va_arg(tab->args, char *);
	if (!str)
	{
		tab->tlen += write(1, "(null)", 6);
		return (1);
	}
	if (ft_strlen(str) != 0)
	{
		tab->tlen += ft_strlen(str);
		ft_putstr(str);
		return (1);
	}
	return (1);
}
