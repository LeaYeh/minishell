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
MAKEFLAGS	:=	-j

# TODO: need to remove forbidden wildcard
SRC 		:= $(wildcard source/*.c source/*/*.c source/*/*/*.c tests/*.c)
OBJ 		:= $(SRC:%.c=$(OBJ_DIR)/%.o)
DEP			:= $(SRC:%.c=$(DEP_DIR)/%.d)

OBJ_SUBDIRS	:= $(sort $(dir $(OBJ)))
DEP_SUBDIRS	:= $(sort $(dir $(DEP)))

export 		MAKECMDGOALS
.PHONY:		all lib clean fclean re

# Needs GNU Make version 4.4
# all:		lib .WAIT $(NAME)	(Replaces .NOTPARALLEL special target)
.NOTPARALLEL:	lib	# temporary until update to version 4.4

all:		lib $(NAME)

lib:
	@	$(MAKE) -C $(LIBRARIES) --no-print-directory

$(NAME):	$(LIBRARIES) $(OBJ)
		$(CC) $(CFLAGS) $(INCLUDES) $(OBJ) $(LIBFLAGS) -o $(NAME)

$(OBJ_DIR)/%.o:		%.c Makefile | $(OBJ_SUBDIRS)
		$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(DEP_DIR)/%.d:		%.c Makefile | $(DEP_SUBDIRS)
	@	$(CC) $(CFLAGS) $(INCLUDES) -M -MP -MF $@ -MT "$(OBJ_DIR)/$*.o $@" $<

$(OBJ_SUBDIRS) $(DEP_SUBDIRS):
	@	mkdir -p $@

clean:
		$(MAKE) -C $(LIBRARIES) clean
		rm -f $(OBJ) $(DEP)
ifneq (,$(wildcard $(OBJ_DIR)))
		-find $(OBJ_DIR) -type d -empty -delete
endif
ifneq (,$(wildcard $(DEP_DIR)))
		-find $(DEP_DIR) -type d -empty -delete
endif

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
