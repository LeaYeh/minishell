%token  WORD
%token  ASSIGNMENT_WORD
/*       '='     */
%token  RED_IN
/*       '<'     */
%token  RED_OUT
/*       '>'     */
%token  PIPE
/*       '|'     */
%token  HERE_DOC
/*       '<<'     */
%token  APPEND
/*       '>>'     */
%token  AND    OR
/*      '&&'  '||'   */
%token  L_BRACKET    R_BRACKET
/*          '('         ')'   */

%start pipe_sequence
%%

pipe_sequence	: command 
				| pipe_sequence PIPE command
				;
and_or          :            pipe_sequence
                | and_or AND pipe_sequence
                | and_or OR  pipe_sequence
                ;
subshell        : L_BRACKET pipe_sequence R_BRACKET
                | L_BRACKET and_or R_BRACKET
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
io_file			: RED_OUT filename
				| RED_IN  filename
				| APPEND  filename
				;
filename		: WORD
				;
io_here			: HERE_DOC here_end
				;
here_end		: WORD
				;