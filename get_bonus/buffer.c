/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tat-nguy <tat-nguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 17:44:51 by tat-nguy          #+#    #+#             */
/*   Updated: 2024/11/16 17:57:08 by tat-nguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

void	flush_buf(t_data *data)
{
	// write-> flush in stdout + stock chars_written
	data->chars_written += write(1, data->buf, data->buffer_index);
	
	//refresh after call
	my_memset(data->buf, 0, BUF_SIZE);
	data->buffer_index = 0;
}

void	write_buff(t_data *data, char c)
{
	if (data->buffer_index == BUF_SIZE)
	{
		//refresh index and write str in stdoutput
		flush_buf(data);
	}
	data->buf[data->buffer_index++] = c;
}