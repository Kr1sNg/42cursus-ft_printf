/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tat-nguy <tat-nguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 12:00:37 by tat-nguy          #+#    #+#             */
/*   Updated: 2024/11/16 17:50:06 by tat-nguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRINTF_H
# define PRINTF_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdarg.h>
#include <stdbool.h>
#include <limits.h>

//Buffer of 4096
#define BUF_SIZE 4096
#define FLAGS	"+ 0-#"
#define NUMBER	"0123456789"
#define SPECIFIERS "cspdiuxX%"

typedef	enum
{
	BASE_2 = 2,
	BASE_8 = 8,
	BASE_10 = 10,
	BASE_16 = 16
}	e_base;

// Symbolic error
typedef	enum
{
	OK = 0;
	MALLOC_ERROR = -42,
	PARSE_ERROR = -1337,
}		e_error;

/*
 * All the bools [+-' '0#][width][.precision]
 */
typedef struct s_format
{
	//PARSING STUFF
	bool	left_justified;
	bool	plus;
	bool	space;
	bool	hash;
	bool	zero_pad;
	// "csdixXpu%"
	char	specifier;
	// width + precision
	int		width_value;
	int		precision_value;
	bool	upper_case;
	e_base	base;
}			t_format;

typedef	struct s_data
{
	// pointer copy to fmt
	const char	*s;
	// valist -> va_arg(ap, int);
	va_list		ap;
	// chars written
	int			chars_written;
	// [buffer]
	char		*buf;
	int			buffer_index;

	t_format	format;
}			t_data;

// PROTOTYPE
void	my_memset(void *ptr, int value, size_t n);

bool	in(const char *s, char c);

int	parse_format(t_data *data);

void	write_buff(t_data *data, char c);

#endif
