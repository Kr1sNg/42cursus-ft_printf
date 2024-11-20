/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tat-nguy <tat-nguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 14:37:03 by tat-nguy          #+#    #+#             */
/*   Updated: 2024/11/14 22:04:53 by tat-nguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

// [%-10c] => [c         ]
//  [%10c] => [         c]
int	ft_print_char(t_flags *flags, int c)
{
	int	count;

	count = 0;
	if (flags->minus == 1)
	{
		count += write(1, &c, 1);
		(flags->width)--;
		while (flags->width > 0)
		{
			count += write(1, " ", 1);
			(flags->width)--;
		}
		return (count);
	}
	while (flags->width > 1)
	{
		count += write(1, " ", 1);
		(flags->width)--;
	}
	return (count + write(1, &c, 1));
}

int	ft_prints(char *str)
{
	int		i;

	if (str == NULL)
		return (ft_prints("(null)"));
	i = 0;
	while (str[i] != '\0')
		write (1, &str[i++], 1);
	return (i);
}

