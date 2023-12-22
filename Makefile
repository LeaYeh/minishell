NAME 		:= minishell
INCLUDES 	:= -I./include -I./libraries/libft/inc
LIBFT 		:= ./libraries/libft
LIBFT_LIB 	:= libft.a

B			:= build/
O			:= $B_obj/
D			:= $B_dep/

CC 			:= cc
CFLAGS 		:= -Wall -Wextra -Werror -g
MAKEFLAGS	:= -j$(nproc)

# TODO: need to remove forbidden wildcard
SRC 		:= $(wildcard source/*.c source/*/*.c source/*/*/*.c tests/*.c)
OBJ 		:= $(SRC:%.c=$O%.o)
DEP			:= $(SRC:%.c=$D%.d)

SUBDIRS_O	:= $(sort $(dir $(OBJ)))
SUBDIRS_D	:= $(sort $(dir $(DEP)))

all:		$(NAME)

$(NAME):	$(OBJ)
		$(MAKE) -C $(LIBFT)
		$(CC) $(CFLAGS) $(INCLUDES) $(OBJ) -L$(LIBFT) -lft -lreadline -o $(NAME)

$O%.o:		%.c | $(SUBDIRS_O)
		$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$D%.d:		%.c | $(SUBDIRS_D)
		$(CC) $(CFLAGS) $(INCLUDES) -M -MP -MF $@ -MT "$O$*.o $@" $<

$(SUBDIRS_O) $(SUBDIRS_D):
		mkdir -p $@

clean:
		$(MAKE) -C $(LIBFT) clean
		rm -f $(OBJ) $(DEP)
		-find $O $D -type d -empty -delete

fclean: 	clean
		$(MAKE) -C $(LIBFT) fclean
		rm -f $(NAME)

re:
		$(MAKE) fclean
		$(MAKE) all

.PHONY: all clean fclean re

ifeq (,$(filter clean fclean re,$(MAKECMDGOALS)))
    ifneq (,$(wildcard $O))
        -include	$(DEP)
    endif
endif

# test without env value:	env -i
# detect memory leak: 		valgrind -s --leak-check=full --show-leak-kinds=all --suppressions=./minishell.supp ./minishell
