/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tat-nguy <tat-nguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 11:55:33 by tat-nguy          #+#    #+#             */
/*   Updated: 2024/11/16 18:04:30 by tat-nguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

void	render_format(t_data *data)
{
	char	specifier;

	specifier = data->format.specifier;

	if (specifier == '%')
		print_char(data, '%');
	else if (specifier == 'c')
		print_char(data, va_arg(data->ap, int));
	else if (specifier == 's')
		print_str(data, va_arg(data->ap, char *));
}

static int	init_data(t_data *data, const char *fmt)
{
	data->s = fmt;
	data->chars_written = 0;
	data->buf = malloc(sizeof(char) * BUF_SIZE);
	if (data->buf == NULL)
		return MALLOC_ERROR;
	data->buffer_index = 0;
	my_memset(data->buf, 0, sizeof(char) * BUF_SIZE);
	return (OK);
}


int	ft_printf (const char *fmt, ...)
{
	t_data	data;
	
	va_start(data->ap, fmt);
	if (init_data(&data, fmt))
		return (-1);
	while (*data->s != '\0')
	{
		if (*data->s == '%' && *(++data->s))
		{
			parse_format(&data)
			{
				return PARSE_ERROR;
			}
			render_format(&data);
		}
		else
		{
			write_buf(&data, *data->s);
		}
		++data->s;
	}
	//write output
	flush_buf(&data);
	
	va_end(data->ap);
	free(data->buf)
	return (data->chars_written);
}