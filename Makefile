NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror -g3
LDFLAGS = -lreadline
RM = rm -f
LIBFT = Libft/libft.a

SRC = minishell.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	make -C Libft
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LIBFT) $(LDFLAGS)

clean:
	make -C Libft clean
	$(RM) $(OBJ)

fclean: clean
	make -C Libft fclean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
