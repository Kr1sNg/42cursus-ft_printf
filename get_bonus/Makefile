# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tat-nguy <tat-nguy@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/07 15:19:42 by tat-nguy          #+#    #+#              #
#    Updated: 2024/11/21 00:29:54 by tat-nguy         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Variables
NAME		= libftprintf.a
CC 			= cc
CFLAGS 		= -Wall -Wextra -Werror
AR			= ar -rc
RANLIB		= ranlib
RM			= rm -rf

# Paths and Files
SRCS 		= ft_printf.c ft_printf_cs.c ft_printf_dec.c ft_printf_dwp.c \
				ft_printf_hex.c ft_printf_ptr.c ft_printf_str.c \
				ft_printf_tools.c ft_printf_utils.c 

OBJS 		= $(SRCS:.c=.o)

INCLUDE		= .

# Rules
all:		$(NAME)

$(NAME):	$(OBJS)
			$(AR) $(NAME) $(OBJS)
			$(RANLIB) $(NAME)

bonus:		all

.c.o:
			$(CC) $(CFLAGS) -I $(INCLUDE) -c $< -o $@

clean:
			$(RM) $(OBJS) $(BONUS_OBJS)

fclean:		clean
			$(RM) $(NAME)

re:			fclean all

.PHONY: all clean fclean re bonus
