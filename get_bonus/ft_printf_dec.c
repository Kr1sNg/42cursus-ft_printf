/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_dec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tat-nguy <tat-nguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 14:37:03 by tat-nguy          #+#    #+#             */
/*   Updated: 2024/11/21 00:08:48 by tat-nguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_print_dec(t_flags *flags, long n)
{
	char	c;
	char	sign;

	c = ' ';
	sign = '-';
	if (flags->space == 1)
		sign = ' ';
	if (flags->plus == 1)
		sign = '+';
	if (flags->zero == 1)
		c = '0';
	if (flags->minus == 1)
		return (ft_printd_minus(flags->width, (flags->precision - 1), n, sign));
	if (flags->width > 0 && flags->precision > 0)
		return (ft_printd_wp(flags->width, (flags->precision - 1), n, sign));
	if (flags->width > 0)
		return (ft_printd_width(flags->width, n, sign, c));
	if (flags->precision > 0)
		return (ft_printd_wp(flags->width, (flags->precision - 1), n, sign));
	if (n < 0)
		return (ft_printd(n));
	if (sign == '+' || sign == ' ')
		return (write(1, &sign, 1) + print_unsigned_dec(n));
	return (print_unsigned_dec(n));
}

int	ft_printd(long n)
{
	int		count;
	char	c;

	count = 0;
	if (n < 0)
	{
		count += write(1, "-", 1);
		n = -n;
	}
	if (n < 10)
	{
		c = n + '0';
		return (count += write(1, &c, 1));
	}
	count += ft_printd(n / 10);
	count += ft_printd(n % 10);
	return (count);
}

int	ft_printd_minus(int width, int pre, long n, char sign)
{
	int	count;

	count = 0;
	if (n == 0 && width > 0)
	{
		if (pre != 0)
			count += write(1, "0", 1);
		while (count < pre)
			count += write(1, "0", 1);
		while (count < width)
			count += write(1, " ", 1);
		return (count);
	}
	count += ft_printd_precision(pre, n, sign);
	while (count < width)
		count += write(1, " ", 1);
	return (count);
}

int	ft_printd_precision(int pre, long n, char sign)
{
	int	count;
	int	len;

	count = 0;
	len = ft_declen(ft_abs(n));
	if (n == 0 && pre == 0)
		return (0);
	if (n < 0)
		return (ft_printd_zero(n, pre + 1));
	if (sign == '+' || sign == ' ')
		count += write(1, &sign, 1);
	while (count < pre - len)
		count += write(1, "0", 1);
	return (count + print_unsigned_dec(n));
}

int	ft_printd_zero(long n, int pre)
{
	int	count;
	int	len;

	count = 0;
	len = ft_declen(ft_abs(n));
	if (n < 0)
	{
		count += write(1, "-", 1);
		n = -n;
	}
	while (count < pre - len)
		count += write(1, "0", 1);
	count += print_unsigned_dec(n);
	return (count);
}

int print_unsigned_dec(long number)
{
    int count;
	char	c;
	unsigned int u = (unsigned int)number;

    count = 0;
    if (u < 10)
    {
        count++;
		c = u + 48;
        write(1, &c, 1);
        return (count);
    }
    count += print_unsigned_dec(u / 10);
    count += print_unsigned_dec(u % 10);
    return (count);
}