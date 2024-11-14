/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tat-nguy <tat-nguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 09:39:49 by tat-nguy          #+#    #+#             */
/*   Updated: 2024/11/14 21:47:40 by tat-nguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int	main()
{
	
	int count = ft_printf(" %p %p ", 0, 0);
	ft_printf("number of char: %i\n", count);

}