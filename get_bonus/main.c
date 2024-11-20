/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tat-nguy <tat-nguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 17:01:07 by tat-nguy          #+#    #+#             */
/*   Updated: 2024/11/20 10:56:14 by tat-nguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <limits.h>
#include "ft_printf.h"


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

int main()
{
	int a = ft_printh(100000, 'x');
	//int result = ft_printf("[%c]\n", 'c');
	printf("characters were written in total is %i\n", a);
}