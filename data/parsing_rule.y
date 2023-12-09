%token  WORD
%token  ASSIGNMENT_WORD
/*       '='     */
%token  RET_IN
/*       '<'     */
%token  RET_OUT
/*       '>'     */
%token  PIPE
/*       '|'     */
%token  HERE_DOC
/*       '<<'     */
%token  APPEND
/*       '>>'     */
%token  AND    OR
/*      '&&'  '||'   */

%start pipe_sequence
%%

pipe_sequence	: command 
				| pipe_sequence PIPE command
				;
and_or          :            pipe_sequence
                | and_or AND pipe_sequence
                | and_or OR  pipe_sequence
                ;
subshell        : '(' and_or ')'
                ;
command         : simple_command
                | subshell
                | subshell redirect_list
                ;
redirect_list   :               io_redirect
                | redirect_list io_redirect
                ;
simple_command	: cmd_prefix cmd_word cmd_suffix
				| cmd_prefix cmd_word
				| cmd_prefix
				| cmd_name cmd_suffix
				| cmd_name
				;
cmd_name		: WORD
				;
cmd_word		: WORD
				;
cmd_prefix		:            io_redirect
				| cmd_prefix io_redirect
                |            ASSIGNMENT_WORD
                | cmd_prefix ASSIGNMENT_WORD
				;
cmd_suffix		:            io_redirect
				| cmd_suffix io_redirect
				|            WORD
				| cmd_suffix WORD
				;
io_redirect		: io_file
				| io_here
				;
io_file			: RET_OUT filename
				| RET_IN  filename
				| APPEND  filename
				;
filename		: WORD
				;
io_here			: HERE_DOC here_end
				;
here_end		: WORD
				;