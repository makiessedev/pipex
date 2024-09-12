NAME = pipex
CC = cc
C_FLAGS = -Wall -Werror -Wextra
RM = rm -rf
FILES = main.c pipex.c
LIBFT = ./libft/libft.a

$(NAME): $(FILES)
	make all -C ./libft
	$(CC) $(C_FLAGS) $(FILES) $(LIBFT) -o $(NAME)

all: $(NAME)

clean:
	$(RM) main.o pipex.o
	make clean -C ./libft

fclean: clean
	$(RM) $(NAME)
	make fclean -C ./libft

re: clean all

.PHONY: all clean fclean re
