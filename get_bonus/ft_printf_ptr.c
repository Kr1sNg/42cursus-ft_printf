/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_ptr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tat-nguy <tat-nguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 14:37:03 by tat-nguy          #+#    #+#             */
/*   Updated: 2024/11/20 10:11:46 by tat-nguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// [%20p]  =>  [0x16d5d730c   ]
// [%-20p] =>  [   0x16d5d730c]
// [%1p]   =>  [0x16d5d730c]

#include "ft_printf.h"

int	ft_print_ptr(unsigned long long p)
{
	int		count;

	count = 0;
	if (!p)
		count += ft_print_str("(nil)");
	else
	{
		count += ft_print_str("0x");
		count += ft_print_hex(p, 'x');
	}
	return (count);
}
