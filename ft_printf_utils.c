/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tat-nguy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 14:37:03 by tat-nguy          #+#    #+#             */
/*   Updated: 2024/11/13 14:37:04 by tat-nguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_print_format(char c, va_list ap)
{
	int	count;

	count = 0;
	if (c == 'c')
		count += ft_print_char(va_arg(ap, int));
	else if (c == 's')
		count += ft_print_str(va_arg(ap, char *));
	else if (c == 'p')
		count += ft_print_digit((long)va_arg(ap, int), 16);
	else if (c == 'd' || c == 'i')
		count += ft_print_nbr((long)va_arg(ap, int));
	else if (c == 'u')
		count += ft_print_digit((long)va_arg(ap, unsigned int), 10);
	else if (c == 'x')
		count += ft_print_digit((long)va_arg(ap, unsigned int), 16);
	else if (c == 'X')
		count += ft_print_digit((long)va_arg(ap, unsigned int), 16);
	else if (c == '%')
	{
		count += write(1, '%', 1);
	}
	else
		count += write(1, &c, 1);
	return (count);
}

int		ft_print_char(int c)
{
	return (write(1, &c, 1));
}

int		ft_print_str(char *str)
{
	int		i;

	i = 0;
	while (str[i] != '\0')
	{
		write (1, &str[i++], 1);
	}
	return (i);
}

int		ft_print_nbr(int nbr)
{
	long	n;
	char	c;
	int		count;

	if (n < 0)
	{
		count += write(1, "-", 1);
		n = -n;
	}
	if (n >= 10)
	{
		count += ft_print_nbr(n / 10);
		count += ft_print_nbr(n % 10);
	}
	else
	{
		n = c + '0';
		count += write(1, &c, 1);
	}
	return (count);
}