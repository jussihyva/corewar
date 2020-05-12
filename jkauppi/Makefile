# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/05/05 11:36:37 by ubuntu            #+#    #+#              #
#    Updated: 2020/05/12 11:46:12 by ubuntu           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= decoder
CC			=	clang
C_FLAGS		=	-g -Wall -Werror -Wextra
INCLUDES	=	-I lib/lib_ft -I lib/lib_ftprintf
HEADER		=	src/decoder.h src/op.h
LIB			=	-L lib/lib_ft -l ft -L lib/lib_ftprintf -l ftprintf

SRC_FOLDER	=	src
SRC			=	input_1.c decoder.c memory_1.c print_hex.c print_asm.c op.c \
				instruction_1.c instruction_2.c

OBJ_FOLDER	=	obj
OBJ			=	$(addprefix $(OBJ_FOLDER)/, $(patsubst %.c, %.o, $(SRC)))

all: $(NAME)

$(NAME): $(OBJ)
	@echo "$(NAME) created."
	@$(CC) $(C_FLAGS) $(INCLUDES) -o $(NAME) $(OBJ) $(LIB)

$(OBJ): $(OBJ_FOLDER)/%.o: $(SRC_FOLDER)/%.c $(HEADER) | $(OBJ_FOLDER)
	@echo "$(@) created."
	@$(CC) $(C_FLAGS) $(INCLUDES) -c -o $@ $<

$(OBJ_FOLDER):
	@mkdir $(OBJ_FOLDER)

.PHONY: all
