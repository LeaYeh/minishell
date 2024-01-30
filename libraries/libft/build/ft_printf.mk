# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    ft_printf.mk                                       :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/16 13:33:22 by ldulling          #+#    #+#              #
#    Updated: 2024/01/29 12:44:04 by ldulling         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


# ****************************** PREPARATION ********************************* #

# Gets this file's name (without suffix) for automatic variable creation later.
FILENAME	:=	$(basename $(notdir $(lastword $(MAKEFILE_LIST))))

# Resets TMP to get rid of any old values from other .mk files.
TMP			:=


# ***************************** CONFIGURATION ******************************** #

# Dependencies - has to be the basename of the corresponding .mk file:
DEPS	:=	libft

# Directory of source files in src/ directory:
DIR		:=	ft_printf/

# Source files:
#  ft_printf + ft_dprintf:
SUBDIR	:=	./
TMP		+=	$(addprefix $(DIR)$(SUBDIR), \
			ft_dprintf.c \
			ft_printf.c \
			parseandprint.c \
			print_char.c \
			print_nbr.c \
			print_parsed.c \
			print_ptr.c \
			print_str.c \
			set_format.c \
)

#  ft_snprintf:
SUBDIR	:=	ft_snprintf/
TMP		+=	$(addprefix $(DIR)$(SUBDIR), \
			ft_snprintf.c \
			get_max_size.c \
			parseandsprint.c \
			sprint_char.c \
			sprint_nbr.c \
			sprint_parsed.c \
			sprint_ptr.c \
			sprint_str.c \
			set_sformat.c \
)

# *************************** VARIABLE CREATION ****************************** #

# Creates a final SRC variable and assigns all the source files specified above.
$(eval SRC_$(FILENAME)		:=	$(TMP))

# Creates an OBJ variable for the dependency rule below.
$(eval OBJ_$(FILENAME)		:=	$(SRC_$(FILENAME):%.c=$O%.o))

# Makes this file's object files dependent on any DEPS specified above.
$(OBJ_$(FILENAME)):	$O%.o	:	$(foreach dep,$(DEPS),$(OBJ_$(dep)))


# *************************** MAKEFILE DEBUGGING ***************************** #

# Prints the values of the variable given after the minus.
print-%	:
	@		echo $* = $($*)
