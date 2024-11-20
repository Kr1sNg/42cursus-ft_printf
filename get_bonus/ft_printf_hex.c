/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_hex.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tat-nguy <tat-nguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 14:37:03 by tat-nguy          #+#    #+#             */
/*   Updated: 2024/11/20 11:46:55 by tat-nguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// [%#010x]
// [%#-10x] => [0x2a         ]
// [%#10x]  => [         0x2a]
// [%#.10c] => [0x0000000002a]

#include "ft_printf.h"

int	ft_print_hex(t_flags *flags, unsigned long long n, char x)
{
	int		len;
	char	c;

	c = ' ';
	if (flags->zero == 1)
		c = '0';
	if (flags->width > 0 && flags->precision > 0)
		c = ' ';
	if (flags->minus == 1)
		return (ft_printh_minus(flags, n, x)); //TODO
	if (flags->hash == 1)
		return (ft_printh_hash(flags, n, x, c)); //TODO
	if (flags->width > 0)
		return (ft_printh_width(flags, n. x, c)); //TODO
	if (flags->precision > 0)
		return (ft_printh_precision((flags->precision - 1), n, x)); //TODO
	len = ft_hexlen(n);
	ft_printh(n, x); //TODO
	return (len);
}

int	ft_printh(unsigned long long n, char x)
{
	int		count;
	char 	*str;

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
