/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_hex.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tat-nguy <tat-nguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 14:37:03 by tat-nguy          #+#    #+#             */
/*   Updated: 2024/11/21 00:10:58 by tat-nguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// [%#010x]
// [%#-10x] => [0x2a         ]
// [%#10x]  => [         0x2a]
// [%#.10c] => [0x0000000002a]

#include "ft_printf.h"

int	ft_print_hex(t_flags *flags, unsigned long long n, char x)
{
	char	c;

	c = ' ';
	if (flags->zero == 1 && flags->precision <= 0 && flags->minus == 0)
		c = '0';
	if (flags->minus == 1)
		return (ft_printh_minus(flags, n, x));
	if (flags->hash == 1)
		return (ft_printh_hash(flags, n, x, c));
	if (flags->width > 0)
		return (ft_printh_width(flags, n, x, c));
	if (flags->precision > 0)
		return (ft_printh_precision((flags->precision - 1), n, x));
	if (n == 0)
		return (write(1, "0", 1));
	return (ft_printh(n, x));
}

int	ft_printh_precision(int pre, unsigned long long n, char x)
{
	int	count;
	int	len;

	if (n == 0 && pre == 0)
		return (0);
	len = ft_hexlen(n);
	count = 0;
	while (len < pre)
	{
		count += write(1, "0", 1);
		pre--;
	}
	count += ft_printh(n, x);
	return (count);
}

int	ft_printh_minus(t_flags *flags, unsigned long long n, char x)
{
	int		count;

	count = 0;
	if (flags->hash == 1)
	{
		if (n != 0)
		{
			count += write(1, "0", 1);
			count += write(1, &x, 1);
		}
	}
	count += ft_printh_precision((flags->precision - 1), n, x);
	while (count < flags->width)
		count += write(1, " ", 1);
	return (count);
}

int	ft_printh_hash(t_flags *flags, unsigned long long n, char x, char c)
{
	int		count;
	int		len;

	count = 0;
	len = ft_hexlen(n);
	if ((flags->precision - 1) > len)
		len = flags->precision - 1;
	if (n == 0 && flags->precision == 1)
		len = 0;
	while (count < flags->width - 2 - len)
		count += write(1, &c, 1);
	if (n != 0)
	{
		count += write(1, "0", 1);
		count += write(1, &x, 1);
	}
	count += ft_printh_precision((flags->precision - 1), n, x);
	return (count);
}

int	ft_printh_width(t_flags *flags, unsigned long long n, char x, char c)
{
	int	count;
	int	len;
	int	padding;

	len = ft_hexlen(n);
	if (n == 0 && (flags->precision - 1) == 0)
		len = 0;
	else if ((flags->precision - 1) > len)
		len = flags->precision - 1;
	padding = flags->width - len;
	count = 0;
	if (flags->minus == 0)
		while (padding-- > 0)
			count += write(1, &c, 1);
	count += ft_printh_precision((flags->precision - 1), n, x);
	if (flags->minus == 1)
		while (padding-- > 0)
			count += write(1, " ", 1);
	return (count);
}
