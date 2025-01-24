# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/23 03:22:46 by ldulling          #+#    #+#              #
#    Updated: 2025/01/24 23:34:49 by ldulling         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


# ***************************** CONFIGURATION ******************************** #

#	Executable

NAME 			:=	minishell
MAKE_NAME		:=	Crash


#	Directories

SRC_DIR			:=	source
INC_DIR			:=	include
BUILD_DIR		:=	build
OBJ_DIR			:=	$(BUILD_DIR)/_obj
DEP_DIR			:=	$(BUILD_DIR)/_dep
LIB_DIR			:=	libraries


#	Dependencies

LIBRARIES		:=	$(LIB_DIR)/libft
LIBRARIES_EXT	:=	readline termcap
LIB_INCLUDES 	:=	$(LIB_DIR)/libft/inc
BUILDFILES		:=	Makefile \
					$(BUILD_DIR)/parsing_table.mk \
					$(BUILD_DIR)/source_files.mk \
					$(BUILD_DIR)/welcome_art.mk


#	Flags

CC				?=	cc
CC_VERSION		:=	$(shell $(CC) --version | head -1)
CFLAGS_STD		:=	-Wall -Wextra -Werror
CFLAGS_DBG		:=	-ggdb3
CFLAGS_SAN		:=	-fsanitize=address,undefined,bounds,float-divide-by-zero
CFLAGS_OPT		:=	-O3
CFLAGS			?=	$(CFLAGS_STD) $(CFLAGS_DBG)
CPPFLAGS		:=	$(addprefix -I,$(INC_DIR) $(LIB_INCLUDES))
DEPFLAGS		=	-M -MP -MF $@ -MT "$(OBJ_DIR)/$*.o $@"
LDFLAGS			:=	$(addprefix -L,$(LIBRARIES))
LDLIBS			:=	$(addprefix -l,$(patsubst lib%,%,$(notdir $(LIBRARIES) $(LIBRARIES_EXT))))
MAKEFLAGS		+=	-j -s


#	Macro definitions

include				$(BUILD_DIR)/parsing_table.mk $(BUILD_DIR)/welcome_art.mk
CPPFLAGS		+=	-D PARSING_TABLE=$(PARSING_TABLE) \
					-D WELCOME_ART1=$(WELCOME_ART1) \
					-D WELCOME_ART2=$(WELCOME_ART2)


#	Characters

COMMA			:=	,
SPACE			:=	$() $()


#	Valgrind

VALGRIND		:=	$(shell which valgrind)

VALGRINDFLAGS	=	--errors-for-leak-kinds=all \
					--leak-check=full \
					--show-error-list=yes \
					--show-leak-kinds=all \
					--suppressions=$(CURDIR)/minishell.supp \
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

TERMINAL		:=	$(shell which gnome-terminal 2>/dev/null)

ifeq (val, $(filter val,$(MAKECMDGOALS)))
TERMINALTITLE	:=	valgrind $(MAKE_NAME)
else ifeq (valfd, $(filter valfd,$(MAKECMDGOALS)))
TERMINALTITLE	:=	valgrind-fd $(MAKE_NAME)
else
TERMINALTITLE	:=	$(MAKE_NAME)
endif

TERMINALFLAGS	:=	--title="$(TERMINALTITLE)" --


#	Files

include				$(BUILD_DIR)/source_files.mk
SRC_EXTENSION	:=	.c
OBJ				:=	$(SRC:%$(SRC_EXTENSION)=$(OBJ_DIR)/%.o)
DEP				:=	$(SRC:%$(SRC_EXTENSION)=$(DEP_DIR)/%.d)


#	Subdirectories

OBJ_SUBDIRS		:=	$(sort $(dir $(OBJ)))
DEP_SUBDIRS		:=	$(sort $(dir $(DEP)))


# *************************** BUILD PREPARATION ****************************** #

export				CC CFLAGS MAKECMDGOALS MAKEFLAGS

SHELL			:=	/bin/bash

PHONY_TARGETS	:=	all run noenv nocolor opt san val valfd term clear modes re \
					build lib waitforlib clean fclean ffclean
ENV_VARIABLES	:=	MODE
HELP_TARGETS	:=	help help-print \
					$(addprefix help-,$(PHONY_TARGETS) $(ENV_VARIABLES)) \
					$(addsuffix -help,$(PHONY_TARGETS) $(ENV_VARIABLES))
PHONY_TARGETS	+=	$(HELP_TARGETS)
export .PHONY	:	$(PHONY_TARGETS)

REBUILD_TARGETS	:=	nocolor opt san re
CLEAN_TARGETS	:=	clean fclean ffclean

.DEFAULT		:
					$(MAKE) help

.DEFAULT_GOAL	:=	all


# ********************************* MODES ************************************ #

ENV				:=

ifeq (run, $(filter run,$(MAKECMDGOALS) $(MODE)))
RUN				:=	true
endif

ifeq (noenv, $(filter noenv,$(MAKECMDGOALS) $(MODE)))
ENV				+=	env -i
RUN				:=	true
endif

ifeq (nocolor, $(filter nocolor,$(MAKECMDGOALS) $(MODE)))
CPPFLAGS		+=	-D NO_COLOR=1
RECOMPILE		:=	true
endif

ifeq (opt, $(filter opt,$(MAKECMDGOALS) $(MODE)))
CFLAGS			:=	$(CFLAGS_STD) $(CFLAGS_OPT)
RECOMPILE		:=	true
endif

ifeq (san, $(filter san,$(MAKECMDGOALS) $(MODE)))
CFLAGS			+=	$(CFLAGS_STD) $(CFLAGS_DBG) $(CFLAGS_SAN)
RECOMPILE		:=	true
endif

ifeq (val, $(filter val,$(MAKECMDGOALS) $(MODE)))
ENV				+=	$(VALGRIND) $(VALGRINDFLAGS)
PATH			:=	/bin:/usr/bin:/usr/sbin:$(PATH)
RUN				:=	true
endif

ifeq (valfd, $(filter valfd,$(MAKECMDGOALS) $(MODE)))
ENV				+=	$(VALGRIND) $(VALGRINDFLAGS) $(VALGRINDFDFLAGS)
PATH			:=	/bin:/usr/bin:/usr/sbin:$(PATH)
NEW_TERM		:=	true
RUN				:=	true
endif

ifeq (term, $(filter term,$(MAKECMDGOALS) $(MODE)))
NEW_TERM		:=	true
RUN				:=	true
endif

ifeq (clear, $(filter clear,$(MAKECMDGOALS) $(MODE)))
CLEAR			:=	true
endif


# ***************************** BUILD TARGETS ******************************** #

all				:
					if $(MAKE) --question build; then \
						echo -e -n $(MSG_NO_CHANGE); \
						echo -e -n $(MSG_HELP); \
					else \
						echo -e -n $(MSG_MODE); \
						echo -e -n " "$(MSG_INFO); \
						echo -e -n " "$(MSG_HELP); \
						echo -e -n $(MSG_START); \
						if $(MAKE) build; then \
							echo; \
							echo -e -n $(MSG_SUCCESS); \
						else \
							echo; \
							echo -e -n $(MSG_FAILURE); \
							exit 42; \
						fi; \
					fi

run noenv nocolor opt san val valfd term clear: modes

modes			:
					if [ "$(RECOMPILE)" = "true" ]; then \
						MAKELEVEL=$$(( $(MAKELEVEL) - 1 )) MSG_SUCCESS="" $(MAKE) re; \
						MAKELEVEL=$$(( $(MAKELEVEL) - 1 )) $(MAKE) clean; \
					else \
						MAKELEVEL=$$(( $(MAKELEVEL) - 1 )) $(MAKE) all; \
					fi
					if [ "$(CLEAR)" = "true" ]; then \
						clear; \
					fi
					if [ "$(NEW_TERM)" = "true" ] && [ -n "$(TERMINAL)" ]; then \
						$(TERMINAL) $(TERMINALFLAGS) bash --posix -c \
							"trap '' SIGINT; \
							$(ENV) ./$(NAME); \
							exec bash --posix"; \
					elif [ "$(RUN)" = "true" ]; then \
						$(ENV) "./$(NAME)"; \
					fi

re				:
					$(MAKE) fclean
					MAKELEVEL=$$(( $(MAKELEVEL) - 1 )) $(MAKE) all


# ***************************** BUILD PROCESS ******************************** #

#	Dependency files inclusion

ifeq (, $(filter $(HELP_TARGETS) $(REBUILD_TARGETS) $(CLEAN_TARGETS),$(MAKECMDGOALS)))
    ifneq (, $(wildcard $(OBJ_DIR)))
        -include	$(DEP)
    endif
endif


#	Library dependency management

ifeq (4.4, $(firstword $(sort $(MAKE_VERSION) 4.4)))
build			:	lib .WAIT $(NAME)
else
build			:	waitforlib
					$(MAKE) $(NAME)
endif


#	Library compilation

lib				:
					$(MAKE) -C $(LIBRARIES)

waitforlib		:	lib


#	Executable linkage

$(NAME)			:	$(LIBRARIES) $(OBJ)
					$(CC) $(CFLAGS) $(LDFLAGS) $(OBJ) $(LDLIBS) -o $(NAME)


#	Source file compilation

$(OBJ_DIR)/%.o	:	$(SRC_DIR)/%$(SRC_EXTENSION) $(BUILDFILES) | $(OBJ_SUBDIRS)
					$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@ \
						&& echo -e -n $(MSG_PROGRESS)


#	Pre-processing and dependency file creation

$(DEP_DIR)/%.d	:	$(SRC_DIR)/%$(SRC_EXTENSION) $(BUILDFILES) | $(DEP_SUBDIRS)
					$(CC) $(CPPFLAGS) $(DEPFLAGS) $(CFLAGS) $<


#	Directory structure mirroring of source files for build artifacts

$(OBJ_SUBDIRS) \
$(DEP_SUBDIRS)	:
					mkdir -p $@


# ***************************** CLEAN TARGETS ******************************** #

clean			:
					echo -e -n $(MSG_CLEAN)
					$(MAKE) clean -C $(LIBRARIES)
					rm -f $(OBJ) $(DEP)
                    ifneq (, $(wildcard $(OBJ_DIR)))
						-find $(OBJ_DIR) -type d -empty -delete
                    endif
                    ifneq (, $(wildcard $(DEP_DIR)))
						-find $(DEP_DIR) -type d -empty -delete
                    endif
					echo -e -n $(MSG_SUCCESS)

fclean			:
					echo -e -n $(MSG_FCLEAN)
					$(MAKE) clean
					$(MAKE) fclean -C $(LIBRARIES)
					rm -f $(NAME)
					echo -e -n $(MSG_SUCCESS)

ffclean			:
					echo -e -n $(MSG_FFCLEAN)
					$(MAKE) fclean
					rm -rf $(OBJ_DIR) $(DEP_DIR)
					echo -e -n $(MSG_SUCCESS)


# ****************************** HELP TARGETS ******************************** #

help			:
					echo -e "Targets:"
					echo -e "  all              Build the project (default target)"
					echo -e "  run              Build and run the project"
					echo -e "  noenv            Build and run the project with an empty environment"
					echo -e "  nocolor          Rebuild the project without colors in the prompt and printouts"
					echo -e "  opt              Rebuild the project with optimizations"
					echo -e "  san              Rebuild the project with sanitizers"
					echo -e "  val              Build and run the project with valgrind"
					echo -e "  valfd            Build and run the project with valgrind and file descriptor tracking"
					echo -e "  term             Build and run the project in a new terminal window"
					echo -e "  clear            Build the project and clear the terminal"
					echo -e "  re               Rebuild the project"
					echo -e "  clean            Remove build artifacts"
					echo -e "  fclean           Remove build artifacts and executable"
					echo -e "  ffclean          Remove build artifacts and executable without checking for unknown files"
					echo -e "  print-%          Print the value of a Makefile variable (replace % with variable name)"
					echo -e "  help             Display this message"
					echo -e "  help-% | %-help  Display more information for a specific target (replace % with target name)"
					echo
					echo -e "Environment Variables:"
					echo -e "  MODE             Build mode to combine multiple targets"
					echo
					echo -e "Usage: make [\\$(STY_UND)target\\$(STY_RES)] [MODE=\"<\\$(STY_UND)mode1\\$(STY_RES)> [\\$(STY_UND)mode2\\$(STY_RES)] [...]\"]"

help-all		:
					echo -e "Build the project."
					echo -e "This is the default target when no target is specified."

help-run		:
					echo -e "Build the project and run the executable."

help-noenv		:
					echo -e "Build the project and run executable with an empty environment (env -i)."

help-nocolor	:
					echo -e "Rebuild the project without colors in the prompt and printouts."
					echo -e "Useful when ANSI escape sequences are not well supported in a terminal emulator."

help-opt		:
					echo -e "Rebuild the project with the following compiler optimization flags:"
					echo -e "  $(CFLAGS_OPT)"

help-san		:
					echo -e "Rebuild the project with the following sanitizer flags:"
					echo -e "  $(CFLAGS_SAN)"

help-val		:
					echo -e "Build the project and run the executable with valgrind."
					echo
					echo -e "The following valgrind flags are used:"
					echo -e "$(VALGRINDFLAGS)" | tr ' ' '\n' | sed 's/^/  /'

help-valfd		:
					echo -e "Build the project and run the executable with valgrind and file descriptor tracking."
					echo -e "A new terminal window is opened to avoid inheriting open file descriptors."
					echo
					echo -e "The following valgrind flags are used:"
					echo -e "$(VALGRINDFLAGS)" | tr ' ' '\n' | sed 's/^/  /'
					echo -e "File descriptor specific flags:"
					echo -e "$(VALGRINDFDFLAGS)" | tr ' ' '\n' | sed 's/^/  /'

help-term		:
					echo -e "Build the project and run the executable in a new terminal window."

help-clear		:
					echo -e "Build the project and clear the terminal."

help-re			:
					echo -e "Rebuild the project."

help-clean		:
					echo -e "Remove build artifacts."

help-fclean		:
					echo -e "Remove build artifacts and the executable."

help-ffclean	:
					echo -e "Remove build artifacts and the executable without checking for unknown files."

help-print		:
					echo -e "Print the value of a Makefile variable by appending the variable name to print-..."
					echo -e "Useful for Makefile debugging."
					echo
					echo -e "Usage: make print-<\\$(STY_UND)variable name\\$(STY_RES)>"

help-help		:
					echo -e "Display more information for a specific target by appending or prepending help."
					echo
					echo -e "Usage: make help-<\\$(STY_UND)target\\$(STY_RES)> | make <\\$(STY_UND)target\\$(STY_RES)>-help"

help-MODE MODE-help:
					echo -e "Build mode to combine with other targets."
					echo -e "Multiple modes can be combined by separating them with a space."
					echo
					echo -e "Usage: make <\\$(STY_UND)target\\$(STY_RES)> MODE=\"<\\$(STY_UND)mode1\\$(STY_RES)> [\\$(STY_UND)mode2\\$(STY_RES)] [...]\""

%-help:
					$(MAKE) help-$(subst -help,,$@)


# ********************************* COLORS *********************************** #

STY_RES			:=	"\e[0m"
STY_BOL			:=	"\e[1m"
STY_ITA			:=	"\e[3m"
STY_UND			:=	"\e[4m"
STY_RED			:=	"\e[31m"
STY_GRE			:=	"\e[32m"
STY_YEL			:=	"\e[33m"
STY_BLU			:=	"\e[34m"
STY_MAG			:=	"\e[35m"
STY_CYA			:=	"\e[36m"
STY_WHI			:=	"\e[37m"
STY_GRA			:=	"\e[90m"
STY_WHI_BRI		:=	"\e[97m"
STY_BLA_BG		:=	"\e[40m"
STY_RED_BG		:=	"\e[41m"
STY_GRE_BG		:=	"\e[42m"
STY_YEL_BG		:=	"\e[43m"
STY_BLU_BG		:=	"\e[44m"
STY_MAG_BG		:=	"\e[45m"
STY_CYA_BG		:=	"\e[46m"
STY_WHI_BG		:=	"\e[47m"
STY_GRA_BG		:=	"\e[100m"
STY_WHI_BRI_BG	:=	"\e[107m"


# **************************** CUSTOM MESSAGES ******************************* #

MSG_PROGRESS	:=	$(STY_ITA)"🌊"$(STY_RES)


########################## Top-level only messages #############################
ifeq (0, $(MAKELEVEL))

#	Make status messages

MSG_INFO		:=	$(STY_ITA)$(STY_WHI)"Make version: $(MAKE_VERSION)\n\
					Compiler version: $(CC_VERSION)"$(STY_RES)"\n"

MSG_HELP		:=	$(STY_ITA)$(STY_WHI)"Run 'make help' to see all available Makefile targets."$(STY_RES)"\n"

ifneq (, $(filter $(REBUILD_TARGETS),$(MAKECMDGOALS) $(MODE)))
MSG_START		:=	$(STY_ITA)"Rebuilding $(MAKE_NAME) ... "$(STY_RES)
else
MSG_START		:=	$(STY_ITA)"Building $(MAKE_NAME) ... "$(STY_RES)
endif

MSG_SUCCESS		?=	$(STY_BOL)$(STY_ITA)$(STY_CYA)"DONE!"$(STY_RES)"\n"

MSG_NO_CHANGE	:=	$(STY_ITA)$(STY_WHI)"Everything up-to-date!"$(STY_RES)"\n"

MSG_FAILURE		:=	$(STY_BOL)$(STY_ITA)$(STY_RED)"BUILD FAILED!"$(STY_RES)"\n"


#	Build modes

MSG_RUN			:=	$(STY_BOL)$(STY_ITA)$(STY_UND)$(STY_YEL)"~~~~~~~~~~~~~~~~~~~~~~~ RUN MODE ~~~~~~~~~~~~~~~~~~~~~~~"$(STY_RES)"\n"
ifneq (, $(filter run,$(MAKECMDGOALS) $(MODE)))
MSG_MODE		:=	$(MSG_MODE)$(MSG_RUN)
endif

MSG_NOENV		:=	$(STY_BOL)$(STY_ITA)$(STY_UND)$(STY_MAG)"~~~~~~~~~~~~~~~~ EMPTY ENVIRONMENT MODE ~~~~~~~~~~~~~~~~"$(STY_RES)"\n"
ifneq (, $(filter noenv,$(MAKECMDGOALS) $(MODE)))
MSG_MODE		:=	$(MSG_MODE)$(MSG_NOENV)
endif

MSG_NOCOLOR		:=	$(STY_BOL)$(STY_ITA)$(STY_UND)$(STY_WHI_BRI)"~~~~~~~~~~~~~~~~~~~~~ NO COLOR MODE ~~~~~~~~~~~~~~~~~~~~"$(STY_RES)"\n"
ifneq (, $(filter nocolor,$(MAKECMDGOALS) $(MODE)))
MSG_MODE		:=	$(MSG_MODE)$(MSG_NOCOLOR)
endif

MSG_OPT			:=	$(STY_BOL)$(STY_ITA)$(STY_UND)$(STY_GRE)"~~~~~~~~~~~~~~~~~~~ OPTIMIZATION MODE ~~~~~~~~~~~~~~~~~~"$(STY_RES)"\n"
ifneq (, $(filter opt,$(MAKECMDGOALS) $(MODE)))
MSG_MODE		:=	$(MSG_MODE)$(MSG_OPT)
endif

MSG_SAN			:=	$(STY_BOL)$(STY_ITA)$(STY_UND)$(STY_RED)"~~~~~~~~~~~~~~~~~~~~ SANITIZER MODE ~~~~~~~~~~~~~~~~~~~~"$(STY_RES)"\n"
ifneq (, $(filter san,$(MAKECMDGOALS) $(MODE)))
MSG_MODE		:=	$(MSG_MODE)$(MSG_SAN)
endif

MSG_VAL			:=	$(STY_BOL)$(STY_ITA)$(STY_UND)$(STY_BLU)"~~~~~~~~~~~~~~~~~~~~~ VALGRIND MODE ~~~~~~~~~~~~~~~~~~~~"$(STY_RES)"\n"
ifneq (, $(filter val,$(MAKECMDGOALS) $(MODE)))
MSG_MODE		:=	$(MSG_MODE)$(MSG_VAL)
endif

MSG_VALFD		:=	$(STY_BOL)$(STY_ITA)$(STY_UND)$(STY_CYA)"~~~~~~~~~~~~~~~~~~~ VALGRIND FD MODE ~~~~~~~~~~~~~~~~~~~"$(STY_RES)"\n"
ifneq (, $(filter valfd,$(MAKECMDGOALS) $(MODE)))
MSG_MODE		:=	$(MSG_MODE)$(MSG_VALFD)
endif

MSG_TERM		:=	$(STY_BOL)$(STY_ITA)$(STY_UND)$(STY_YEL)"~~~~~~~~~~~~~~~~~~~ NEW TERMINAL MODE ~~~~~~~~~~~~~~~~~~"$(STY_RES)"\n"
ifneq (, $(filter term,$(MAKECMDGOALS) $(MODE)))
MSG_MODE		:=	$(MSG_MODE)$(MSG_TERM)
endif

MSG_CLEAR		:=	$(STY_BOL)$(STY_ITA)$(STY_UND)$(STY_GRA)"~~~~~~~~~~~~~~~~~~~~~ CLEAR MODE ~~~~~~~~~~~~~~~~~~~~"$(STY_RES)"\n"
ifneq (, $(filter clear,$(MAKECMDGOALS) $(MODE)))
MSG_MODE		:=	$(MSG_MODE)$(MSG_CLEAR)
endif


#	Clean messages

MSG_CLEAN		:=	$(STY_ITA)"Cleaning up build artifacts ... "$(STY_RES)"\n"

MSG_FCLEAN		:=	$(STY_ITA)"Cleaning up build artifacts and executable ... "$(STY_RES)"\n"

MSG_FFCLEAN		:=	$(STY_ITA)"Forcefully cleaning up build artifacts directory and executable ... "$(STY_RES)"\n"

endif
################################################################################


# *************************** MAKEFILE DEBUGGING ***************************** #

print-%			:
					echo -e $* = $($*)


# ********************************* NOTES ************************************ #

#	PATH_MAX (4096 characters):
#	255------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------/510------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------/765------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------/1020-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------/1275-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------/1530-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------/1785-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------/2040-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------/2295-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------/2550-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------/2805-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------/3060-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------/3315-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------/3570-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------/3825-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------/4080-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------/
