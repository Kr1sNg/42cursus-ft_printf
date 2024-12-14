/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tat-nguy <tat-nguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 14:37:03 by tat-nguy          #+#    #+#             */
/*   Updated: 2024/11/21 00:18:20 by tat-nguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_hexlen(unsigned long long n)
{
	int	i;

	i = 1;
	while (n >= 16)
	{
		n = n / 16;
		i++;
	}
	return (i);
}

int	ft_declen(unsigned long long n)
{
	int	i;

	i = 1;
	while (n >= 10)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

int	ft_abs(long n)
{
	if (n >= 0)
		return (n);
	else
		return (-n);
}

int	print_unsigned_dec(unsigned int u)
{
	int		count;
	char	c;

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
