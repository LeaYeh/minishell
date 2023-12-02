# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/25 12:48:32 by ldulling          #+#    #+#              #
#    Updated: 2023/12/02 20:14:14 by ldulling         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


# ***************************** CONFIGURATION ******************************** #

NAME			:=	libft.a

# Header files directory:
I				:=	inc/

# Build directories:
B				:=	build/
D				:=	$B_dep/
O				:=	$B_obj/

# Source files directory:
S				:=	src/

# Makefiles in build/ directory with source file listings to be included
# (files that are dependent on others need to be below their dependency):
SOURCELISTS		:=	libft.mk \
					ft_printf.mk \
					get_next_line.mk \

# Flags:
CC				:=	cc
CFLAGS			?=	-Wall -Wextra -Werror $(addprefix -I,$I)
DEBUGFLAGS		:=	-g
ARFLAGS			:=	rcs


# ***************************** BUILD PROCESS ******************************** #

.DEFAULT_GOAL	:=	all

include				$(addprefix $B,$(SOURCELISTS))

SRC				:=	$(foreach name,$(basename $(SOURCELISTS)),$(SRC_$(name)))

DEP				:=	$(SRC:%.c=$D%.d)
OBJ				:=	$(SRC:%.c=$O%.o)
SUBDIRS_D		:=	$(sort $(dir $(DEP)))
SUBDIRS_O		:=	$(sort $(dir $(OBJ)))

.PHONY			:	all cleandep cleanobj clean fclean re debug norm print-%

all				:	$(NAME)

$(NAME)			:	$(OBJ)
					ar $(ARFLAGS) $(NAME) $(OBJ)

$(OBJ):	$O%.o	:	$S%.c | $(SUBDIRS_O)
					$(CC) $(CFLAGS) -c $< -o $@

$(DEP):	$D%.d	:	$S%.c | $(SUBDIRS_D)
	@				$(CC) $(CFLAGS) -M -MP -MF $@ -MT "$O$*.o $@" $<

$(SUBDIRS_O) $(SUBDIRS_D):
	@				mkdir -p $@

cleandep		:
ifneq (,$(wildcard $(DEP)))
					rm -f $(DEP)
endif
ifneq (,$(wildcard $D))
					-find $(D) -type d -empty -delete
endif

cleanobj		:
ifneq (,$(wildcard $(OBJ)))
					rm -f $(OBJ)
endif
ifneq (,$(wildcard $O))
					-find $(O) -type d -empty -delete
endif

clean			:	cleandep cleanobj

fclean			:	clean
ifneq (,$(wildcard $(NAME)))
					rm -f $(NAME)
endif

re				:	fclean all

debug			:	CFLAGS += $(DEBUGFLAGS)
debug			:	re

norm			:
	@				read -p "Press Enter to check $$(basename "$$(pwd)")..." \
					userInput;
	@				-norminette -R CheckForbiddenSourceHeader -R CheckDefine \
					$(addprefix $S,$(SRC)) $(foreach dir,$I,$(dir)*.h)

ifeq (,$(filter cleandep cleanobj clean fclean re debug norm,$(MAKECMDGOALS)))
    ifneq (,$(wildcard $O))
        -include	$(DEP)
    endif
endif


# *************************** MAKEFILE DEBUGGING ***************************** #

# Prints the values of the variable given after the minus.
print-%			:
	@				echo $* = $($*)
