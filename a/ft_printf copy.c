
# include <unistd.h>
# include <stdarg.h>

/*
** :::::::::::::::::::::::::::* STRUCT DECLARATION *::::::::::::::::::::::::: **
*/

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

/*
** ::::::::::::::::::::::::::* FUNCTION PROTOTYPES *::::::::::::::::::::::::: **
*/

//	ft_printf.c

int		ft_printf(const char *manda, ...);
int		ft_print_format(t_flags *flags, const char *manda, int *i, va_list ap);
void	ft_update_flags(t_flags *flags, const char *manda, int *i);

//	ft_printf_utils.c

int		ft_hexlen(unsigned long long n);
int		ft_declen(unsigned long long n);
int		ft_abs(long n);

//	ft_printf_tools.c

void	ft_bzero(void *s, size_t n);
void	*ft_memchr(const void *s, int c, size_t n);
int		ft_isdigit(int c);
int		ft_atoi(const char *nptr);
int		ft_strlen(char *s);

//	ft_printf_cs.c

int		ft_print_char(t_flags *flags, int c);
int		ft_prints(char *str);

//	ft_printf_str.c

int		ft_print_str(t_flags *flags, char *str);
int		ft_prints_precision(int precision, char *str);
int		ft_prints_width(int width, char *str, int minus);
int		ft_prints_duo(int width, int precision, char *str, int minus);

//	ft_printf_hex.c

int		ft_print_hex(t_flags *flags, unsigned long long n, char x);
int		ft_printh_precision(int pre, unsigned long long n, char x);
int		ft_printh_minus(t_flags *flags, unsigned long long n, char x);
int		ft_printh_hash(t_flags *flags, unsigned long long n, char x, char c);
int		ft_printh_width(t_flags *flags, unsigned long long n, char x, char c);

//	ft_printf_ptr.c

int		ft_print_ptr(t_flags *flags, unsigned long long p);
int		ft_printp(int width, int minus, unsigned long long p);
int		ft_printh(unsigned long long n, char x);

//	ft_printf_dec.c

int		ft_print_dec(t_flags *flags, long n);
int		ft_printd(long n);
int		ft_printd_minus(int width, int pre, long n, char sign);
int		ft_printd_precision(int pre, long n, char sign);
int		ft_printd_zero(long n, int pre);

//	ft_printf_dwp.c

int		ft_printd_width(int width, long n, char sign, char c);
int		ft_printd_wplus(int width, long n, char sign, char c);
int		ft_printd_wp(int width, int pre, long n, char sign);
int		ft_printd_wpsign(int width, int pre, long n, char sign);

//

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
		ft_bzero(&flags, sizeof(t_flags));
		if (manda[i] == '%')
		{
			i++;
			while (ft_memchr("-+ #0.", manda[i], 6) || ft_isdigit(manda[i]))
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
	if (manda[*i] == 'c')
		count += ft_print_char(flags, va_arg(ap, int));
	else if (manda[*i] == 's')
		count += ft_print_str(flags, va_arg(ap, char *));
	else if (manda[*i] == 'p')
		count += ft_print_ptr(flags,
				(unsigned long long)va_arg(ap, unsigned long));
	else if (manda[*i] == 'd' || manda[*i] == 'i')
		count += ft_print_dec(flags, (long)va_arg(ap, int));
	else if (manda[*i] == 'u')
		count += ft_print_dec(flags, (long)va_arg(ap, unsigned int));
	else if (manda[*i] == 'x' || manda[*i] == 'X')
		count += ft_print_hex(flags,
				(unsigned long long)va_arg(ap, unsigned int), manda[*i]);
	else if (manda[*i] == '%')
		count += write(1, "%", 1);
	(*i)++;
	return (count);
}

void	ft_update_flags(t_flags *flags, const char *manda, int *i)
{
	while (ft_memchr("-+ #", manda[*i], 4) != NULL)
	{
		if (manda[*i] == '-')
			flags->minus = 1;
		if (manda[*i] == '+')
			flags->plus = 1;
		if (manda[*i] == ' ')
			flags->space = 1;
		if (manda[*i] == '#')
			flags->hash = 1;
		(*i)++;
	}
	if (manda[*i] == '0')
		flags->zero = 1;
	if (ft_isdigit(manda[*i]) != 0 || manda[*i] == '.')
	{
		if (manda[*i] == '.')
			flags->precision = ft_atoi(&manda[++(*i)]) + 1;
		else
			flags->width = ft_atoi(&manda[*i]);
		while (ft_isdigit(manda[*i]) != 0)
			(*i)++;
	}
}

// CS

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

// DEC

int	ft_print_dec(t_flags *flags, long n)
{
	char	c;
	char	sign;

	c = ' ';
	sign = '-';
	if (flags->space == 1)
		sign = ' ';
	if (flags->plus == 1)
		sign = '+';
	if (flags->zero == 1)
		c = '0';
	if (flags->minus == 1)
		return (ft_printd_minus(flags->width, (flags->precision - 1), n, sign));
	if (flags->width > 0 && flags->precision > 0)
		return (ft_printd_wp(flags->width, (flags->precision - 1), n, sign));
	if (flags->width > 0)
		return (ft_printd_width(flags->width, n, sign, c));
	if (flags->precision > 0)
		return (ft_printd_wp(flags->width, (flags->precision - 1), n, sign));
	if (n < 0)
		return (ft_printd(n));
	if (sign == '+' || sign == ' ')
		return (write(1, &sign, 1) + ft_printd(n));
	return (ft_printd(n));
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

int	ft_printd_minus(int width, int pre, long n, char sign)
{
	int	count;

	count = 0;
	if (n == 0 && width > 0)
	{
		if (pre != 0)
			count += write(1, "0", 1);
		while (count < pre)
			count += write(1, "0", 1);
		while (count < width)
			count += write(1, " ", 1);
		return (count);
	}
	count += ft_printd_precision(pre, n, sign);
	while (count < width)
		count += write(1, " ", 1);
	return (count);
}

int	ft_printd_precision(int pre, long n, char sign)
{
	int	count;
	int	len;

	count = 0;
	len = ft_declen(ft_abs(n));
	if (n == 0 && pre == 0)
		return (0);
	if (n < 0)
		return (ft_printd_zero(n, pre + 1));
	if (sign == '+' || sign == ' ')
		count += write(1, &sign, 1);
	while (count < pre - len)
		count += write(1, "0", 1);
	return (count + ft_printd(n));
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
	count += ft_printd(n);
	return (count);
}

// DWP

int	ft_printd_width(int width, long n, char sign, char c)
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
	return (count + ft_printd(n));
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
		while (count < width - len) //width - len - 1
			count += write(1, "0", 1);
		return (count + ft_printd(n) + 1);
	}
	while (count < width - len) //width - len - 1
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
	if (count < 0)
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

// HEX

int	ft_print_hex(t_flags *flags, unsigned long long n, char x)
{
	char	c;

	c = ' ';
	if (flags->zero == 1)
		c = '0';
	if (flags->width > 0 && flags->precision > 0)
		c = ' ';
	if (flags->minus == 1)
		return (ft_printh_minus(flags, n, x));
	if (flags->hash == 1)
		return (ft_printh_hash(flags, n, x, c));
	if (flags->width > 0)
		return (ft_printh_width(flags, n, x, c));
	if (flags->precision > 0)
		return (ft_printh_precision((flags->precision - 1), n, x));
	return (ft_printh(n, x));
}

int	ft_printh_precision(int pre, unsigned long long n, char x)
{
	int	count;

	if (n == 0 && pre == 0)
		return (0);
	count = ft_hexlen(n);
	while (count < pre)
		count += write(1, "0", 1);
	ft_printh(n, x);
	return (count);
}

int	ft_printh_minus(t_flags *flags, unsigned long long n, char x)
{
	int		count;

	count = 0;
	if (flags->hash == 1)
	{
		if (n != 0)
		{
			count += write(1, "0", 1);
			count += write(1, &x, 1);
		}
	}
	count += ft_printh_precision((flags->precision - 1), n, x);
	while (count < flags->width)
		count += write(1, " ", 1);
	return (count);
}

int	ft_printh_hash(t_flags *flags, unsigned long long n, char x, char c)
{
	int		count;
	int		len;

	count = 0;
	len = ft_hexlen(n);
	if ((flags->precision - 1) > len)
		len = flags->precision - 1;
	if (n == 0 && flags->precision == 1)
		len = 0;
	while (count < flags->width - 2 - len)
		count += write(1, &c, 1);
	if (n != 0)
	{
		count += write(1, "0", 1);
		count += write(1, &x, 1);
	}
	count += ft_printh_precision((flags->precision - 1), n, x);
	return (count);
}

int	ft_printh_width(t_flags *flags, unsigned long long n, char x, char c)
{
	int	count;
	int	len;

	count = 0;
	len = ft_hexlen(n);
	if ((flags->precision - 1) > len)
		len = flags->precision - 1;
	if (n == 0 && flags->width == 1)
		len = 0;
	while (count < (flags->width - len))
		count += write(1, &c, 1);
	count += ft_printh_precision((flags->precision - 1), n, x);
	return (count);
}

// PTR


int	ft_print_ptr(t_flags *flags, unsigned long long p)
{
	int		count;

	count = 0;
	if (p == 0)
	{
		count = 5;
		if (flags->width <= 5)
			return (write(1, "(nil)", 5));
		if (flags->minus == 1)
		{
			write(1, "(nil)", 5);
			while (flags->width > count)
				count += write(1, " ", 1);
			return (count);
		}
		while (flags->width > count)
			count += write(1, " ", 1);
		write(1, "(nil)", 5);
		return (count);
	}
	if (flags->width > 0)
		return (ft_printp(flags->width, flags->minus, p));
	count += write(1, "0x", 2);
	count += ft_printh(p, 'x');
	return (count);
}

int	ft_printp(int width, int minus, unsigned long long p)
{
	int	count;

	count = ft_hexlen(p) + 2;
	if (width <= count)
	{
		write(1, "0x", 2);
		ft_printh(p, 'x');
		return (count);
	}
	if (minus == 1)
	{
		write(1, "0x", 2);
		ft_printh(p, 'x');
		while (width > count)
			count += write(1, " ", 1);
		return (count);
	}
	while (width > count)
		count += write(1, " ", 1);
	write(1, "0x", 2);
	ft_printh(p, 'x');
	return (count);
}

int	ft_printh(unsigned long long n, char x)
{
	int		count;
	char	*str;

	count = 0;
	if (n < 16)
	{
		if (x == 'x')
		{
			str = "0123456789abcdef";
			return (count += write(1, &str[n], 1));
		}
		else if (x == 'X')
		{
			str = "0123456789ABCDEF";
			return (count += write(1, &str[n], 1));
		}
	}
	count += ft_printh(n / 16, x);
	count += ft_printh(n % 16, x);
	return (count);
}

// STR

int	ft_print_str(t_flags *flags, char *str)
{
	if (flags->width > 0 && flags->precision > 0)
		return (ft_prints_duo(flags->width, (flags->precision -1), str,
				flags->minus));
	if (flags->width > 0)
		return (ft_prints_width(flags->width, str, flags->minus));
	if (flags->precision > 0)
		return (ft_prints_precision((flags->precision - 1), str));
	return (ft_prints(str));
}

int	ft_prints_precision(int precision, char *str)
{
	int	i;

	i = 0;
	if (str == NULL)
	{
		if (precision < 6)
			precision = 0;
		ft_prints_precision(precision, "(null)");
	}
	while (str[i] != '\0' && i < precision)
		i += write (1, &str[i], 1);
	return (i);
}

int	ft_prints_width(int width, char *str, int minus)
{
	int	i;
	int	strlen;

	if (str == NULL)
		str = "(null)";
	strlen = ft_strlen(str);
	i = 0;
	if (strlen >= width)
		return (ft_prints(str));
	if (minus == 1)
	{
		i += ft_prints(str);
		while (i < width)
			i += write(1, " ", 1);
		return (i);
	}
	while (i < width - strlen)
		i += write(1, " ", 1);
	return (i + ft_prints(str));
}

int	ft_prints_duo(int width, int precision, char *str, int minus)
{
	int	strlen;
	int	count;

	if (str == NULL)
	{
		str = "(null)";
		if (precision < 6)
			precision = 0;
	}
	strlen = ft_strlen(str);
	if (precision < strlen)
		strlen = precision;
	if (strlen >= width)
		return (ft_prints_precision(precision, str));
	count = 0;
	if (minus == 1)
	{
		count += ft_prints_precision(precision, str);
		while (count < width)
			count += write(1, " ", 1);
		return (count);
	}
	while (count < width - strlen)
		count += write(1, " ", 1);
	return (count + ft_prints_precision(precision, str));
}


// TOOLS

void	ft_bzero(void *s, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		((unsigned char *)s)[i] = 0;
		i++;
	}
}

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		if (((const unsigned char *)s)[i] == (unsigned char)c)
			return ((unsigned char *)s + i);
		i++;
	}
	return (NULL);
}

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (2048);
	else
		return (0);
}

int	ft_atoi(const char *nptr)
{
	int	i;
	int	nb;

	i = 0;
	nb = 0;
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		nb = nb * 10 + (nptr[i] - '0');
		i++;
	}
	return (nb);
}

int	ft_strlen(char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

// UTILS


int	ft_hexlen(unsigned long long n)
{
	int	i;

	i = 1;
	while (n >= 16)
	{
		n = n / 16;
		i++;
	}
	return (i);
}

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

#include <stdio.h>
#include <limits.h>

int main (void)
{
	int a = ft_printf("ft_printf: [%-163.23u%-68.0X]\n", 3421138903u, 514939578u);
	int b = printf("   printf: [%-163.23u%-68.0X]\n", 3421138903u, 514939578u);
	ft_printf("characters were written in total is %i\n", a);
	printf("characters were written in total is %i\n", b);
}