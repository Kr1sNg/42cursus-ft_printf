/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_ptr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tat-nguy <tat-nguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 14:37:03 by tat-nguy          #+#    #+#             */
/*   Updated: 2024/11/21 00:12:54 by tat-nguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// [%20p]  =>  [0x16d5d730c   ]
// [%-20p] =>  [   0x16d5d730c]
// [%1p]   =>  [0x16d5d730c]

#include "ft_printf.h"

int	ft_print_ptr(t_flags *flags, unsigned long long p)
{
	int		count;

	count = 0;
	if (p == 0)
	{
		count = 5;
		if (flags->width <= 5)
			return (write(1, "(nil)", 5));
		if (flags->minus == 1)
		{
			write(1, "(nil)", 5);
			while (flags->width > count)
				count += write(1, " ", 1);
			return (count);
		}
		while (flags->width > count)
			count += write(1, " ", 1);
		write(1, "(nil)", 5);
		return (count);
	}
	if (flags->width > 0)
		return (ft_printp(flags->width, flags->minus, p));
	count += write(1, "0x", 2);
	count += ft_printh(p, 'x');
	return (count);
}

int	ft_printp(int width, int minus, unsigned long long p)
{
	int	count;

	count = ft_hexlen(p) + 2;
	if (width <= count)
	{
		write(1, "0x", 2);
		ft_printh(p, 'x');
		return (count);
	}
	if (minus == 1)
	{
		write(1, "0x", 2);
		ft_printh(p, 'x');
		while (width > count)
			count += write(1, " ", 1);
		return (count);
	}
	while (width > count)
		count += write(1, " ", 1);
	write(1, "0x", 2);
	ft_printh(p, 'x');
	return (count);
}

int	ft_printh(unsigned long long n, char x)
{
	int		count;
	char	*str;

	count = 0;
	if (n < 16)
	{
		if (x == 'x')
		{
			str = "0123456789abcdef";
			return (count += write(1, &str[n], 1));
		}
		else if (x == 'X')
		{
			str = "0123456789ABCDEF";
			return (count += write(1, &str[n], 1));
		}
	}
	count += ft_printh(n / 16, x);
	count += ft_printh(n % 16, x);
	return (count);
}
