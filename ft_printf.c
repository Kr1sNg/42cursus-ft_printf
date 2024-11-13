/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tat-nguy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 14:33:47 by tat-nguy          #+#    #+#             */
/*   Updated: 2024/11/13 14:33:54 by tat-nguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

int	ft_printf(const char *mand_arg, ...)
{
	int	i;
	int count;
	int	a;

	i = 0;
	count = 0;
	while (mand_arg[i] != '\0')
	{
		while (mand_arg != '%')
		{
			write(1, &mand_arg[i], 1);
			i++;
			count++;
		}
		if (mand_arg[i] == '%')
		{
			i++;
			a = ft_format_check(mand_arg[i]);
			if (a != 0)
			{
				ft_put_arg(a, var_arg); 
			}
			else
				return (0);
		}
	}
}
