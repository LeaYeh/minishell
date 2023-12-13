| State | Token Type | Action | Next State | Number of Reduced Tokens |
|-------|------------|--------|------------|-------------------------|
| 0 | WORD | shift | 1 | ['WORD'] |
| 0 | ASSIGNMENT_WORD | shift | 2 | ['WORD'] |
| 0 | RED_IN | shift | 3 | ['WORD'] |
| 0 | RED_OUT | shift | 4 | ['WORD'] |
| 0 | HERE_DOC | shift | 5 | ['WORD'] |
| 0 | APPEND | shift | 6 | ['WORD'] |
| 0 | L_BRACKET | shift | 7 | ['WORD'] |
| 0 | pipe_sequence | go to state 8 | 8 | -1 |
| 0 | subshell | go to state 9 | 9 | -1 |
| 0 | command | go to state 10 | 10 | -1 |
| 0 | simple_command | go to state 11 | 11 | -1 |
| 0 | cmd_name | go to state 12 | 12 | -1 |
| 0 | cmd_prefix | go to state 13 | 13 | -1 |
| 0 | io_redirect | go to state 14 | 14 | -1 |
| 0 | io_file | go to state 15 | 15 | -1 |
| 0 | io_here | go to state 16 | 16 | -1 |
| 1 | -1 | reduce | cmd_name | -1 |
| 2 | -1 | reduce | cmd_prefix | -1 |
| 3 | WORD | shift | 17 | ['subshell'] |
| 3 | filename | go to state 18 | 18 | -1 |
| 4 | WORD | shift | 17 | ['subshell'] |
| 4 | filename | go to state 19 | 19 | -1 |
| 5 | WORD | shift | 20 | ['subshell'] |
| 5 | here_end | go to state 21 | 21 | -1 |
| 6 | WORD | shift | 17 | ['subshell'] |
| 6 | filename | go to state 22 | 22 | -1 |
| 7 | WORD | shift | 1 | ['subshell'] |
| 7 | ASSIGNMENT_WORD | shift | 2 | ['subshell'] |
| 7 | RED_IN | shift | 3 | ['subshell'] |
| 7 | RED_OUT | shift | 4 | ['subshell'] |
| 7 | HERE_DOC | shift | 5 | ['subshell'] |
| 7 | APPEND | shift | 6 | ['subshell'] |
| 7 | L_BRACKET | shift | 7 | ['subshell'] |
| 7 | pipe_sequence | go to state 23 | 23 | -1 |
| 7 | and_or | go to state 24 | 24 | -1 |
| 7 | subshell | go to state 9 | 9 | -1 |
| 7 | command | go to state 10 | 10 | -1 |
| 7 | simple_command | go to state 11 | 11 | -1 |
| 7 | cmd_name | go to state 12 | 12 | -1 |
| 7 | cmd_prefix | go to state 13 | 13 | -1 |
| 7 | io_redirect | go to state 14 | 14 | -1 |
| 7 | io_file | go to state 15 | 15 | -1 |
| 7 | io_here | go to state 16 | 16 | -1 |
| 8 | $end | shift | 25 | ['subshell'] |
| 8 | PIPE | shift | 26 | ['subshell'] |
| 9 | RED_IN | shift | 3 | ['subshell'] |
| 9 | RED_OUT | shift | 4 | ['subshell'] |
| 9 | HERE_DOC | shift | 5 | ['subshell'] |
| 9 | APPEND | shift | 6 | ['subshell'] |
| 9 | -1 | reduce | command | -1 |
| 9 | redirect_list | go to state 27 | 27 | -1 |
| 9 | io_redirect | go to state 28 | 28 | -1 |
| 9 | io_file | go to state 15 | 15 | -1 |
| 9 | io_here | go to state 16 | 16 | -1 |
| 10 | -1 | reduce | pipe_sequence | -1 |
| 11 | -1 | reduce | command | -1 |
| 12 | WORD | shift | 29 | ['cmd_name'] |
| 12 | RED_IN | shift | 3 | ['cmd_name'] |
| 12 | RED_OUT | shift | 4 | ['cmd_name'] |
| 12 | HERE_DOC | shift | 5 | ['cmd_name'] |
| 12 | APPEND | shift | 6 | ['cmd_name'] |
| 12 | -1 | reduce | simple_command | -1 |
| 12 | cmd_suffix | go to state 30 | 30 | -1 |
| 12 | io_redirect | go to state 31 | 31 | -1 |
| 12 | io_file | go to state 15 | 15 | -1 |
| 12 | io_here | go to state 16 | 16 | -1 |
| 13 | WORD | shift | 32 | ['cmd_prefix'] |
| 13 | ASSIGNMENT_WORD | shift | 33 | ['cmd_prefix'] |
| 13 | RED_IN | shift | 3 | ['cmd_prefix'] |
| 13 | RED_OUT | shift | 4 | ['cmd_prefix'] |
| 13 | HERE_DOC | shift | 5 | ['cmd_prefix'] |
| 13 | APPEND | shift | 6 | ['cmd_prefix'] |
| 13 | -1 | reduce | simple_command | -1 |
| 13 | cmd_word | go to state 34 | 34 | -1 |
| 13 | io_redirect | go to state 35 | 35 | -1 |
| 13 | io_file | go to state 15 | 15 | -1 |
| 13 | io_here | go to state 16 | 16 | -1 |
| 14 | -1 | reduce | cmd_prefix | -1 |
| 15 | -1 | reduce | io_redirect | -1 |
| 16 | -1 | reduce | io_redirect | -1 |
| 17 | -1 | reduce | filename | -1 |
| 18 | -1 | reduce | io_file | -1 |
| 19 | -1 | reduce | io_file | -1 |
| 20 | -1 | reduce | here_end | -1 |
| 21 | -1 | reduce | io_here | -1 |
| 22 | -1 | reduce | io_file | -1 |
| 23 | PIPE | shift | 26 | ['pipe_sequence'] |
| 23 | -1 | reduce | and_or | -1 |
| 24 | AND | shift | 36 | ['subshell', 'redirect_list'] |
| 24 | OR | shift | 37 | ['subshell', 'redirect_list'] |
| 24 | R_BRACKET | shift | 38 | ['subshell', 'redirect_list'] |
| 25 | -1 | accept | None | -1 |
| 26 | WORD | shift | 1 | ['subshell', 'redirect_list'] |
| 26 | ASSIGNMENT_WORD | shift | 2 | ['subshell', 'redirect_list'] |
| 26 | RED_IN | shift | 3 | ['subshell', 'redirect_list'] |
| 26 | RED_OUT | shift | 4 | ['subshell', 'redirect_list'] |
| 26 | HERE_DOC | shift | 5 | ['subshell', 'redirect_list'] |
| 26 | APPEND | shift | 6 | ['subshell', 'redirect_list'] |
| 26 | L_BRACKET | shift | 7 | ['subshell', 'redirect_list'] |
| 26 | subshell | go to state 9 | 9 | -1 |
| 26 | command | go to state 39 | 39 | -1 |
| 26 | simple_command | go to state 11 | 11 | -1 |
| 26 | cmd_name | go to state 12 | 12 | -1 |
| 26 | cmd_prefix | go to state 13 | 13 | -1 |
| 26 | io_redirect | go to state 14 | 14 | -1 |
| 26 | io_file | go to state 15 | 15 | -1 |
| 26 | io_here | go to state 16 | 16 | -1 |
| 27 | RED_IN | shift | 3 | ['subshell', 'redirect_list'] |
| 27 | RED_OUT | shift | 4 | ['subshell', 'redirect_list'] |
| 27 | HERE_DOC | shift | 5 | ['subshell', 'redirect_list'] |
| 27 | APPEND | shift | 6 | ['subshell', 'redirect_list'] |
| 27 | -1 | reduce | command | -1 |
| 27 | io_redirect | go to state 40 | 40 | -1 |
| 27 | io_file | go to state 15 | 15 | -1 |
| 27 | io_here | go to state 16 | 16 | -1 |
| 28 | -1 | reduce | redirect_list | -1 |
| 29 | -1 | reduce | cmd_suffix | -1 |
| 30 | WORD | shift | 41 | ['cmd_name', 'cmd_suffix'] |
| 30 | RED_IN | shift | 3 | ['cmd_name', 'cmd_suffix'] |
| 30 | RED_OUT | shift | 4 | ['cmd_name', 'cmd_suffix'] |
| 30 | HERE_DOC | shift | 5 | ['cmd_name', 'cmd_suffix'] |
| 30 | APPEND | shift | 6 | ['cmd_name', 'cmd_suffix'] |
| 30 | -1 | reduce | simple_command | -1 |
| 30 | io_redirect | go to state 42 | 42 | -1 |
| 30 | io_file | go to state 15 | 15 | -1 |
| 30 | io_here | go to state 16 | 16 | -1 |
| 31 | -1 | reduce | cmd_suffix | -1 |
| 32 | -1 | reduce | cmd_word | -1 |
| 33 | -1 | reduce | cmd_prefix | -1 |
| 34 | WORD | shift | 29 | ['cmd_prefix', 'cmd_word'] |
| 34 | RED_IN | shift | 3 | ['cmd_prefix', 'cmd_word'] |
| 34 | RED_OUT | shift | 4 | ['cmd_prefix', 'cmd_word'] |
| 34 | HERE_DOC | shift | 5 | ['cmd_prefix', 'cmd_word'] |
| 34 | APPEND | shift | 6 | ['cmd_prefix', 'cmd_word'] |
| 34 | -1 | reduce | simple_command | -1 |
| 34 | cmd_suffix | go to state 43 | 43 | -1 |
| 34 | io_redirect | go to state 31 | 31 | -1 |
| 34 | io_file | go to state 15 | 15 | -1 |
| 34 | io_here | go to state 16 | 16 | -1 |
| 35 | -1 | reduce | cmd_prefix | -1 |
| 36 | WORD | shift | 1 | ['L_BRACKET', 'and_or', 'R_BRACKET'] |
| 36 | ASSIGNMENT_WORD | shift | 2 | ['L_BRACKET', 'and_or', 'R_BRACKET'] |
| 36 | RED_IN | shift | 3 | ['L_BRACKET', 'and_or', 'R_BRACKET'] |
| 36 | RED_OUT | shift | 4 | ['L_BRACKET', 'and_or', 'R_BRACKET'] |
| 36 | HERE_DOC | shift | 5 | ['L_BRACKET', 'and_or', 'R_BRACKET'] |
| 36 | APPEND | shift | 6 | ['L_BRACKET', 'and_or', 'R_BRACKET'] |
| 36 | L_BRACKET | shift | 7 | ['L_BRACKET', 'and_or', 'R_BRACKET'] |
| 36 | pipe_sequence | go to state 44 | 44 | -1 |
| 36 | subshell | go to state 9 | 9 | -1 |
| 36 | command | go to state 10 | 10 | -1 |
| 36 | simple_command | go to state 11 | 11 | -1 |
| 36 | cmd_name | go to state 12 | 12 | -1 |
| 36 | cmd_prefix | go to state 13 | 13 | -1 |
| 36 | io_redirect | go to state 14 | 14 | -1 |
| 36 | io_file | go to state 15 | 15 | -1 |
| 36 | io_here | go to state 16 | 16 | -1 |
| 37 | WORD | shift | 1 | ['L_BRACKET', 'and_or', 'R_BRACKET'] |
| 37 | ASSIGNMENT_WORD | shift | 2 | ['L_BRACKET', 'and_or', 'R_BRACKET'] |
| 37 | RED_IN | shift | 3 | ['L_BRACKET', 'and_or', 'R_BRACKET'] |
| 37 | RED_OUT | shift | 4 | ['L_BRACKET', 'and_or', 'R_BRACKET'] |
| 37 | HERE_DOC | shift | 5 | ['L_BRACKET', 'and_or', 'R_BRACKET'] |
| 37 | APPEND | shift | 6 | ['L_BRACKET', 'and_or', 'R_BRACKET'] |
| 37 | L_BRACKET | shift | 7 | ['L_BRACKET', 'and_or', 'R_BRACKET'] |
| 37 | pipe_sequence | go to state 45 | 45 | -1 |
| 37 | subshell | go to state 9 | 9 | -1 |
| 37 | command | go to state 10 | 10 | -1 |
| 37 | simple_command | go to state 11 | 11 | -1 |
| 37 | cmd_name | go to state 12 | 12 | -1 |
| 37 | cmd_prefix | go to state 13 | 13 | -1 |
| 37 | io_redirect | go to state 14 | 14 | -1 |
| 37 | io_file | go to state 15 | 15 | -1 |
| 37 | io_here | go to state 16 | 16 | -1 |
| 38 | -1 | reduce | subshell | -1 |
| 39 | -1 | reduce | pipe_sequence | -1 |
| 40 | -1 | reduce | redirect_list | -1 |
| 41 | -1 | reduce | cmd_suffix | -1 |
| 42 | -1 | reduce | cmd_suffix | -1 |
| 43 | WORD | shift | 41 | ['cmd_prefix', 'cmd_word', 'cmd_suffix'] |
| 43 | RED_IN | shift | 3 | ['cmd_prefix', 'cmd_word', 'cmd_suffix'] |
| 43 | RED_OUT | shift | 4 | ['cmd_prefix', 'cmd_word', 'cmd_suffix'] |
| 43 | HERE_DOC | shift | 5 | ['cmd_prefix', 'cmd_word', 'cmd_suffix'] |
| 43 | APPEND | shift | 6 | ['cmd_prefix', 'cmd_word', 'cmd_suffix'] |
| 43 | -1 | reduce | simple_command | -1 |
| 43 | io_redirect | go to state 42 | 42 | -1 |
| 43 | io_file | go to state 15 | 15 | -1 |
| 43 | io_here | go to state 16 | 16 | -1 |
| 44 | PIPE | shift | 26 | ['and_or', 'AND', 'pipe_sequence'] |
| 44 | -1 | reduce | and_or | -1 |
| 45 | PIPE | shift | 26 | ['and_or', 'OR', 'pipe_sequence'] |
| 45 | -1 | reduce | and_or | -1 |
