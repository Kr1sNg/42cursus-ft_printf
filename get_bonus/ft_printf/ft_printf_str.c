/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_str.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tat-nguy <tat-nguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 14:37:03 by tat-nguy          #+#    #+#             */
/*   Updated: 2024/11/21 00:15:33 by tat-nguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// [%.3s]       => [Wor]
// [%10.3s]     => [       Wor]
// [%-10.3s]    => [Wor       ]
// [%3s]/[%-3s] => [World]
// [%10s]       => [World     ]
// [%-10s]      => [     World]

#include "ft_printf.h"

int	ft_print_str(t_flags *flags, char *str)
{
	if (flags->width > 0 && flags->precision > 0)
		return (ft_prints_duo(flags->width, (flags->precision -1), str,
				flags->minus));
	if (flags->width > 0)
		return (ft_prints_width(flags->width, str, flags->minus));
	if (flags->precision > 0)
		return (ft_prints_precision((flags->precision - 1), str));
	return (ft_prints(str));
}

int	ft_prints_precision(int precision, char *str)
{
	int	i;

	i = 0;
	if (str == NULL)
	{
		if (precision < 6)
			precision = 0;
		ft_prints_precision(precision, "(null)");
	}
	while (str[i] != '\0' && i < precision)
		i += write (1, &str[i], 1);
	return (i);
}

int	ft_prints_width(int width, char *str, int minus)
{
	int	i;
	int	strlen;

	if (str == NULL)
		str = "(null)";
	strlen = ft_strlen(str);
	i = 0;
	if (strlen >= width)
		return (ft_prints(str));
	if (minus == 1)
	{
		i += ft_prints(str);
		while (i < width)
			i += write(1, " ", 1);
		return (i);
	}
	while (i < width - strlen)
		i += write(1, " ", 1);
	return (i + ft_prints(str));
}

int	ft_prints_duo(int width, int precision, char *str, int minus)
{
	int	strlen;
	int	count;

	if (str == NULL)
	{
		str = "(null)";
		if (precision < 6)
			precision = 0;
	}
	strlen = ft_strlen(str);
	if (precision < strlen)
		strlen = precision;
	if (strlen >= width)
		return (ft_prints_precision(precision, str));
	count = 0;
	if (minus == 1)
	{
		count += ft_prints_precision(precision, str);
		while (count < width)
			count += write(1, " ", 1);
		return (count);
	}
	while (count < width - strlen)
		count += write(1, " ", 1);
	return (count + ft_prints_precision(precision, str));
}
