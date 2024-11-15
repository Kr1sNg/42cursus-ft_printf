/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   real_printf.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tat-nguy <tat-nguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 17:01:07 by tat-nguy          #+#    #+#             */
/*   Updated: 2024/11/14 18:59:11 by tat-nguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>


int main()
{
	int result = printf("[%#x, %X\n]", __INT64_MAX__, __INT64_MAX__);
	printf("characters were written in total (both 2 arguments)%i\n", result);

   
}