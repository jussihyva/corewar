# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/05/05 11:36:37 by ubuntu            #+#    #+#              #
#    Updated: 2020/05/07 23:20:54 by ubuntu           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= decoder
CC			=	clang
INCLUDES	=	-I lib/lib_ft -I lib/lib_ftprintf
LIB			=	-L lib/lib_ft -l ft -L lib/lib_ftprintf -l ftprintf

SRC			=	src/input_1.c src/decoder.c src/memory_1.c src/print_hex.c src/op.c

all:
	$(CC) -Wall -Werror -Wextra $(INCLUDES) -o decoder $(SRC) $(LIB)

.PHONY: all
