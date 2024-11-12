/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variadic_func.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tat-nguy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 14:51:34 by tat-nguy          #+#    #+#             */
/*   Updated: 2024/11/12 14:58:10 by tat-nguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// example of using va_start, va_arg, va_end
// create a function which returns the avrage of 'num_args' integers in arguments

#include <stdarg.h>

int ft_avr(int num_args, ...)
{
	int		sum;
	int		i;
	va_list	ap;

	va_start(ap, num_args);
	i = 0;
	sum = 0;
	while (i < num_args)
	{
		sum = sum + va_arg(ap, int);
		i++;
	}
	va_end(ap);
	return (sum / num_args);
}
