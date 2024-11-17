/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tat-nguy <tat-nguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 12:32:48 by tat-nguy          #+#    #+#             */
/*   Updated: 2024/11/16 17:43:55 by tat-nguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

bool	in(const char *s, char c)
{
	if (s == NULL)
		return (false);
	while (*s)
	{
		if (*s == c)
			return (true);
		s++;
	}
	return (false);
}

void	my_memset(void *ptr, unsigned char value, size_t n)
{
	unsigned char	*ptr_byte;
	
	ptr_byte = (unsigned char *)ptr;
	while (n > 0)
	{
		*ptr_byte++ = value;
		--n;
	}
}