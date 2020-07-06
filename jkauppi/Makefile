# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/05/05 11:36:37 by ubuntu            #+#    #+#              #
#    Updated: 2020/07/06 17:51:18 by jkauppi          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME1		=	decoder
NAME2		=	cpu
CC			=	clang
C_FLAGS		=	-g -Wall -Werror -Wextra
LIB_FOLDER	=	../jkauppi/lib
INCLUDES	=	-I $(LIB_FOLDER)
LIB			=	-L $(LIB_FOLDER) -l ft -l ftprintf

SRC			=	input_1.c input_cpu.c memory_1.c \
				print_hex.c print_asm.c op.c print_cpu.c print_memory.c\
				instruction_1.c instruction_2.c \
				execution_1.c execution_2.c execution_3.c execution_4.c \
				cycles_cpu.c cpu_1.c

HEADERS		=	decoder.h op.h cpu.h common.h

SRC_FOLDER	=	src

NAME1_MAIN	=	$(SRC_FOLDER)/decoder.c
NAME2_MAIN	=	$(SRC_FOLDER)/cpu.c

HEADER_LIST	=	$(addprefix $(SRC_FOLDER)/, $(HEADERS))

OBJ_FOLDER	=	obj
OBJ			=	$(addprefix $(OBJ_FOLDER)/, $(patsubst %.c, %.o, $(SRC)))

all: make_lib $(NAME1) $(NAME2)

$(NAME1): $(OBJ) $(NAME1_MAIN) $(HEADER_LIST)
	@echo "$@ created."
	@$(CC) $(C_FLAGS) $(INCLUDES) -o $@ $(OBJ) $(NAME1_MAIN) $(LIB)

$(NAME2): $(OBJ) $(NAME2_MAIN) $(HEADER_LIST)
	@echo "$@ created."
	@$(CC) $(C_FLAGS) $(INCLUDES) -o $@ $(OBJ) $(NAME2_MAIN) $(LIB)

$(OBJ): $(OBJ_FOLDER)/%.o: $(SRC_FOLDER)/%.c $(HEADER_LIST) | $(OBJ_FOLDER)
	@echo "$(@) created."
	@$(CC) $(C_FLAGS) $(INCLUDES) -c -o $@ $<

$(OBJ_FOLDER):
	@mkdir $(OBJ_FOLDER)

make_lib:
	@make -C ${LIB_FOLDER} 1>/dev/null

.PHONY: all make_lib
