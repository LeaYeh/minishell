| State | Element | Action | Next State | Number of Reduced Tokens |
|-------|------------|--------|------------|-------------------------|
| 0 | WORD | shift | 1 | -1 |
| 0 | ASSIGNMENT_WORD | shift | 2 | -1 |
| 0 | RED_IN | shift | 3 | -1 |
| 0 | RED_OUT | shift | 4 | -1 |
| 0 | HERE_DOC | shift | 5 | -1 |
| 0 | APPEND | shift | 6 | -1 |
| 0 | L_PAREN | shift | 7 | -1 |
| 0 | and_or | goto | 8 | -1 |
| 0 | pipe_sequence | goto | 9 | -1 |
| 0 | command | goto | 10 | -1 |
| 0 | subshell | goto | 11 | -1 |
| 0 | simple_command | goto | 12 | -1 |
| 0 | cmd_name | goto | 13 | -1 |
| 0 | cmd_prefix | goto | 14 | -1 |
| 0 | io_redirect | goto | 15 | -1 |
| 0 | io_file | goto | 16 | -1 |
| 0 | io_here | goto | 17 | -1 |
| 1 | -1 | reduce | cmd_name | ['WORD'] |
| 2 | -1 | reduce | cmd_prefix | ['ASSIGNMENT_WORD'] |
| 3 | WORD | shift | 18 | -1 |
| 3 | filename | goto | 19 | -1 |
| 4 | WORD | shift | 18 | -1 |
| 4 | filename | goto | 20 | -1 |
| 5 | WORD | shift | 21 | -1 |
| 5 | here_end | goto | 22 | -1 |
| 6 | WORD | shift | 18 | -1 |
| 6 | filename | goto | 23 | -1 |
| 7 | WORD | shift | 1 | -1 |
| 7 | ASSIGNMENT_WORD | shift | 2 | -1 |
| 7 | RED_IN | shift | 3 | -1 |
| 7 | RED_OUT | shift | 4 | -1 |
| 7 | HERE_DOC | shift | 5 | -1 |
| 7 | APPEND | shift | 6 | -1 |
| 7 | L_PAREN | shift | 7 | -1 |
| 7 | and_or | goto | 24 | -1 |
| 7 | pipe_sequence | goto | 9 | -1 |
| 7 | command | goto | 10 | -1 |
| 7 | subshell | goto | 11 | -1 |
| 7 | simple_command | goto | 12 | -1 |
| 7 | cmd_name | goto | 13 | -1 |
| 7 | cmd_prefix | goto | 14 | -1 |
| 7 | io_redirect | goto | 15 | -1 |
| 7 | io_file | goto | 16 | -1 |
| 7 | io_here | goto | 17 | -1 |
| 8 | $end | shift | 25 | -1 |
| 8 | AND | shift | 26 | -1 |
| 8 | OR | shift | 27 | -1 |
| 9 | PIPE | shift | 28 | -1 |
| 9 | -1 | reduce | and_or | ['pipe_sequence'] |
| 10 | -1 | reduce | pipe_sequence | ['command'] |
| 11 | RED_IN | shift | 3 | -1 |
| 11 | RED_OUT | shift | 4 | -1 |
| 11 | HERE_DOC | shift | 5 | -1 |
| 11 | APPEND | shift | 6 | -1 |
| 11 | -1 | reduce | command | ['subshell'] |
| 11 | redirect_list | goto | 29 | -1 |
| 11 | io_redirect | goto | 30 | -1 |
| 11 | io_file | goto | 16 | -1 |
| 11 | io_here | goto | 17 | -1 |
| 12 | -1 | reduce | command | ['simple_command'] |
| 13 | WORD | shift | 31 | -1 |
| 13 | RED_IN | shift | 3 | -1 |
| 13 | RED_OUT | shift | 4 | -1 |
| 13 | HERE_DOC | shift | 5 | -1 |
| 13 | APPEND | shift | 6 | -1 |
| 13 | -1 | reduce | simple_command | ['cmd_name'] |
| 13 | cmd_suffix | goto | 32 | -1 |
| 13 | io_redirect | goto | 33 | -1 |
| 13 | io_file | goto | 16 | -1 |
| 13 | io_here | goto | 17 | -1 |
| 14 | WORD | shift | 34 | -1 |
| 14 | ASSIGNMENT_WORD | shift | 35 | -1 |
| 14 | RED_IN | shift | 3 | -1 |
| 14 | RED_OUT | shift | 4 | -1 |
| 14 | HERE_DOC | shift | 5 | -1 |
| 14 | APPEND | shift | 6 | -1 |
| 14 | -1 | reduce | simple_command | ['cmd_prefix'] |
| 14 | cmd_word | goto | 36 | -1 |
| 14 | io_redirect | goto | 37 | -1 |
| 14 | io_file | goto | 16 | -1 |
| 14 | io_here | goto | 17 | -1 |
| 15 | -1 | reduce | cmd_prefix | ['io_redirect'] |
| 16 | -1 | reduce | io_redirect | ['io_file'] |
| 17 | -1 | reduce | io_redirect | ['io_here'] |
| 18 | -1 | reduce | filename | ['WORD'] |
| 19 | -1 | reduce | io_file | ['RED_IN', 'filename'] |
| 20 | -1 | reduce | io_file | ['RED_OUT', 'filename'] |
| 21 | -1 | reduce | here_end | ['WORD'] |
| 22 | -1 | reduce | io_here | ['HERE_DOC', 'here_end'] |
| 23 | -1 | reduce | io_file | ['APPEND', 'filename'] |
| 24 | AND | shift | 26 | -1 |
| 24 | OR | shift | 27 | -1 |
| 24 | R_PAREN | shift | 38 | -1 |
| 25 | -1 | accept | None | -1 |
| 26 | WORD | shift | 1 | -1 |
| 26 | ASSIGNMENT_WORD | shift | 2 | -1 |
| 26 | RED_IN | shift | 3 | -1 |
| 26 | RED_OUT | shift | 4 | -1 |
| 26 | HERE_DOC | shift | 5 | -1 |
| 26 | APPEND | shift | 6 | -1 |
| 26 | L_PAREN | shift | 7 | -1 |
| 26 | pipe_sequence | goto | 39 | -1 |
| 26 | command | goto | 10 | -1 |
| 26 | subshell | goto | 11 | -1 |
| 26 | simple_command | goto | 12 | -1 |
| 26 | cmd_name | goto | 13 | -1 |
| 26 | cmd_prefix | goto | 14 | -1 |
| 26 | io_redirect | goto | 15 | -1 |
| 26 | io_file | goto | 16 | -1 |
| 26 | io_here | goto | 17 | -1 |
| 27 | WORD | shift | 1 | -1 |
| 27 | ASSIGNMENT_WORD | shift | 2 | -1 |
| 27 | RED_IN | shift | 3 | -1 |
| 27 | RED_OUT | shift | 4 | -1 |
| 27 | HERE_DOC | shift | 5 | -1 |
| 27 | APPEND | shift | 6 | -1 |
| 27 | L_PAREN | shift | 7 | -1 |
| 27 | pipe_sequence | goto | 40 | -1 |
| 27 | command | goto | 10 | -1 |
| 27 | subshell | goto | 11 | -1 |
| 27 | simple_command | goto | 12 | -1 |
| 27 | cmd_name | goto | 13 | -1 |
| 27 | cmd_prefix | goto | 14 | -1 |
| 27 | io_redirect | goto | 15 | -1 |
| 27 | io_file | goto | 16 | -1 |
| 27 | io_here | goto | 17 | -1 |
| 28 | WORD | shift | 1 | -1 |
| 28 | ASSIGNMENT_WORD | shift | 2 | -1 |
| 28 | RED_IN | shift | 3 | -1 |
| 28 | RED_OUT | shift | 4 | -1 |
| 28 | HERE_DOC | shift | 5 | -1 |
| 28 | APPEND | shift | 6 | -1 |
| 28 | L_PAREN | shift | 7 | -1 |
| 28 | command | goto | 41 | -1 |
| 28 | subshell | goto | 11 | -1 |
| 28 | simple_command | goto | 12 | -1 |
| 28 | cmd_name | goto | 13 | -1 |
| 28 | cmd_prefix | goto | 14 | -1 |
| 28 | io_redirect | goto | 15 | -1 |
| 28 | io_file | goto | 16 | -1 |
| 28 | io_here | goto | 17 | -1 |
| 29 | RED_IN | shift | 3 | -1 |
| 29 | RED_OUT | shift | 4 | -1 |
| 29 | HERE_DOC | shift | 5 | -1 |
| 29 | APPEND | shift | 6 | -1 |
| 29 | -1 | reduce | command | ['subshell', 'redirect_list'] |
| 29 | io_redirect | goto | 42 | -1 |
| 29 | io_file | goto | 16 | -1 |
| 29 | io_here | goto | 17 | -1 |
| 30 | -1 | reduce | redirect_list | ['io_redirect'] |
| 31 | -1 | reduce | cmd_suffix | ['WORD'] |
| 32 | WORD | shift | 43 | -1 |
| 32 | RED_IN | shift | 3 | -1 |
| 32 | RED_OUT | shift | 4 | -1 |
| 32 | HERE_DOC | shift | 5 | -1 |
| 32 | APPEND | shift | 6 | -1 |
| 32 | -1 | reduce | simple_command | ['cmd_name', 'cmd_suffix'] |
| 32 | io_redirect | goto | 44 | -1 |
| 32 | io_file | goto | 16 | -1 |
| 32 | io_here | goto | 17 | -1 |
| 33 | -1 | reduce | cmd_suffix | ['io_redirect'] |
| 34 | -1 | reduce | cmd_word | ['WORD'] |
| 35 | -1 | reduce | cmd_prefix | ['cmd_prefix', 'ASSIGNMENT_WORD'] |
| 36 | WORD | shift | 31 | -1 |
| 36 | RED_IN | shift | 3 | -1 |
| 36 | RED_OUT | shift | 4 | -1 |
| 36 | HERE_DOC | shift | 5 | -1 |
| 36 | APPEND | shift | 6 | -1 |
| 36 | -1 | reduce | simple_command | ['cmd_prefix', 'cmd_word'] |
| 36 | cmd_suffix | goto | 45 | -1 |
| 36 | io_redirect | goto | 33 | -1 |
| 36 | io_file | goto | 16 | -1 |
| 36 | io_here | goto | 17 | -1 |
| 37 | -1 | reduce | cmd_prefix | ['cmd_prefix', 'io_redirect'] |
| 38 | -1 | reduce | subshell | ['L_PAREN', 'and_or', 'R_PAREN'] |
| 39 | PIPE | shift | 28 | -1 |
| 39 | -1 | reduce | and_or | ['and_or', 'AND', 'pipe_sequence'] |
| 40 | PIPE | shift | 28 | -1 |
| 40 | -1 | reduce | and_or | ['and_or', 'OR', 'pipe_sequence'] |
| 41 | -1 | reduce | pipe_sequence | ['pipe_sequence', 'PIPE', 'command'] |
| 42 | -1 | reduce | redirect_list | ['redirect_list', 'io_redirect'] |
| 43 | -1 | reduce | cmd_suffix | ['cmd_suffix', 'WORD'] |
| 44 | -1 | reduce | cmd_suffix | ['cmd_suffix', 'io_redirect'] |
| 45 | WORD | shift | 43 | -1 |
| 45 | RED_IN | shift | 3 | -1 |
| 45 | RED_OUT | shift | 4 | -1 |
| 45 | HERE_DOC | shift | 5 | -1 |
| 45 | APPEND | shift | 6 | -1 |
| 45 | -1 | reduce | simple_command | ['cmd_prefix', 'cmd_word', 'cmd_suffix'] |
| 45 | io_redirect | goto | 44 | -1 |
| 45 | io_file | goto | 16 | -1 |
| 45 | io_here | goto | 17 | -1 |
