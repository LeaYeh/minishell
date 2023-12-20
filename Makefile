NAME 		:= minishell
INCLUDES 	:= -I./include -I./libraries/libft/inc
LIBFT 		:= ./libraries/libft
LIBFT_LIB 	:= libft.a

CC 			:= cc
CFLAGS 		:= -Wall -Wextra -Werror -g

# TODO: need to remove forbidden wildcard
SRC 		= $(wildcard source/*.c source/*/*.c source/*/*/*.c tests/*.c)
OBJ 		= $(SRC:.c=.o)

all:		$(NAME)

$(NAME):	$(OBJ)
		$(MAKE) -C $(LIBFT)
		$(CC) $(CFLAGS) $(INCLUDES) $(OBJ) -L$(LIBFT) -lft -lreadline -o $(NAME)

%.o: %.c
		$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
		$(MAKE) -C $(LIBFT) clean
		rm -f $(OBJ)

fclean: 	clean
		$(MAKE) -C $(LIBFT) fclean
		rm -f $(NAME)

re: 	fclean all

.PHONY: all clean fclean re

# test without env value:	env -i
# detect memory leak: 		valgrind -s --leak-check=full --show-leak-kinds=all --suppressions=./minishell.supp ./minishell
