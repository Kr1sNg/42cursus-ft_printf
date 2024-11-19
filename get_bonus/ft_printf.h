/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tat-nguy <tat-nguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 13:15:16 by tat-nguy          #+#    #+#             */
/*   Updated: 2024/11/14 21:20:06 by tat-nguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

/*
** :::::::::::::::::::::::::::::::::* HEADERS *:::::::::::::::::::::::::::::: **
*/

# include <unistd.h>
# include <stdarg.h>

/*
** :::::::::::::::::::::::::::* STRUCT DECLARATION *::::::::::::::::::::::::: **
*/

typedef	struct s_flags
{
	//[-+' '#0.]
	int	minus; //for align_left
	int plus; // +0 -42
	int	space; // ' '42
	int	hash; // '0x' or '0X'
	int	zero; // 000042
	int	width;
	int	point; // [forty_tw" "]
	int	precision;
}	t_flags;

/*
** ::::::::::::::::::::::::::* FUNCTION PROTOTYPES *::::::::::::::::::::::::: **
*/

//	ft_printf.c

int		ft_printf(const char *mand_arg, ...);
int		ft_print_format(t_flags *flags, const char *mand_arg, int *i, va_list ap);
void	ft_update_flags(t_flags *flags, const char *mand_arg, int *i);

//	ft_printf_utils.c

int		ft_print_char(int c);
int		ft_print_str(char *str);
int		ft_print_dec(long n);
int		ft_print_hex(unsigned long long n, char c);
int		ft_print_ptr(unsigned long long p);

//	ft_printf_tools.c

void	ft_bzero(void *s, size_t n);
void	*ft_memchr(const void *s, int c, size_t n);
int		ft_isdigit(int c);
int 	ft_atoi(const char *nptr);


#endif