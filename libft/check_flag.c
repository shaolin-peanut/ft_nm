/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_flag.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbars <marvin@42lausanne.ch>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 11:09:00 by sbars             #+#    #+#             */
/*   Updated: 2024/05/13 19:11:37 by sbars            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	check_flag(t_info *tab, char *string, int i)
{
	if (string[i] == 'd' || string[i] == 'i' || string[i] == 'u')
		return (print_int(tab, string[i]));
	else if (string[i] == 'c')
		return (print_char(tab));
	else if (string[i] == 's')
		return (print_string(tab));
	else if (string[i] == 'p')
		return (print_pointer(tab));
	else if (string[i] == 'x')
		return (print_lower_hex(tab));
	else if (string[i] == 'X')
		return (print_hex(tab));
	else if (string[i] == '%')
	{
		tab->tlen += 1;
		return (write(1, "%", 1));
	}
	return (i);
}
