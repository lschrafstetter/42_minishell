# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dfranke <dfranke@student.42wolfsburg.de>   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/25 17:39:13 by lschrafs          #+#    #+#              #
#    Updated: 2022/08/17 14:51:24 by dfranke          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

COMPILER = cc

CFLAGS = -Wall -Wextra -Werror

SRCS = \
		ft_isalpha ft_isdigit ft_isalnum ft_isascii ft_isprint \
		ft_strlen ft_memset ft_bzero ft_memcpy ft_memmove ft_strlcpy \
		ft_strlcat ft_toupper ft_tolower ft_strchr ft_strrchr ft_memchr \
		ft_memcmp ft_strnstr ft_atoi ft_strncmp ft_strdup ft_calloc \
		ft_substr ft_strjoin ft_strtrim ft_split ft_itoa ft_strmapi \
		ft_striteri ft_putchar_fd ft_putstr_fd ft_putendl_fd ft_putnbr_fd \
		ft_atoi_e ft_strthreejoin \
		\
		ft_printf ft_printchar ft_printstring ft_printint ft_printuint \
		ft_printhex \
		\
		get_next_line get_next_line_utils
		

OBJS = ${SRCS:%=%.o}

all: ${NAME}

$(NAME): ${OBJS}
	ar rcs $@ $?

%.o: %.c
	${COMPILER} ${CFLAGS} -c $< -o $@

clean:
	rm -f *.o

fclean: clean
	rm -f ${NAME}

re: fclean all

.PHONY: all clean fclean re