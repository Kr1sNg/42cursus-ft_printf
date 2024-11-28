/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tat-nguy <tat-nguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 13:15:16 by tat-nguy          #+#    #+#             */
/*   Updated: 2024/11/21 00:26:47 by tat-nguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

/*
** :::::::::::::::::::::::::::::::::* HEADERS *:::::::::::::::::::::::::::::: **
*/

# include <unistd.h>
# include <stdarg.h>
# include <limits.h>

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


int print_unsigned_dec(long u);

#endif