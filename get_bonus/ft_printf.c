/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tat-nguy <tat-nguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 14:33:47 by tat-nguy          #+#    #+#             */
/*   Updated: 2024/11/21 00:23:02 by tat-nguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf(const char *manda, ...)
{
	int		i;
	int		count;
	t_flags	flags;
	va_list	ap;

	if (manda == NULL || (manda[0] == '%' && manda[1] == '\0'))
		return (-42);
	va_start(ap, manda);
	i = 0;
	count = 0;
	while (manda[i] != '\0')
	{
		ft_bzero(&flags, sizeof(t_flags));
		if (manda[i] == '%')
		{
			i++;
			while (ft_memchr("-+ #0.", manda[i], 6) || ft_isdigit(manda[i]))
				ft_update_flags(&flags, manda, &i);
			count += ft_print_format(&flags, manda, &i, ap);
		}
		else
			count += write(1, &manda[i++], 1);
	}
	va_end(ap);
	return (count);
}

int	ft_print_format(t_flags *flags, const char *manda, int *i, va_list ap)
{
	int	count;

	count = 0;
	if (manda[*i] == 'c')
		count += ft_print_char(flags, va_arg(ap, int));
	else if (manda[*i] == 's')
		count += ft_print_str(flags, va_arg(ap, char *));
	else if (manda[*i] == 'p')
		count += ft_print_ptr(flags,
				(unsigned long long)va_arg(ap, unsigned long));
	else if (manda[*i] == 'd' || manda[*i] == 'i')
		count += ft_print_dec(flags, (long)va_arg(ap, int));
	else if (manda[*i] == 'u')
		count += ft_print_dec(flags, (long)va_arg(ap, unsigned int));
	else if (manda[*i] == 'x' || manda[*i] == 'X')
		count += ft_print_hex(flags,
				(unsigned long long)va_arg(ap, unsigned int), manda[*i]);
	else if (manda[*i] == '%')
		count += write(1, "%", 1);
	(*i)++;
	return (count);
}

void	ft_update_flags(t_flags *flags, const char *manda, int *i)
{
	while (ft_memchr("-+ #", manda[*i], 4) != NULL)
	{
		if (manda[*i] == '-')
			flags->minus = 1;
		if (manda[*i] == '+')
			flags->plus = 1;
		if (manda[*i] == ' ')
			flags->space = 1;
		if (manda[*i] == '#')
			flags->hash = 1;
		(*i)++;
	}
	if (manda[*i] == '0')
		flags->zero = 1;
	if (ft_isdigit(manda[*i]) != 0 || manda[*i] == '.')
	{
		if (manda[*i] == '.')
			flags->precision = ft_atoi(&manda[++(*i)]) + 1;
		else
			flags->width = ft_atoi(&manda[*i]);
		while (ft_isdigit(manda[*i]) != 0)
			(*i)++;
	}
}


#include <stdio.h>
#include <limits.h>

int main (void)
{
	int a = ft_printf("ft_printf: [%-163.23u%-68.0X]\n", 3421138903u, 514939578u);
	int b = printf("   printf: [%-163.23u%-68.0X]\n", 3421138903u, 514939578u);
	ft_printf("characters were written in total is %i\n", a);
	printf("characters were written in total is %i\n", b);
}
