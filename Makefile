NAME = pipex
CC = cc
C_FLAGS = -Wall -Werror -Wextra -fsanitize=address
RM = rm -rf
FILES = main.c pipex.c ./libft/libft.a

$(NAME):
	make all -C ./libft
	$(CC) $(C_FLAGS) $(FILES) -o $(NAME)

all: $(NAME)

clean:
	$(RM) $(NAME)
	make clean -C ./libft

fclean: clean
	make fclean -C ./libft

re: fclean all

.PHONY: all clean fclean re
