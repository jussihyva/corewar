NAME = prog

SRC = \
	main.c \
	init.c parse_av.c champ_init.c read_to.c \
	wm_init.c carriage.c \
	game/run_game.c game/game_utils.c op.c \
	statements/op_live.c statements/op_ld.c statements/op_st.c statements/op_add.c \
	statements/op_sub.c statements/op_and.c statements/op_or.c statements/op_xor.c \
	statements/op_zjmp.c statements/op_ldi.c statements/op_sti.c statements/op_fork.c \
	statements/op_lld.c statements/op_lldi.c statements/op_lfork.c statements/op_aff.c \
	free.c

S_DIR = src
O_DIR = obj
OBJ = $(addprefix $(O_DIR)/, $(SRC:.c=.o))
HEAD = test.h op.h struct.h
H_DIR = includes
LIBFT = libft/libft.a
GCC = gcc -Wall -Wextra -Werror
DEPS = $(patsubst %,$(H_DIR)/%,$(HEAD))

all: $(NAME)

$(NAME): $(OBJ) | $(LIBFT)
	@$(GCC) -o $@ $^ -I $(H_DIR) $(LIBFT)
	@echo  "prog \033[1;32m[OK]\033[0m"

$(O_DIR)/%.o : $(S_DIR)/%.c $(DEPS)
	$(GCC) -o $@ -c $< -I $(H_DIR)

$(OBJ): | $(O_DIR)

clean:
	@rm -rf $(O_DIR)
	@rm -rf libft/$(O_DIR)
	@echo "clean \033[1;32m[OK]\033[0m"

fclean:
	@rm -rf $(O_DIR)
	@rm -rf $(NAME)
	@rm -rf libft/$(O_DIR)
	@rm -rf $(LIBFT)
	@echo "fclean \033[1;32m[OK]\033[0m"

del:
	rm -rf *.cor
	@echo "cor_del \033[1;32m[OK]\033[0m"

re: fclean all

$(LIBFT):
	@make -C libft

$(O_DIR):
	mkdir $(O_DIR)
	mkdir $(O_DIR)/game
	mkdir $(O_DIR)/statements
