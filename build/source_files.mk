# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    source_files.mk                                    :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/19 16:15:33 by ldulling          #+#    #+#              #
#    Updated: 2024/03/19 17:42:04 by ldulling         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


# Source files:
#  Main:
SUBDIR	:=	./
SRC		+=	$(addprefix $(SUBDIR), \
            main.c \
            shell_clean.c \
)

#  Backend:
#   Executor:
SUBDIR	:=	backend/executor/
SRC		+=	$(addprefix $(SUBDIR), \
            executor.c \
            executor_utils.c \
            handle_assignment.c \
            handle_builtin.c \
            handle_control_op.c \
            handle_external.c \
            handle_pipeline.c \
            handle_simple_cmd.c \
            handle_subshell.c \
)
#   Redirection:
SUBDIR	:=	backend/redirection/
SRC		+=	$(addprefix $(SUBDIR), \
            bind.c \
            heredoc.c \
            heredoc_utils.c \
            io_redirect.c \
            pipe_redirect.c \
            pipe_redirect_utils.c \
)

#  Builtins:
SUBDIR	:=	builtins/
SRC		+=	$(addprefix $(SUBDIR), \
            echo.c \
            env.c \
            exit.c \
            exit_utils.c \
            pwd.c \
            unset.c \
)
#   cd:
SUBDIR	:=	builtins/cd/
SRC		+=	$(addprefix $(SUBDIR), \
            cd.c \
            cd_errors.c \
            cd_utils.c \
            cmpnt_list.c \
            cmpnt_list_utils.c \
            dot_cmpnts.c \
            env_pwd_update.c \
            get_target_dir.c \
            process_path.c \
)
#   export:
SUBDIR	:=	builtins/export/
SRC		+=	$(addprefix $(SUBDIR), \
            export.c \
            print_exported_env.c \
)

#  Frontend:
#   Lexer:
SUBDIR	:=	frontend/lexer/
SRC		+=	$(addprefix $(SUBDIR), \
            create_token_data_list.c \
            create_token_list.c \
            finetune_token_list.c \
            lexer.c \
            lexer_utils.c \
            set_token_type.c \
)
#   Parser:
SUBDIR	:=	frontend/parser/
SRC		+=	$(addprefix $(SUBDIR), \
            cmd_table_list.c \
            cmd_table_symbol.c \
            cmd_table_symbol_utils.c \
            cmd_table_word.c \
            parser.c \
            parser_operation.c \
            parser_utils.c \
            parsing_table.c \
)
#   Expander:
SUBDIR	:=	frontend/expander/
SRC		+=	$(addprefix $(SUBDIR), \
            bad_substitution.c \
            expander.c \
            expander_task_list.c \
            expander_task_list_utils.c \
            expander_utils.c \
            expansion_handler.c \
            null_expansion.c \
            quote_removal.c \
            special_param_expansion.c \
            variable_expansion.c \
            word_splitting.c \
)

#  Init:
SUBDIR	:=	init/
SRC		+=	$(addprefix $(SUBDIR), \
            init_shell.c \
            setup_default_env_list.c \
            setup_env_list.c \
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
            cmd_table_operation_utils.c \
            cmd_table_status_utils.c \
            cmd_table_traversal_utils.c \
            cmd_table_type_utils.c \
            env_list_op_utils.c \
            env_list_status_utils.c \
            env_utils.c \
            exec_path_setup_utils.c \
            expansion_utils.c \
            file_utils.c \
            final_cmd_table_setup.c \
            final_cmd_table_utils.c \
            io_redirect_status_utils.c \
            io_redirect_utils.c \
            process_utils.c \
            stack_status_utils.c \
            stack_utils.c \
            string_utils.c \
            symbol_utils.c \
            token_status_utils.c \
            token_utils.c \
            type_utils.c \
            varname_utils.c \
)
