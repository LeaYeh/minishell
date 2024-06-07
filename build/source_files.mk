# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    source_files.mk                                    :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/19 16:15:33 by ldulling          #+#    #+#              #
#    Updated: 2024/06/07 07:25:14 by ldulling         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Initialize SRC
SRC		:= $(SRC)

# Main:
DIR		:=	./
SRC		+=	$(addprefix $(DIR), \
            main.c \
)

# Backend:
#  Builtins:
DIR		:=	backend/builtins/
SRC		+=	$(addprefix $(DIR), \
            easter_egg.c \
            echo.c \
            env.c \
            pwd.c \
            unset.c \
)
#  cd:
DIR		:=	backend/builtins/cd/
SRC		+=	$(addprefix $(DIR), \
            cd.c \
            cd_errors.c \
            cd_utils.c \
            component_list.c \
            component_list_utils.c \
            dot_component.c \
            env_pwd_update.c \
            path.c \
)
#  exit:
DIR		:=	backend/builtins/exit/
SRC		+=	$(addprefix $(DIR), \
            exit.c \
            exit_utils.c \
)
#  export:
DIR		:=	backend/builtins/export/
SRC		+=	$(addprefix $(DIR), \
            export.c \
            export_output.c \
)
#  Executor:
DIR		:=	backend/executor/
SRC		+=	$(addprefix $(DIR), \
            builtin_cmd.c \
            control_operator.c \
            executor.c \
            executor_utils.c \
            external_cmd.c \
            pipeline_process.c \
            simple_cmd_process.c \
            subshell_process.c \
            wait_process.c \
)
#  Redirection:
DIR		:=	backend/redirection/
SRC		+=	$(addprefix $(DIR), \
            file_descriptor.c \
            heredoc.c \
            heredoc_string_utils.c \
            heredoc_utils.c \
            io_file.c \
            pipe.c \
            pipe_utils.c \
            stdio_redirect.c \
)

# Debug:
DIR		:=	debug/
SRC		+=	$(addprefix $(DIR), \
            print_ast_bfs.c \
            print_cmd_table.c \
            print_expanded_cmd_table.c \
            print_expanded_cmd_table_content.c \
            print_expander_task_list.c \
            print_final_cmd_table.c \
            print_list.c \
            print_stack.c \
)

# Frontend:
#  Expander:
DIR		:=	frontend/expander/
SRC		+=	$(addprefix $(DIR), \
            bad_substitution.c \
            expander.c \
            expander_task_list.c \
            expander_task_list_utils.c \
            expander_task_utils.c \
            expander_utils.c \
            null_expansion.c \
            parameter_expansion.c \
            quote_removal.c \
            wildcard_expansion.c \
            wildcard_expansion_utils.c \
            wildcard_file_list.c \
            wildcard_task_list.c \
            word_splitting.c \
            word_splitting_utils.c \
)
#  Lexer:
DIR		:=	frontend/lexer/
SRC		+=	$(addprefix $(DIR), \
            lexer.c \
            lexer_utils.c \
            token_data_list.c \
            token_list.c \
            token_list_post_processing.c \
            token_type.c \
)
#  Parser:
DIR		:=	frontend/parser/
SRC		+=	$(addprefix $(DIR), \
            cmd_table_list.c \
            cmd_table_symbol.c \
            cmd_table_symbol_utils.c \
            cmd_table_word.c \
            parser_action.c \
            parser.c \
            parser_data.c \
            parsing_table_operation.c \
            syntax_error.c \
)

# Shell:
DIR		:=	shell/
SRC		+=	$(addprefix $(DIR), \
            clean.c \
            default_env_list.c \
            env_list.c \
            init.c \
)

# Signal:
DIR		:=	signal/
SRC		+=	$(addprefix $(DIR), \
            exception_broadcaster.c \
            signal_handler.c \
)

# Utils:
DIR		:=	utils/
SRC		+=	$(addprefix $(DIR), \
            array_utils.c \
            ast_utils.c \
            cmd_table_list_utils.c \
            cmd_table_operation_utils.c \
            cmd_table_traversal_utils.c \
            cmd_table_type_utils.c \
            env_list_operation_utils.c \
            env_list_status_utils.c \
            env_utils.c \
            error_utils.c \
            exec_path_setup_utils.c \
            expansion_utils.c \
            file_utils.c \
            final_cmd_table_setup.c \
            final_cmd_table_utils.c \
            io_redirect_utils.c \
            pid_utils.c \
            print_utils.c \
            stack_utils.c \
            symbol_utils.c \
            token_status_utils.c \
            token_type_utils.c \
            token_utils.c \
            user_input_utils.c \
            varname_utils.c \
)
