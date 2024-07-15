NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror -g3
LDFLAGS = -lreadline
RM = rm -f
LIBFT = Libft/libft.a

SRC = minishell.c Parser.c Lexer.c helper_func.c builtins.c #dms_parser.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	@echo "\033[0;32mCompiling minishell..."
	@make -C Libft
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LIBFT) $(LDFLAGS)


%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@make -C Libft clean
	@$(RM) $(OBJ)

fclean: clean
	@make -C Libft fclean
	@$(RM) $(NAME)

re: fclean all

.SECONDARY: $(OBJ)
.PHONY: all clean fclean re
