# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    libft.mk                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/16 13:33:38 by ldulling          #+#    #+#              #
#    Updated: 2024/06/28 19:31:23 by ldulling         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Initialize SRC
SRC		:= $(SRC)

# Chars:
DIR		:=	chars/
SRC		+=	$(addprefix $(DIR), \
			ft_isalnum.c \
			ft_isalpha.c \
			ft_isascii.c \
			ft_isdigit.c \
			ft_issign.c \
			ft_isprint.c \
			ft_isspace.c \
			ft_tolower.c \
			ft_toupper.c \
)

# ft_printf:
#  ft_printf + ft_dprintf:
DIR		:=	ft_printf/
SRC		+=	$(addprefix $(DIR), \
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

#  ft_snprintf + ft_vsnprintf:
DIR		:=	ft_printf/ft_snprintf/
SRC		+=	$(addprefix $(DIR), \
			check_args.c \
			ft_snprintf.c \
			ft_vsnprintf.c \
			get_max_size.c \
			parseandsprint.c \
			sprint_char.c \
			sprint_nbr.c \
			sprint_parsed.c \
			sprint_ptr.c \
			sprint_str.c \
			set_sformat.c \
)

# get_next_line:
DIR		:=	get_next_line/
SRC		+=	$(addprefix $(DIR), \
			get_next_line.c \
			get_next_line_utils.c \
			free_get_next_line.c \
)

# Lists:
#  Doubly-linked:
DIR		:=	lists/doubly_linked/
SRC		+=	$(addprefix $(DIR), \
			ft_lstadd_back_d.c \
			ft_lstadd_front_d.c \
			ft_lstclear_d.c \
			ft_lstdelone_d.c \
			ft_lstdrop_node_d.c \
			ft_lstiter_d.c \
			ft_lstlast_d.c \
			ft_lstnew_back_d.c \
			ft_lstnew_d.c \
)

#  Singly-linked:
DIR		:=	lists/singly_linked/
SRC		+=	$(addprefix $(DIR), \
			ft_lstadd_back.c \
			ft_lstadd_back_eff.c \
			ft_lstadd_front.c \
			ft_lstclear.c \
			ft_lstdelone.c \
			ft_lstdrop_node.c \
			ft_lstdup.c \
			ft_lstinsert_after.c \
			ft_lstinsert_before.c \
			ft_lstiter.c \
			ft_lstlast.c \
			ft_lstmap.c \
			ft_lstnew.c \
			ft_lstnew_back.c \
			ft_lstnew_back_eff.c \
			ft_lstnew_front.c \
			ft_lstpop_front.c \
			ft_lstpop_front_content.c \
			ft_lstsize.c \
			ft_lstsize_non_null.c \
			ft_lstsort_bubble.c \
			ft_lstsort_merge.c \
			ft_lstswap_head.c \
)

# Memory:
DIR		:=	memory/
SRC		+=	$(addprefix $(DIR), \
			ft_bzero.c \
			ft_calloc.c \
			ft_free_and_null.c \
			ft_memchr.c \
			ft_memcmp.c \
			ft_memcpy.c \
			ft_memmove.c \
			ft_memset.c \
)

# Numbers:
DIR		:=	numbers/
SRC		+=	$(addprefix $(DIR), \
			ft_atof.c \
			ft_atoi.c \
			ft_atol.c \
			ft_isoverflow_int.c \
			ft_isoverflow_long.c \
)

# Put:
DIR		:=	put/
SRC		+=	$(addprefix $(DIR), \
			ft_putchar_fd.c \
			ft_putendl_fd.c \
			ft_putnbr_base_fd.c \
			ft_putnbr_fd.c \
			ft_putnchar_fd.c \
			ft_putnstr_fd.c \
			ft_putstr_fd.c \
			ft_snputnbr_base.c \
			ft_sputnchar.c \
			ft_sputnstr.c \
)

# Strings:
DIR		:=	strings/
SRC		+=	$(addprefix $(DIR), \
			ft_alphabetic.c \
			ft_itoa.c \
			ft_split.c \
			ft_split_at_index.c \
			ft_strchr.c \
			ft_strcmp.c \
			ft_strdel_sequence.c \
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
			ft_strndup.c \
			ft_strnstr.c \
			ft_strrchr.c \
			ft_strrnstr.c \
			ft_strrplc_part.c \
			ft_strrplc_sequence.c \
			ft_strtok.c \
			ft_strtrim.c \
			ft_substr.c \
)
