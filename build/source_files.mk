# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    source_files.mk                                    :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/19 16:15:33 by ldulling          #+#    #+#              #
#    Updated: 2024/04/04 23:25:38 by ldulling         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


# Source files:
#  Main:
SUBDIR	:=	./
SRC		:=	$(addprefix $(SUBDIR), \
            main.c \
)

#  Backend:
#   Builtins:
SUBDIR	:=	backend/builtins/
SRC		+=	$(addprefix $(SUBDIR), \
            easter_egg.c \
            echo.c \
            env.c \
            pwd.c \
            unset.c \
)
#   cd:
SUBDIR	:=	backend/builtins/cd/
SRC		+=	$(addprefix $(SUBDIR), \
            cd.c \
            cd_errors.c \
            cd_utils.c \
            component_list.c \
            component_list_utils.c \
            dot_component.c \
            env_pwd_update.c \
            path.c \
)
#   exit:
SUBDIR	:=	backend/builtins/exit/
SRC		+=	$(addprefix $(SUBDIR), \
            exit.c \
            exit_utils.c \
)
#   export:
SUBDIR	:=	backend/builtins/export/
SRC		+=	$(addprefix $(SUBDIR), \
            export.c \
            export_output.c \
)
#   Executor:
SUBDIR	:=	backend/executor/
SRC		+=	$(addprefix $(SUBDIR), \
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
#   Redirection:
SUBDIR	:=	backend/redirection/
SRC		+=	$(addprefix $(SUBDIR), \
            file_descriptor.c \
            heredoc.c \
            heredoc_string_utils.c \
            heredoc_utils.c \
            io_file.c \
            pipe.c \
            pipe_utils.c \
            stdio_bind.c \
)

#  Debug:
SUBDIR	:=	debug/
SRC		+=	$(addprefix $(SUBDIR), \
            print_ast_bfs.c \
            print_cmd_table.c \
            print_expanded_cmd_table.c \
            print_expanded_cmd_table_content.c \
            print_expander_task_list.c \
            print_final_cmd_table.c \
            print_list.c \
            print_stack.c \
)

#  Frontend:
#   Expander:
SUBDIR	:=	frontend/expander/
SRC		+=	$(addprefix $(SUBDIR), \
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
#   Lexer:
SUBDIR	:=	frontend/lexer/
SRC		+=	$(addprefix $(SUBDIR), \
            lexer.c \
            lexer_utils.c \
            token_data_list.c \
            token_list.c \
            token_list_post_processing.c \
            token_type.c \
)
#   Parser:
SUBDIR	:=	frontend/parser/
SRC		+=	$(addprefix $(SUBDIR), \
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

#  Shell:
SUBDIR	:=	shell/
SRC		+=	$(addprefix $(SUBDIR), \
            clean.c \
            default_env_list.c \
            env_list.c \
            init.c \
)

#  Signal:
SUBDIR	:=	signal/
SRC		+=	$(addprefix $(SUBDIR), \
            exception_broadcaster.c \
            signal_handler.c \
)

#  Utils:
SUBDIR	:=	utils/
SRC		+=	$(addprefix $(SUBDIR), \
            array_utils.c \
            ast_utils.c \
            cmd_table_list_utils.c \
            cmd_table_operation_utils.c \
            cmd_table_traversal_utils.c \
            cmd_table_type_utils.c \
            env_list_operation_utils.c \
            env_list_status_utils.c \
            env_utils.c \
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
