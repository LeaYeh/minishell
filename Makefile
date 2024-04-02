# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/23 03:22:46 by ldulling          #+#    #+#              #
#    Updated: 2024/04/02 17:20:11 by ldulling         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


# ***************************** CONFIGURATION ******************************** #

#	Executable

NAME 			:=	minishell


#	Directories

SRC_DIR			:=	source
BUILD_DIR		:=	build
OBJ_DIR			:=	$(BUILD_DIR)/_obj
DEP_DIR			:=	$(BUILD_DIR)/_dep
LIB_DIR			:=	libraries


#	Dependencies

LIBRARIES		:=	$(wildcard $(LIB_DIR)/*)
LIBRARIES_EXT	:=	readline termcap
INCLUDES 		:=	-I./include -I./$(LIBRARIES)/inc
BUILDFILES		:=	Makefile \
					$(BUILD_DIR)/parsing_table.mk \
					$(BUILD_DIR)/source_files.mk \
					$(BUILD_DIR)/welcome_art.mk


#	Flags

CC 				:=	cc
CFLAGS 			:=	-Wall -Wextra -Werror -g
LIBFLAGS		:=	$(addprefix -L,$(LIBRARIES)) \
					$(addprefix -l,$(patsubst lib%,%,$(notdir \
					$(LIBRARIES) $(LIBRARIES_EXT))))
MAKEFLAGS		:=	-j -s


#	Macro definitions

include				$(BUILD_DIR)/parsing_table.mk $(BUILD_DIR)/welcome_art.mk
MACROS			:=	-D PARSING_TABLE=$(PARSING_TABLE) \
					-D WELCOME_ART=$(WELCOME_ART1)


#	Characters

COMMA			:=	,
SPACE			:=	$() $()


#	Valgrind

VALGRIND		:=	$(shell which valgrind)

VALGRINDFLAGS	=	--errors-for-leak-kinds=all \
					--leak-check=full \
					--read-var-info=yes \
					--show-error-list=yes \
					--show-leak-kinds=all \
					--suppressions=./minishell.supp \
					--trace-children=yes \
					--trace-children-skip=$(subst $(SPACE),$(COMMA),$(ABSOLUTE_PATHS)) \
					--track-origins=yes

VALGRINDFDFLAGS	:=	--track-fds=all

VALGRINDIGNORE	:=	norminette

ABSOLUTE_PATHS	:=	/bin/* \
					/usr/bin/* \
					/usr/sbin/* \
					$(shell which -a $(VALGRINDIGNORE))


#	Terminal

TERMINAL		:=	$(shell which gnome-terminal 2> /dev/null)

ifeq ($(filter val,$(MAKECMDGOALS)),val)
TERMINALTITLE	:=	valgrind $(NAME)
else ifeq ($(filter valfd,$(MAKECMDGOALS)),valfd)
TERMINALTITLE	:=	valgrind-fd $(NAME)
else
TERMINALTITLE	:=	$(NAME)
endif

TERMINALFLAGS	:=	--title="$(TERMINALTITLE)" -- /bin/sh -c


#	Files

include				$(BUILD_DIR)/source_files.mk
SRC				:=	$(addprefix $(SRC_DIR)/,$(SRC))
OBJ 			:=	$(SRC:%.c=$(OBJ_DIR)/%.o)
DEP				:=	$(SRC:%.c=$(DEP_DIR)/%.d)


#	Subdirectories

OBJ_SUBDIRS		:=	$(sort $(dir $(OBJ)))
DEP_SUBDIRS		:=	$(sort $(dir $(DEP)))


# ***************************** BUILD PROCESS ******************************** #

.PHONY			:	all test run val noenv valfd build lib clean fclean ffclean \
					re


#	Compilation

all				:
					($(MAKE) --question build && echo $(MSG_NO_CHNG)) \
						|| (echo -n $(MSG_INFO)$(MSG_START) \
							&& ($(MAKE) build && echo $(MSG_SUCCESS)) \
							|| (echo $(MSG_FAILURE) && exit 42))

run				:	all
					"./$(NAME)"

val				:	all
					$(VALGRIND) $(VALGRINDFLAGS) "./$(NAME)"

noenv			:	all
					env -i $(VALGRIND) $(VALGRINDFLAGS) "./$(NAME)"

valfd			:	all
ifneq ($(TERMINAL),)
					$(TERMINAL) $(TERMINALFLAGS) \
					"bash --posix -c 'trap \"\" SIGINT ; \
					$(VALGRIND) $(VALGRINDFLAGS) $(VALGRINDFDFLAGS) ./$(NAME) ; \
					exec bash --posix'"
else
					$(VALGRIND) $(VALGRINDFLAGS) $(VALGRINDFDFLAGS) "./$(NAME)"
endif


#	Version check for Make

ifeq ($(firstword $(sort $(MAKE_VERSION) 4.4)),4.4)
MSG_INFO		=	$(MSG_MAKE_V4.4+)
build			:	lib .WAIT $(NAME)
else
MSG_INFO		=	$(MSG_MAKE_V4.3-)
.NOTPARALLEL	:	lib
build			:	lib $(NAME)
endif


#	Library compilation

export				MAKECMDGOALS

lib				:
					$(MAKE) -C $(LIBRARIES)


#	Executable linking

$(NAME)			:	$(LIBRARIES) $(OBJ)
					$(CC) $(CFLAGS) $(INCLUDES) $(OBJ) $(LIBFLAGS) -o $(NAME)


#	Source file compiling

$(OBJ_DIR)/%.o	:	%.c $(BUILDFILES) | $(OBJ_SUBDIRS)
					$(CC) $(CFLAGS) $(MACROS) $(INCLUDES) -c $< -o $@ \
						&& echo -n $(MSG_PROGRESS)


#	Pre-processing and dependency file creation

$(DEP_DIR)/%.d	:	%.c $(BUILDFILES) | $(DEP_SUBDIRS)
					$(CC) $(CFLAGS) $(MACROS) $(INCLUDES) \
						-M -MP -MF $@ -MT "$(OBJ_DIR)/$*.o $@" $<


#	Mirror directory structure for build artifacts

$(OBJ_SUBDIRS) \
$(DEP_SUBDIRS)	:
					mkdir -p $@


#	Cleaning

clean			:
					$(MAKE) clean -C $(LIBRARIES)
					rm -f $(OBJ) $(DEP)
ifneq (,$(wildcard $(OBJ_DIR)))
					-find $(OBJ_DIR) -type d -empty -delete
endif
ifneq (,$(wildcard $(DEP_DIR)))
					-find $(DEP_DIR) -type d -empty -delete
endif

fclean			:	clean
					$(MAKE) fclean -C $(LIBRARIES)
					rm -f $(NAME)

ffclean			:	fclean
					rm -rf $(OBJ_DIR) $(DEP_DIR)

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

################################################################################
MSG_MAKE_V4.4+	:=	"\e[3;37m Make version 4.4+ detected\n\
					Make version: $(MAKE_VERSION)\n\
					Parallel build for libraries enabled\n\e[0m"
################################################################################
MSG_MAKE_V4.3-	:=	"\e[3;37m Make version 4.4+ not detected\n\
					Make version: $(MAKE_VERSION)\n\
					Parallel build for libraries disabled\n\e[0m"
################################################################################
MSG_START		:=	"\e[3mBuilding Crash ... \e[0m"
################################################################################
MSG_PROGRESS	:=	"\e[3m🌊\e[0m"
################################################################################
MSG_SUCCESS		:=	"\e[1;3;36m\nDONE!\e[0m"
################################################################################
MSG_NO_CHNG		:=	"\e[3;37mEverything up-to-date!\e[0m"
################################################################################
MSG_FAILURE		:=	"\e[1;3;31mBUILD FAILED!\e[0m"
################################################################################


# *************************** MAKEFILE DEBUGGING ***************************** #

#	Execute "make print-[variable name]" to list the variable's values

print-%			:
					echo $* = $($*)


# ********************************* NOTES ************************************ #

#	test without env value:
#	env -i

#	PATH_MAX (4096 characters):
#	255------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------/510------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------/765------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------/1020-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------/1275-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------/1530-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------/1785-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------/2040-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------/2295-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------/2550-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------/2805-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------/3060-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------/3315-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------/3570-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------/3825-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------/4080-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------/
