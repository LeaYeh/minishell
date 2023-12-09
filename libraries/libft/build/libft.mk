# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    libft.mk                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/16 13:33:38 by ldulling          #+#    #+#              #
#    Updated: 2023/12/07 03:12:53 by ldulling         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


# ****************************** PREPARATION ********************************* #

# Gets this file's name (without suffix) for automatic variable creation later.
FILENAME	:=	$(basename $(notdir $(lastword $(MAKEFILE_LIST))))

# Resets TMP to get rid of any old values from other .mk files.
TMP			:=


# ***************************** CONFIGURATION ******************************** #

# Dependencies - has to be the basename of the corresponding .mk file:
DEPS	:=

# Directory of source files in src/ directory:
DIR		:=	libft/

# Source files:
#  Chars:
SUBDIR	:=	chars/
TMP		+=	$(addprefix $(DIR)$(SUBDIR), \
			ft_isalnum.c \
			ft_isalpha.c \
			ft_isascii.c \
			ft_isdigit.c \
			ft_isprint.c \
			ft_isspace.c \
			ft_tolower.c \
			ft_toupper.c \
)

#  Lists:
#   Singly-linked:
SUBDIR	:=	lists/singly_linked/
TMP		+=	$(addprefix $(DIR)$(SUBDIR), \
			ft_lstadd_back.c \
			ft_lstadd_front.c \
			ft_lstclear.c \
			ft_lstdelone.c \
			ft_lstiter.c \
			ft_lstlast.c \
			ft_lstmap.c \
			ft_lstnew.c \
			ft_lstsize.c \
			ft_lstsort_bubble.c \
)

#   Doubly-linked:
SUBDIR	:=	lists/doubly_linked/
TMP		+=	$(addprefix $(DIR)$(SUBDIR), \
			ft_lstadd_back_d.c \
			ft_lstadd_front_d.c \
			ft_lstclear_d.c \
			ft_lstlast_d.c \
			ft_lstnew_d.c \
)

#  Memory:
SUBDIR	:=	memory/
TMP		+=	$(addprefix $(DIR)$(SUBDIR), \
			ft_bzero.c \
			ft_calloc.c \
			ft_free_and_null.c \
			ft_memchr.c \
			ft_memcmp.c \
			ft_memcpy.c \
			ft_memmove.c \
			ft_memset.c \
)

#  Numbers:
SUBDIR	:=	numbers/
TMP		+=	$(addprefix $(DIR)$(SUBDIR), \
			ft_atof.c \
			ft_atoi.c \
			ft_atol.c \
)

#  Put:
SUBDIR	:=	put/
TMP		+=	$(addprefix $(DIR)$(SUBDIR), \
			ft_putchar_fd.c \
			ft_putendl_fd.c \
			ft_putnbr_base_fd.c \
			ft_putnbr_fd.c \
			ft_putnchar_fd.c \
			ft_putnstr_fd.c \
			ft_putstr_fd.c \
)

#  Strings:
SUBDIR	:=	strings/
TMP		+=	$(addprefix $(DIR)$(SUBDIR), \
			ft_itoa.c \
			ft_split.c \
			ft_strchr.c \
			ft_strcmp.c \
			ft_strdup.c \
			ft_strisdigits.c \
			ft_striteri.c \
			ft_strjoin.c \
			ft_strlcat.c \
			ft_strlcpy.c \
			ft_strlen.c \
			ft_strmapi.c \
			ft_strmatches_any.c \
			ft_strncmp.c \
			ft_strnstr.c \
			ft_strrchr.c \
			ft_strtok.c \
			ft_strtrim.c \
			ft_substr.c \
)

#  Various:
SUBDIR	:=	various/
TMP		+=	$(addprefix $(DIR)$(SUBDIR), \
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
