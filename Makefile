# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/05/05 11:36:37 by ubuntu            #+#    #+#              #
#    Updated: 2020/05/05 14:45:58 by ubuntu           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= decoder
CC			=	clang
INCLUDES	=	-I lib/lib_ft -I lib/lib_ftprintf
LIB			=	-L lib/lib_ft -l ft -L lib/lib_ftprintf -l ftprintf

all: $(NAME)
	$(CC) -Wall -Werror -Wextra $(INCLUDES) -o decoder src/decoder.c $(LIB)

.PHONY: all
