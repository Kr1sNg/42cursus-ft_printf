/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_dwp.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tat-nguy <tat-nguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 14:37:03 by tat-nguy          #+#    #+#             */
/*   Updated: 2024/11/22 16:09:28 by tat-nguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printd_width(int width, long n, char sign, char c)
{
	int	len;
	int	count;

	len = ft_declen(ft_abs(n));
	count = 0;
	if (n < 0)
	{
		if (c == '0')
			return (ft_printd_zero(n, width));
		while (count < width - len - 1)
			count += write(1, " ", 1);
		return (count + ft_printd(n));
	}
	if (sign == '+')
		return (ft_printd_wplus(width, n, sign, c));
	while (count < width - len)
		count += write(1, &c, 1);
	return (count + print_unsigned_dec(n));
}

int	ft_printd_wplus(int width, long n, char sign, char c)
{
	int	len;
	int	count;

	len = ft_declen(ft_abs(n));
	count = 0;
	if (c == '0')
	{
		write(1, &sign, 1);
		while (count < width - len)
			count += write(1, "0", 1);
		return (count + ft_printd(n) + 1);
	}
	while (count < width - len)
		count += write(1, " ", 1);
	write(1, &sign, 1);
	return (count + ft_printd(n) + 1);
}

int	ft_printd_wp(int width, int pre, long n, char sign)
{
	int	len;
	int	count;

	count = 0;
	len = ft_declen(ft_abs(n));
	if (n < 0)
	{
		if (pre > len)
			len = pre;
		while (count < width - len - 1)
			count += write(1, " ", 1);
		return (count + ft_printd_precision(pre, n, sign));
	}
	if (sign == '+' || sign == ' ')
		return (ft_printd_wpsign(width, pre, n, sign));
	if (n == 0)
		len = 0;
	if (pre > len)
		len = pre;
	while (count < width - len)
		count += write (1, " ", 1);
	return (count + ft_printd_precision(pre, n, sign));
}

int	ft_printd_wpsign(int width, int pre, long n, char sign)
{
	int	len;
	int	count;

	count = 0;
	len = ft_declen(ft_abs(n));
	if (pre > len)
		len = pre;
	while (count < width - len - 1)
		count += write (1, " ", 1);
	return (count + ft_printd_precision(pre, n, sign));
}
