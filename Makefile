# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/23 03:22:46 by ldulling          #+#    #+#              #
#    Updated: 2024/01/18 23:33:23 by ldulling         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


# ***************************** CONFIGURATION ******************************** #

#	Executable

NAME 			:=	minishell


#	Directories

BUILD_DIR		:=	build
OBJ_DIR			:=	$(BUILD_DIR)/_obj
DEP_DIR			:=	$(BUILD_DIR)/_dep
LIB_DIR			:=	libraries


#	Dependencies

LIBRARIES		:=	$(wildcard $(LIB_DIR)/*)
LIBRARIES_EXT	:=	readline
INCLUDES 		:=	-I./include -I./$(LIBRARIES)/inc


#	Flags

CC 				:=	cc
CFLAGS 			:=	-Wall -Wextra -Werror -g
ifeq ($(filter debug,$(MAKECMDGOALS)),debug)
CFLAGS			+=	-D DEBUG_MODE
endif
LIBFLAGS		:=	$(addprefix -L,$(LIBRARIES)) \
					$(addprefix -l,$(patsubst lib%,%,$(notdir \
					$(LIBRARIES) $(LIBRARIES_EXT))))
MAKEFLAGS		:=	-j -s


#	Files

# TODO: need to remove forbidden wildcard
SRC 			:=	$(wildcard source/*.c source/*/*.c source/*/*/*.c source/*/*/*/*.c tests/*.c)
OBJ 			:=	$(SRC:%.c=$(OBJ_DIR)/%.o)
DEP				:=	$(SRC:%.c=$(DEP_DIR)/%.d)


#	Subdirectories

OBJ_SUBDIRS		:=	$(sort $(dir $(OBJ)))
DEP_SUBDIRS		:=	$(sort $(dir $(DEP)))


# ***************************** BUILD PROCESS ******************************** #

.PHONY			:	all build lib clean fclean re debug


#	Compilation

all				:
					($(MAKE) --question build && echo -n $(MSG_NO_CHNG)) \
						|| (echo -n $(MSG_START) \
							&& ($(MAKE) build && echo -n $(MSG_SUCCESS)) \
							|| (echo -n $(MSG_FAILURE) && exit 42))

#		Version check for Make

ifeq ($(firstword $(sort $(MAKE_VERSION) 4.4)),4.4)
build			:	lib .WAIT $(NAME)
else
.NOTPARALLEL:		lib
build			:	lib $(NAME)
endif


#		Library compilation

export				MAKECMDGOALS

lib				:
					$(MAKE) -C $(LIBRARIES)


#		Executable linking

$(NAME)			:	$(LIBRARIES) $(OBJ)
					$(CC) $(CFLAGS) $(INCLUDES) $(OBJ) $(LIBFLAGS) -o $(NAME)


#		Source file compiling

$(OBJ_DIR)/%.o	:	%.c Makefile | $(OBJ_SUBDIRS)
					$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@ \
						&& echo -n $(MSG_PROGRESS)


#		Pre-processing and dependency file creation

$(DEP_DIR)/%.d	:	%.c Makefile | $(DEP_SUBDIRS)
					$(CC) $(CFLAGS) $(INCLUDES) \
						-M -MP -MF $@ -MT "$(OBJ_DIR)/$*.o $@" $<


#		Mirror directory structure for build artifacts

$(OBJ_SUBDIRS) \
$(DEP_SUBDIRS)	:
					mkdir -p $@


#	Cleaning

clean:
					$(MAKE) -C $(LIBRARIES)
					rm -f $(OBJ) $(DEP)
ifneq (,$(wildcard $(OBJ_DIR)))
					-find $(OBJ_DIR) -type d -empty -delete
endif
ifneq (,$(wildcard $(DEP_DIR)))
					-find $(DEP_DIR) -type d -empty -delete
endif

fclean			:	clean
					$(MAKE) -C $(LIBRARIES)
					rm -f $(NAME)

re				:
					$(MAKE) fclean
					$(MAKE) all


#	Include dependency files

ifeq (,$(filter clean fclean re,$(MAKECMDGOALS)))
    ifneq (,$(wildcard $(OBJ_DIR)))
        -include	$(DEP)
    endif
endif


# **************************** CUSTOM MESSAGES ******************************* #

MSG_START		:=	"\e[3mBuilding \e[1;34m🌊rash \e[0;3m... \e[0m"
MSG_PROGRESS	:=	"\e[3m🌊\e[0m"
MSG_SUCCESS		:=	"\e[1;3;36m\nDONE!\n\e[0m"
MSG_NO_CHNG		:=	"\e[3;37mEverything up-to-date!\n\e[0m"
MSG_FAILURE		:=	"\e[1;3;31mBUILD FAILED!\n\e[0m"


# *************************** MAKEFILE DEBUGGING ***************************** #

#	Execute "make print-[variable name]" to list the variable's values

print-%			:
					echo $* = $($*)


# ********************************* NOTES ************************************ #

# test without env value:	env -i
# detect memory leak: 		valgrind -s --leak-check=full --show-leak-kinds=all --suppressions=./minishell.supp ./minishell
# valgrind -s --leak-check=full --show-leak-kinds=all --track-fds=yes --trace-children=yes --suppressions=./minishell.supp ./minishell
