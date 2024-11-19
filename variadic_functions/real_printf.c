/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   real_printf.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tat-nguy <tat-nguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 17:01:07 by tat-nguy          #+#    #+#             */
/*   Updated: 2024/11/16 11:46:08 by tat-nguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>


int main()
{
	int result = printf("[%], [%*i]\n", "-2147483647", 10);
	printf("characters were written in total (both 2 arguments)%i\n", result);

   
}