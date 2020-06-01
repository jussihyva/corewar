# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/05/05 11:36:37 by ubuntu            #+#    #+#              #
#    Updated: 2020/06/01 15:50:41 by ubuntu           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME1				= decoder
NAME2				= cpu
CC					=	clang
C_FLAGS				=	-g -Wall -Werror -Wextra
INCLUDES			=	-I lib/lib_ft -I lib/lib_ftprintf
HEADER				=	src/decoder.h src/op.h src/cpu.h
LIBFT_FOLDER		=	lib/lib_ft
LIBFT_PRINTF_FOLDER	=	lib/lib_ftprintf
LIBFT				=	$(LIBFT_FOLDER)/libft.a
LIBFT_PRINTF		=	$(LIBFT_PRINTF_FOLDER)/libftprintf.a
LIB					=	-L $(LIBFT_FOLDER) -l ft -L LIBFT_PRINTF_FOLDER -l ftprintf

SRC_FOLDER	=	src
NAME1_MAIN	=	src/decoder.c
NAME2_MAIN	=	src/cpu.c
SRC			=	input_1.c memory_1.c print_hex.c print_asm.c op.c \
				instruction_1.c instruction_2.c execution_1.c

OBJ_FOLDER	=	obj
OBJ			=	$(addprefix $(OBJ_FOLDER)/, $(patsubst %.c, %.o, $(SRC)))

all: $(LIBFT) $(LIBFT_PRINTF) $(NAME1) $(NAME2)

$(NAME1): $(OBJ) $(NAME1_MAIN)
	@echo "$(NAME1) created."
	@$(CC) $(C_FLAGS) $(INCLUDES) -o $(NAME1) $(OBJ) $(NAME1_MAIN) $(LIB)
	@$(CC) $(C_FLAGS) $(INCLUDES) -o $(NAME2) $(OBJ) $(NAME2_MAIN) $(LIB)

$(NAME2): $(OBJ) $(NAME2_MAIN)
	@echo "$(NAME2) created."
	@$(CC) $(C_FLAGS) $(INCLUDES) -o $(NAME1) $(OBJ) $(NAME1_MAIN) $(LIB)
	@$(CC) $(C_FLAGS) $(INCLUDES) -o $(NAME2) $(OBJ) $(NAME2_MAIN) $(LIB)

$(OBJ): $(OBJ_FOLDER)/%.o: $(SRC_FOLDER)/%.c $(HEADER) | $(OBJ_FOLDER)
	@echo "$(@) created."
	@$(CC) $(C_FLAGS) $(INCLUDES) -c -o $@ $<

$(OBJ_FOLDER):
	@mkdir $(OBJ_FOLDER)

$(LIBFT):
	make -C ${LIBFT_FOLDER}

$(LIBFT_PRINTF):
	make -C ${LIBFT_PRINTF_FOLDER}


.PHONY: all
