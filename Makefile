NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror -g3
LDFLAGS = -lreadline
RM = rm -f
LIBFT = Libft/libft.a

SRC_DIR = src
SRC = $(SRC_DIR)/minishell.c $(SRC_DIR)/Parser.c $(SRC_DIR)/Lexer.c $(SRC_DIR)/helper_func.c $(SRC_DIR)/builtins.c $(SRC_DIR)/execution.c $(SRC_DIR)/dms_parser.c

OBJ_DIR = obj
OBJ = $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

all: $(NAME)

$(NAME): $(OBJ)
	@echo "\033[0;32mCompiling minishell..."
	@make -C Libft
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LIBFT) $(LDFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

clean:
	@make -C Libft clean
	@$(RM) $(OBJ)

fclean: clean
	@make -C Libft fclean
	@$(RM) $(NAME)
	@rmdir $(OBJ_DIR) 2> /dev/null || true

re: fclean all

.SECONDARY: $(OBJ)
.PHONY: all clean fclean re
