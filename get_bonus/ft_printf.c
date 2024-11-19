/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tat-nguy <tat-nguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 14:33:47 by tat-nguy          #+#    #+#             */
/*   Updated: 2024/11/14 21:20:45 by tat-nguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf(const char *mand_arg, ...)
{
	int		i;
	int		count;
	t_flags	flags;
	va_list	ap;

	if (mand_arg == NULL || (mand_arg[0] == '%' && mand_arg[1] == '\0'))
		return (-42);
	va_start(ap, mand_arg);
	i = 0;
	count = 0;
	while (mand_arg[i] != '\0')
	{
		ft_bzero(&flags, sizeof(t_flags));
		if (mand_arg[i] == '%')
		{
			i++;
			while ((ft_memchr("-+ #0.", mand_arg[i], 6) != NULL) ||
						ft_isdigit(mand_arg[i]) != 0)
				ft_update_flags(&flags, mand_arg, &i);
			count += ft_print_format(&flags, mand_arg, &i, ap);
		}
		else
			count += write(1, &mand_arg[i], 1);
		i++;
	}
	va_end(ap);
	return (count);
}

int	ft_print_format(t_flags *flags, const char *mand_arg, int *i, va_list ap)
{
	int	count;

	count = 0;
	if (mand_arg[*i] == 'c')
		count += ft_print_char(flags, va_arg(ap, int)); //update
	else if (mand_arg[*i] == 's')
		count += ft_print_str(flags, va_arg(ap, char *)); //update
	else if (mand_arg[*i] == 'p')
		count += ft_print_ptr(flags, (unsigned long long)va_arg(ap, unsigned long)); //update
	else if (mand_arg[*i] == 'd' || c == 'i')
		count += ft_print_dec(flags, (long)va_arg(ap, int)); //update
	else if (mand_arg[*i] == 'u')
		count += ft_print_dec(flags, (long)va_arg(ap, unsigned int)); //update
	else if (mand_arg[*i] == 'x' || c == 'X')
		count += ft_print_hex(flags, (unsigned long long)va_arg(ap, unsigned int), mand_arg[*i]); //update
	else if (mand_arg[*i] == '%')
		count += ft_print_char('%');
	// DONT KNOW if it's needed to run (*i)++ here!?

	return (count);
}

void	ft_update_flags(t_flags *flags, const char *mand_arg, int *i)
{
	while (ft_memchr("-+ #", mand_arg[*i]) != NULL)
	{
		if (mand_arg[*i] == '-')
			flags->minus = 1;
		else if (mand_arg[*i] == '+')
			flags->plus = 1;
		else if (mand_arg[*i] == ' ')
			flags->space = 1;
		else if (mand_arg[*i] == '#')
			flags->hash = 1;
		(*i)++;	
	}
	if (mand_arg[*i] == '0')
		flags->zero = 1;
	if (ft_isdigit(mand_arg[*i]) != 0 || mand_arg[*i] == '.')
	{
		if (mand_arg[*i] == '.')
		{
			(*i)++;
			flags->precision = ft_atoi(&mand_arg[*i]) + 1;
		}
		else
			flags->width = ft_atoi(&mand_arg[*i]);
		while (ft_isdigit(mand_arg[*i]) != 1)
			(*i)++;
	}
}