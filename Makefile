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
MAKEFLAGS	:=	-j -s

# TODO: need to remove forbidden wildcard
SRC 		:= $(wildcard source/*.c source/*/*.c source/*/*/*.c tests/*.c)
OBJ 		:= $(SRC:%.c=$(OBJ_DIR)/%.o)
DEP			:= $(SRC:%.c=$(DEP_DIR)/%.d)

OBJ_SUBDIRS	:= $(sort $(dir $(OBJ)))
DEP_SUBDIRS	:= $(sort $(dir $(DEP)))

export		MAKECMDGOALS
.PHONY:		all build lib clean fclean re

all:
		($(MAKE) --question build && echo -n $(MSG_NO_CHNG)) \
		|| (echo -n $(MSG_START) && ($(MAKE) build \
		&& echo -n $(MSG_SUCCESS)) || echo -n $(MSG_FAILURE))

ifeq ($(firstword $(sort $(MAKE_VERSION) 4.4)),4.4)
build:		lib .WAIT $(NAME)
else
.NOTPARALLEL:	lib
build:		lib $(NAME)
endif

lib:
		$(MAKE) -C $(LIBRARIES)

$(NAME):	$(LIBRARIES) $(OBJ)
		$(CC) $(CFLAGS) $(INCLUDES) $(OBJ) $(LIBFLAGS) -o $(NAME)

$(OBJ_DIR)/%.o:		%.c Makefile | $(OBJ_SUBDIRS)
		$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@ \
		&& echo -n $(MSG_PROGRESS)

$(DEP_DIR)/%.d:		%.c Makefile | $(DEP_SUBDIRS)
		$(CC) $(CFLAGS) $(INCLUDES) -M -MP -MF $@ -MT "$(OBJ_DIR)/$*.o $@" $<

$(OBJ_SUBDIRS) $(DEP_SUBDIRS):
		mkdir -p $@

clean:
		$(MAKE) -C $(LIBRARIES)
		rm -f $(OBJ) $(DEP)
ifneq (,$(wildcard $(OBJ_DIR)))
		-find $(OBJ_DIR) -type d -empty -delete
endif
ifneq (,$(wildcard $(DEP_DIR)))
		-find $(DEP_DIR) -type d -empty -delete
endif

fclean: 	clean
		$(MAKE) -C $(LIBRARIES)
		rm -f $(NAME)

re:
		$(MAKE) fclean
		$(MAKE) all

ifeq (,$(filter clean fclean re,$(MAKECMDGOALS)))
    ifneq (,$(wildcard $(OBJ_DIR)))
        -include	$(DEP)
    endif
endif

# Custom messages
MSG_START	:= "\033[3mBuilding \033[1;34mCrash \033[0m"
MSG_PROGRESS:= "\033[3m🌊\033[0m"
MSG_SUCCESS	:= "\033[1;3;36m\nDONE!\n\033[0m"
MSG_NO_CHNG	:= "\033[3;37mEverything up-to-date!\n\033[0m"
MSG_FAILURE	:= "\033[1;3;31mBUILD FAILED!\n\033[0m"

# Makefile debugging
print-%:
		echo $* = $($*)

# test without env value:	env -i
# detect memory leak: 		valgrind -s --leak-check=full --show-leak-kinds=all --suppressions=./minishell.supp ./minishell
