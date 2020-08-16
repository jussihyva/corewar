#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jhakala <jhakala@student.hive.fi>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/08/12 14:13:55 by jhakala           #+#    #+#              #
#    Updated: 2020/08/16 20:13:58 by jhakala          ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME_C = corewar
NAME_A = asm

C_SRC = main.c \
	init.c parse_av.c parse_utils.c champ_init.c read_to.c \
	wm_init.c carriage.c free.c \
	game/run_game.c game/game_utils.c game/check.c op.c \
	statements/op_live.c statements/op_ld.c statements/op_st.c statements/op_add.c \
	statements/op_sub.c statements/op_and.c statements/op_or.c statements/op_xor.c \
	statements/op_zjmp.c statements/op_ldi.c statements/op_sti.c statements/op_fork.c \
	statements/op_lld.c statements/op_lldi.c statements/op_lfork.c statements/op_aff.c \
	statements/op_utils.c \
	ncurses.c


A_SRC = main.c \
	op.c init.c \
    is.c skip.c rev.c \
    get_head.c get_lines.c \
    parse_cmd.c parse_utils.c \
    check_champ.c check_name.c \
    write.c

CS_DIR = src_corewar
CO_DIR = obj_corewar

AS_DIR = src_asm
AO_DIR = obj_asm

C_OBJ = $(addprefix $(CO_DIR)/, $(C_SRC:.c=.o))
A_OBJ = $(addprefix $(AO_DIR)/, $(A_SRC:.c=.o))

C_HEAD = test.h struct.h op.h
C_INC = -I $(H_DIR)/test.h -I $(H_DIR)/struct.h -I $(H_DIR)/op.h
A_HEAD = asm.h error.h op.h
A_INC = -I $(H_DIR)/asm.h -I $(H_DIR)/error.h -I $(H_DIR)/op.h
H_DIR = includes

LIBFT = libft/libft.a
GCC = gcc -Wall -Wextra -Werror

C_DEPS = $(patsubst %,$(H_DIR)/%,$(C_HEAD))
A_DEPS = $(patsubst %,$(H_DIR)/%,$(A_HEAD))

all: $(LIBFT) $(NAME_C) $(NAME_A)

$(NAME_C): $(C_OBJ)
	@$(GCC) -o $@ $^ $(C_INC) $(LIBFT) -lncurses
	@echo "corewar \033[1;32m[OK]\033[0m"

$(CO_DIR)/%.o: $(CS_DIR)/%.c $(C_DEPS)
	$(GCC) -o $@ -c $< -I $(H_DIR)

$(C_OBJ): | $(CO_DIR)

$(NAME_A): $(A_OBJ)
	@$(GCC) -o $@ $^ $(A_INC) $(LIBFT)
	@echo "asm \033[1;32m[OK]\033[0m"

$(AO_DIR)/%.o: $(AS_DIR)/%.c $(A_DEPS)
	$(GCC) -o $@ -c $< -I $(H_DIR)

$(A_OBJ): | $(AO_DIR)

clean:
	rm -rf $(CO_DIR)
	rm -rf $(AO_DIR)
	rm -rf libft/obj
	@echo "clean \033[1;32m[OK]\033[0m"

fclean:
	rm -rf $(CO_DIR)
	rm -rf $(AO_DIR)
	rm -rf libft/obj
	rm -rf $(LIBFT)
	rm -rf $(NAME_C)
	rm -rf $(NAME_A)
	@echo "clean \033[1;32m[OK]\033[0m"

re: fclean all

$(CO_DIR):
	mkdir $(CO_DIR)
	mkdir $(CO_DIR)/game
	mkdir $(CO_DIR)/statements

$(AO_DIR):
	mkdir $(AO_DIR)

$(LIBFT):
	make -C libft
