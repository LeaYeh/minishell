NAME 		:= minishell
INCLUDES 	:= -I./include -I./libraries/libft/inc
LIBFT 		:= ./libraries/libft
LIBFT_LIB 	:= libft.a

BUILD_DIR	:= build/
OBJ_DIR		:= $(BUILD_DIR)_obj/
DEP_DIR		:= $(BUILD_DIR)_dep/

CC 			:= cc
CFLAGS 		:= -Wall -Wextra -Werror -g
MAKEFLAGS	:= -j$(nproc)

# TODO: need to remove forbidden wildcard
SRC 		:= $(wildcard source/*.c source/*/*.c source/*/*/*.c tests/*.c)
OBJ 		:= $(SRC:%.c=$(OBJ_DIR)%.o)
DEP			:= $(SRC:%.c=$(DEP_DIR)%.d)

OBJ_SUBDIRS	:= $(sort $(dir $(OBJ)))
DEP_SUBDIRS	:= $(sort $(dir $(DEP)))

all:		$(NAME)

$(NAME):	$(OBJ)
		$(MAKE) -C $(LIBFT)
		$(CC) $(CFLAGS) $(INCLUDES) $(OBJ) -L$(LIBFT) -lft -lreadline -o $(NAME)

$(OBJ_DIR)%.o:		%.c Makefile | $(OBJ_SUBDIRS)
		$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(DEP_DIR)%.d:		%.c Makefile | $(DEP_SUBDIRS)
		$(CC) $(CFLAGS) $(INCLUDES) -M -MP -MF $@ -MT "$(OBJ_DIR)$*.o $@" $<

$(OBJ_SUBDIRS) $(DEP_SUBDIRS):
		mkdir -p $@

clean:
		$(MAKE) -C $(LIBFT) clean
		rm -f $(OBJ) $(DEP)
		-find $(OBJ_DIR) $(DEP_DIR) -type d -empty -delete

fclean: 	clean
		$(MAKE) -C $(LIBFT) fclean
		rm -f $(NAME)

re:
		$(MAKE) fclean
		$(MAKE) all

.PHONY: all clean fclean re

ifeq (,$(filter clean fclean re,$(MAKECMDGOALS)))
    ifneq (,$(wildcard $(OBJ_DIR)))
        -include	$(DEP)
    endif
endif

# Makefile debugging
print-%:
	@	echo $* = $($*)

# test without env value:	env -i
# detect memory leak: 		valgrind -s --leak-check=full --show-leak-kinds=all --suppressions=./minishell.supp ./minishell
