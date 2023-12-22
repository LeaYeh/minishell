NAME 		:= minishell

BUILD_DIR	:= build
OBJ_DIR		:= $(BUILD_DIR)/_obj
DEP_DIR		:= $(BUILD_DIR)/_dep
LIB_DIR		:= libraries

LIBRARIES		:= $(wildcard $(LIB_DIR)/*)
LIBRARIES_EXT	:= readline
INCLUDES 		:= -I./include -I./$(LIBRARIES)/inc

CC 			:=	cc
CFLAGS 		:=	-Wall -Wextra -Werror -g
LIBFLAGS	:=	$(addprefix -L,$(LIBRARIES)) \
				$(addprefix -l,$(patsubst lib%,%,$(notdir \
				$(LIBRARIES) $(LIBRARIES_EXT))))
MAKEFLAGS	:=	-j$(nproc)

# TODO: need to remove forbidden wildcard
SRC 		:= $(wildcard source/*.c source/*/*.c source/*/*/*.c tests/*.c)
OBJ 		:= $(SRC:%.c=$(OBJ_DIR)/%.o)
DEP			:= $(SRC:%.c=$(DEP_DIR)/%.d)

OBJ_SUBDIRS	:= $(sort $(dir $(OBJ)))
DEP_SUBDIRS	:= $(sort $(dir $(DEP)))

export 		MAKECMDGOALS
.PHONY:		all lib clean fclean re

all:		lib $(NAME)

lib:
		$(MAKE) -C $(LIBRARIES)

$(NAME):	$(LIBRARIES) $(OBJ)
		$(CC) $(CFLAGS) $(INCLUDES) $(OBJ) $(LIBFLAGS) -o $(NAME)

$(OBJ_DIR)/%.o:		%.c Makefile | $(OBJ_SUBDIRS)
		$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(DEP_DIR)/%.d:		%.c Makefile | $(DEP_SUBDIRS)
		$(CC) $(CFLAGS) $(INCLUDES) -M -MP -MF $@ -MT "$(OBJ_DIR)/$*.o $@" $<

$(OBJ_SUBDIRS) $(DEP_SUBDIRS):
		mkdir -p $@

clean:
		$(MAKE) -C $(LIBRARIES) clean
		rm -f $(OBJ) $(DEP)
		-find $(OBJ_DIR) $(DEP_DIR) -type d -empty -delete

fclean: 	clean
		$(MAKE) -C $(LIBRARIES) fclean
		rm -f $(NAME)

re:
		$(MAKE) fclean
		$(MAKE) all

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
