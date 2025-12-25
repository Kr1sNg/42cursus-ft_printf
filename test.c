#include <stdio.h>
#include "./ft_printf_bonus/ft_printf.h"

int main (void)
{
	int a = ft_printf("ft_printf: %.7s\n", NULL);
	int b = printf("   printf: %.7s\n", NULL);
	ft_printf("characters were written in total is %i\n", a);
	printf("characters were written in total is %i\n", b);
}