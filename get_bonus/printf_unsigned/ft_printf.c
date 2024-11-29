
#include <unistd.h>
#include <stdarg.h>
#include <limits.h>
#include <strings.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>


typedef struct s_flags
{
	//[-+' '#0.]
	int	minus; //for align_left
	int	plus; // +0 -42
	int	space; // ' '42
	int	hash; // '0x' or '0X'
	int	zero; // 000042
	int	width; // 
	int	point; // [forty_tw" "]
	int	precision;
}	t_flags;

int		ft_printf(const char *manda, ...);
int		ft_print_format(t_flags *flags, const char *manda, int *i, va_list ap);
void	ft_update_flags(t_flags *flags, const char *manda, int *i);

//	ft_printf_utils.c

int		ft_declen(unsigned long long n);
int		ft_abs(long n);

//	ft_printf_dec.c

int		ft_print_dec(t_flags *flags, unsigned int n);
int		ft_printd(long n);
int		ft_printd_minus(int width, int pre, long n, char sign);
int		ft_printd_precision(int pre, long n, char sign);
int		ft_printd_zero(long n, int pre);

//	ft_printf_dwp.c

int		ft_printd_width(int width, unsigned int n, char sign, char c);
int		ft_printd_wplus(int width, long n, char sign, char c);
int		ft_printd_wp(int width, int pre, long n, char sign);
int		ft_printd_wpsign(int width, int pre, long n, char sign);


int print_unsigned_dec(unsigned int u);


int	ft_declen(unsigned long long n)
{
	int	i;

	i = 1;
	while (n >= 10)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

int	ft_abs(long n)
{
	if (n >= 0)
		return (n);
	else
		return (-n);
}

int	ft_print_dec(t_flags *flags, unsigned int n)
{
	char	c;
	char	sign;

	c = ' ';
	sign = '-';
	if (flags->zero == 1)
		c = '0';
	if (flags->width > 0 && flags->precision > 0)
		return (ft_printd_wp(flags->width, (flags->precision - 1), n, sign));
	if (flags->width > 0)
		return (ft_printd_width(flags->width, n, sign, c));
	if (flags->precision > 0)
		return (ft_printd_wp(flags->width, (flags->precision - 1), n, sign));
//	if (n < 0)
//		return (ft_printd(n));
	return (print_unsigned_dec(n));
}

int	ft_printf(const char *manda, ...)
{
	int		i;
	int		count;
	t_flags	flags;
	va_list	ap;

	if (manda == NULL || (manda[0] == '%' && manda[1] == '\0'))
		return (-42);
	va_start(ap, manda);
	i = 0;
	count = 0;
	while (manda[i] != '\0')
	{
		bzero(&flags, sizeof(t_flags));
		if (manda[i] == '%')
		{
			i++;
			while (memchr("-+ #0.", manda[i], 6) || isdigit(manda[i]))
				ft_update_flags(&flags, manda, &i);
			count += ft_print_format(&flags, manda, &i, ap);
		}
		else
			count += write(1, &manda[i++], 1);
	}
	va_end(ap);
	return (count);
}

int	ft_print_format(t_flags *flags, const char *manda, int *i, va_list ap)
{
	int	count;

	count = 0;
	if (manda[*i] == 'u')
		count += ft_print_dec(flags, (unsigned int)va_arg(ap, unsigned int));
	(*i)++;
	return (count);
}

void	ft_update_flags(t_flags *flags, const char *manda, int *i)
{
	if (manda[*i] == '0')
	{
		flags->zero = 1;
		flags->minus = 0;
	}
	if (isdigit(manda[*i]) != 0 || manda[*i] == '.')
	{
		if (manda[*i] == '.')
			flags->precision = atoi(&manda[++(*i)]) + 1;
		else
			flags->width = atoi(&manda[*i]);
		while (isdigit(manda[*i]) != 0)
			(*i)++;
	}
}

int	ft_printd(long n)
{
	int		count;
	char	c;

	count = 0;
	if (n < 0)
	{
		count += write(1, "-", 1);
		n = -n;
	}
	if (n < 10)
	{
		c = n + '0';
		return (count += write(1, &c, 1));
	}
	count += ft_printd(n / 10);
	count += ft_printd(n % 10);
	return (count);
}

int	ft_printd_precision(int pre, long n, char sign)
{
	int	count;
	int	len;

	count = 0;
	len = ft_declen(n);
	if (n == 0 && pre == 0)
		return (0);
	if (n < 0)
		return (ft_printd_zero(n, pre + 1));
	if (sign == '+' || sign == ' ')
		count += write(1, &sign, 1);
	while (count < pre - len)
		count += write(1, "0", 1);
	return (count + print_unsigned_dec(n));
}

int	ft_printd_zero(long n, int pre)
{
	int	count;
	int	len;

	count = 0;
	len = ft_declen(ft_abs(n));
	if (n < 0)
	{
		count += write(1, "-", 1);
		n = -n;
	}
	while (count < pre - len)
		count += write(1, "0", 1);
	count += print_unsigned_dec(n);
	return (count);
}

int print_unsigned_dec(unsigned int u)
{
    int count;
	char	c;

    count = 0;
    if (u < 10)
    {
        count++;
		c = u + 48;
        write(1, &c, 1);
        return (count);
    }
    count += print_unsigned_dec(u / 10);
    count += print_unsigned_dec(u % 10);
    return (count);
}

int	ft_printd_width(int width, unsigned int n, char sign, char c)
{
	int	len;
	int	count;

	len = ft_declen(ft_abs(n));
	count = 0;
	if (n < 0)
	{
		if (c == '0')
			return (ft_printd_zero(n, width));
		while (count < width - len - 1)
			count += write(1, " ", 1);
		return (count + ft_printd(n));
	}
	if (sign == '+')
		return (ft_printd_wplus(width, n, sign, c));
	while (count < width - len)
		count += write(1, &c, 1);
	return (count + print_unsigned_dec(n));
}

int	ft_printd_wplus(int width, long n, char sign, char c)
{
	int	len;
	int	count;

	len = ft_declen(ft_abs(n));
	count = 0;
	if (c == '0')
	{
		write(1, &sign, 1);
		while (count < width - len)
			count += write(1, "0", 1);
		return (count + ft_printd(n) + 1);
	}
	while (count < width - len)
		count += write(1, " ", 1);
	write(1, &sign, 1);
	return (count + ft_printd(n) + 1);
}

int	ft_printd_wp(int width, int pre, long n, char sign)
{
	int	len;
	int	count;

	count = 0;
	len = ft_declen(ft_abs(n));
	if (n < 0)
	{
		if (pre > len)
			len = pre;
		while (count < width - len - 1)
			count += write(1, " ", 1);
		return (count + ft_printd_precision(pre, n, sign));
	}
	if (sign == '+' || sign == ' ')
		return (ft_printd_wpsign(width, pre, n, sign));
	if (n == 0)
		len = 0;
	if (pre > len)
		len = pre;
	while (count < width - len)
		count += write (1, " ", 1);
	return (count + ft_printd_precision(pre, n, sign));
}

int	ft_printd_wpsign(int width, int pre, long n, char sign)
{
	int	len;
	int	count;

	count = 0;
	len = ft_declen(ft_abs(n));
	if (pre > len)
		len = pre;
	while (count < width - len - 1)
		count += write (1, " ", 1);
	return (count + ft_printd_precision(pre, n, sign));
}


#include <stdio.h>

int main (void)
{
	ft_printf("ft_printf: %20u, %020u\n", -1024u, -1024u);
	printf("   printf: %20u, %020u\n", -1024u, -1042u);
}
