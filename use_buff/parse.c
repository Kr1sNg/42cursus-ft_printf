/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tat-nguy <tat-nguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 16:52:33 by tat-nguy          #+#    #+#             */
/*   Updated: 2024/11/16 17:39:55 by tat-nguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

static int	my_atoi(t_data *data)
{
	int	value;

	value = 0;
	while (in(NUMBER, *data->s))
	{
		value = (value * 10) + (*data->s++ - '0');
	}
	return (value);
}


/* flags are: "%[0-' '#+][10][.3]d" */
static void prase_flags(t_data *data)
{
	char	flag;
	
	while (in(FLAGS, *data->s))
	{
		flag = *data->s;
		if (flag == '0')
			data->format.zero_pad = true;
		else if (flag == '+')
			data->format.plus = true;
		else if (flag == ' ')
			data->format.space = true;
		else if (flag == '#')
			data->format.hash = true;
		else if (flag == '-')
			data->format.left_justified = true;
		++data->s;
	}
}

static void	get_value(t_data *data, int *value)
{
	if (*data->s == '*')
	{
		*value = va_arg(data->ap, int);
		++data->s;
		return;
	}
	*value = my_atoi(data);
}


int	parse_format(t_data *data)
{
	//refresh data
	my_memset(&data->format, 0, sizeof(t_format));
	// set precision_value to 0, not width
	data->format.precision_value = -1;

	//[0-' '#+]
	parse_flags(data);

	// [width]
	parse_width(data);
	get_value(data, &data->format.width_value);

	//[.precision_value]
	if (*data->s == '.' && *(++data->))
		get_value(data, &data->format.precision_value);
	
	if (!in(SPECIFIERS, *data->s))
		return PARSE_ERROR;
	else
	{
		data->format.specifier = *data->s;
		if (in("diu", data->format.specifier))
			data->format.base = BASE_10;
		else if (in("xXp", data->format.specifier))
			data->format.base = BASE_16;
			if (data->format.specifier == 'X')
				data->format.upper_case = true;
	}
	
	return OK;
	
}
