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
	if (flags->width != 0 && flags->precision != 0)
		c = ' ';
	if (flags->minus == 1)

		
	if (n >= 16)
	{
		count += ft_print_hex(n / 16, c);
		count += ft_print_hex(n % 16, c);
	}
	else
	{
		if (c == 'x')
			count += ft_print_char("0123456789abcdef"[n]);
		if (c == 'X')
			count += ft_print_char("0123456789ABCDEF"[n]);
	}
	return (count);
}

