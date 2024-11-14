/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   real_printf.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tat-nguy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 17:01:07 by tat-nguy          #+#    #+#             */
/*   Updated: 2024/11/12 17:01:11 by tat-nguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>

int	print_digit(long n, int base)
{
	int		count;
	char	*symbols;

	symbols = "0123456789abcdef";
	if (n < 0)
	{
		write(1, "-", 1);
		return print_digit(-n, base) + 1;
	}
	else if (n < base)
		return (write(1, &symbols[n], 1));
	else
	{
		count = print_digit(n / base, base);
		return count + print_digit(n % base, base);
	}
}


int		ft_print_str(char *str)
{
	int		i;

	i = 0;
	while (str[i] != '\0')
	{
		write (1, &str[i++], 1);
	}
	return (i);
}

int main()
{
//    int result = printf("Sentence to know how many %s\n", "characters were written");
//    printf("% characters were written in total (both 2 arguments)%i\n", result);

    int count = print_digit(42, 2);
    printf ("\n%i\n", count);
   
}