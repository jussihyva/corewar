NAME = prog

SRC = main.c \
	utils.c \
	get.c \
	init.c \
	statements.c \
	statement_selection.c \
	cmds.c

S_DIR = src
O_DIR = obj
OBJ = $(addprefix $(O_DIR)/, $(SRC:.c=.o))
HEAD = test.h op.h
H_DIR = includes
GCC = gcc -Wall -Wextra -Werror
DEPS = $(patsubst %,$(H_DIR)/%,$(HEAD))

all: $(NAME)

$(NAME): $(OBJ) | $(LIBFT)
	@$(GCC) -o $@ $^ -I $(H_DIR)
	@echo  "test \033[1;32m[OK]\033[0m"

$(O_DIR)/%.o : $(S_DIR)/%.c $(DEPS)
	$(GCC) -o $@ -c $< -I $(H_DIR)

$(OBJ): | $(O_DIR)

clean:
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

$(O_DIR):
	mkdir $(O_DIR)
