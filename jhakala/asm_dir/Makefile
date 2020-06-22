NAME = asm

SRC = \
	op.c \
	main.c \
	init.c \
	is.c \
	skip.c \
	rev.c \
	get_head.c \
	get_lines.c \
	parse_cmd.c \
	parse_utils.c \
	check_champ.c \
	check_name.c \
	write.c

S_DIR = src
O_DIR = obj
OBJ = $(addprefix $(O_DIR)/, $(SRC:.c=.o))
HEAD = asm.h op.h error.h
H_DIR = includes
LIBFT = libft/libft.a
GCC = gcc -Wall -Wextra -Werror
DEPS = $(patsubst %,$(H_DIR)/%,$(HEAD))

all: $(NAME)

$(NAME): $(OBJ) | $(LIBFT)
	@$(GCC) -o $@ $^ -I $(H_DIR) $(LIBFT)
	@echo  "asm \033[1;32m[OK]\033[0m"

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
