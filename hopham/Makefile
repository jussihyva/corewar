# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: HoangPham <HoangPham@student.42.fr>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/06/09 11:31:39 by HoangPham         #+#    #+#              #
#    Updated: 2020/06/09 15:20:24 by HoangPham        ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = asm

SRC = main.c \
	utils.c \
	get.c \
	init.c

S_DIR = src
O_DIR = obj
OBJ = $(addprefix $(O_DIR)/, $(SRC:.c=.o))
HEAD = asm.h op.h
H_DIR = includes
GCC = gcc -Wall -Wextra -Werror
DEPS = $(patsubst %,$(H_DIR)/%,$(HEAD))
LIBFT_FOLDER		=	lib/lib_ft
LIBFT_PRINTF_FOLDER	=	lib/lib_ftprintf
LIBFT				=	$(LIBFT_FOLDER)/libft.a
LIBFT_PRINTF		=	$(LIBFT_PRINTF_FOLDER)/libftprintf.a
LIB					=	-L $(LIBFT_FOLDER) -l ft -L $(LIBFT_PRINTF_FOLDER) -l ftprintf

all: $(NAME)

$(NAME): $(OBJ) | $(LIBFT)
	@$(GCC) -o $@ $^ -I $(H_DIR) $(LIB) $(OBJ)
	@echo  "test \033[1;32m[OK]\033[0m"

$(OBJ): $(OBJ_DIR)/%.o: $(SRC_FOLDER)/%.c $(HEADER) | $(OBJ_DIR)
	@echo "$(@) created."
	@$(GCC) $(INCLUDES) -c -o $@ $<

$(OBJ_DIR):
	@mkdir $(OBJ_DIR)

$(LIBFT):
	make -C ${LIBFT_FOLDER}

$(LIBFT_PRINTF):
	make -C ${LIBFT_PRINTF_FOLDER}

clean:
	make clean -C $(LIBFT_FOLDER)
	make clean -C $(LIBFT_PRINTF_FOLDER)
	@rm -rf $(O_DIR)
	@echo "clean \033[1;32m[OK]\033[0m"

fclean:
	@rm -rf $(O_DIR)
	@rm -rf $(NAME)
	@echo "fclean \033[1;32m[OK]\033[0m"

del:
	rm -rf *.cor
	@echo "cor_del \033[1;32m[OK]\033[0m"

re: fclean all

#$(LIBFT):
#	@make -C libft
