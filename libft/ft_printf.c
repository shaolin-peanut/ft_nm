/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbars <marvin@42lausanne.ch>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 16:50:28 by sbars             #+#    #+#             */
/*   Updated: 2024/05/13 19:11:23 by sbars            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static t_info	*initialize(t_info *tab)
{
	tab->tlen = 0;
	return (tab);
}

int	ft_printf(const char *string, ...)
{
	t_info	*info;
	char	*str;
	int		i;
	int		ret;

	i = -1;
	ret = 0;
	str = (char *) string;
	info = (t_info *) malloc(sizeof(t_info));
	if (!info)
		return (i);
	info = initialize(info);
	va_start(info->args, string);
	while (++i < ft_strlen(str))
	{
		if (str[i] != '%' && str[i])
			info->tlen += write(1, &str[i], 1);
		else
			i += check_flag(info, str, i + 1);
	}
	va_end(info->args);
	ret = info->tlen;
	free(info);
	return ret;
}
