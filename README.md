# 🌊rash Minishell | @42Vienna

This project goes beyond merely crafting a new shell from scratch; it endeavors to emulate the Bash source code and the GNU Bash POSIX manual while incorporating principles from compiler parsing. By referencing these authoritative sources, the project aims to meticulously implement a shell interpreter. Moreover, it documents the entire journey from ground zero to the creation of a personalized shell, serving as a valuable resource for future learners seeking insights into shell development.

# Table of Contents

* [Support Features](#support-features)
* [The Challenges](#the-challenges)
    * [How Does Bash Work](#how-does-bash-work)
    * What Should You Know Before Suffering in Corner Cases Hell
* [Implementations](#implementations)
    * [Frontend](#frontend)
        * Lexer
        * Parser
            * Why We Decide to Use `Shift-Reduce` as Parsing Algorithm
    * [Backend](#backend)
        * Executor
        * Builtins
        * Redirection
    * [Cross-end](#cross-end)
        * Expander
        * Signal
            * Exception Handling
            * Signal Handling
    * DevOPS Spirit
        * Basic cowork flow and git command


# Support Features

| Category   | Module      | Function               | Requirement                                                                                              | Status |
|------------|-------------|------------------------|----------------------------------------------------------------------------------------------------------|--------|
| Frontend   | Lexer       | Tokenizing             | Tokenized user input into token list.                                                                    | ✅      |
|            |             |                        | Support the `PIPE` character `\|`.                                                                       | ✅      |
|            |             |                        | Support logical `AND` `&&`.                                                                              | ✅      |
|            |             |                        | Support logical `OR` `\|\|`.                                                                             | ✅      |
|            |             |                        | Support left and right brackets `()` for `SUBSHELL`.                                                     | ✅      |
|            |             |                        | Support `WORD` representing basic words.                                                                 | ✅      |
|            |             |                        | Support `ASSIGNMENT_WORD` `=` for variable assignments.                                                   | ✅      |
| Frontend   | Parser      | Syntax Analysis        | Analyze syntax of token list and report syntax errors based on Shift-Reduce algorithm with predefined grammar rules and then output as command table list. | ✅      |
| Frontend   | Expander    | Brace Expansion        | Perform brace expansion to generate multiple strings based on expressions enclosed in braces `{}`.      | ✅      |
|            |             | Tilde Expansion        | Perform tilde expansion to replace `~` with the current user's home directory path.                      | ❌      |
|            |             | Parameter Expansion    | Perform parameter expansion to replace variables and special parameters in a string.                     | ✅      |
|            |             | Command Substitution   | Perform command substitution to replace command output in a string.                                      | ❌      |
|            |             | Arithmetic Expansion   | Perform arithmetic expansion to evaluate mathematical expressions enclosed in `$(())`.                    | ❌      |
|            |             | Process Substitution   | Perform process substitution to use the output of a command as a file or input to another command.        | ❌      |
|            |             | Word Splitting         | Perform word splitting to split a string into separate words based on spaces, tabs, and newlines.        | ✅      |
|            |             | Wildcard Expansion     | Perform filename expansion (globbing) to generate filenames matching a specified pattern.                | ❌      |
|            |             | Quote Removal          | Remove quotes from strings to interpret them as literal values.                                           | ✅      |
| Backend    | Builtins    | cd                     | Implement `cd` with only a relative or absolute path.                                                    | ✅      |
|            |             | echo                   | Implement `echo` with option `-n`.                                                                      | ✅      |
|            |             | env                    | Implement `env` with no options or arguments.                                                            | ✅      |
|            |             | exit                   | Implement `exit` with no options.                                                                        | ✅      |
|            |             | export                 | Implement `export` with no options.                                                                      | ✅      |
|            |             | pwd                    | Implement `pwd` with no options.                                                                         | ✅      |
|            |             | unset                  | Implement `unset` with no options.                                                                       | ✅      |
| Backend    | Redirection | IO Redirection         | Redirected `STDIN` with input redirection by `<` operator.                                              | ✅      |
|            |             |                        | Redirected `HEREDOC` with input redirection by `<<` operator.                                             | ✅      |
|            |             |                        | Redirected `STDOUT` with output redirection by `>` operator.                                              | ✅      |
|            |             |                        | Redirected `STDOUT` append with output redirection by `>>` operator.                                      | ✅      |
|            |             | Subsell Redirection    | Implement redirections and pipes (\| character).                                                         | ✅      |
|            |             | Pipe Redirection       | Redirected `STDIN`/`STDOUT` by `pipe()`.                                                                 | ✅      |
| Cross-end  | Signal      | Signal Handling        | Handled `ctrl-C` as `SIGINT` as bash behavior.                                                           | ✅      |
|            |             |                        | Handled `ctrl-D` as `EOF` as bash behavior.                                                              | ✅      |
|            |             |                        | Handled `ctrl-\\` as `SIGQUIT` as bash behavior.                                                         | ✅      |
|            |             | Exception Handling     | Ignored `SIGPIPE` in internal process and set it back as default in external commands sub-process.       | ✅      |
|            |             |                        | Used `SIGABRT` and `SIGTERM` to raise internal critical error to all related process and handle it depends on scenario.       | ✅      |


# The Challenges

## How Does Bash Work

## What Should You Know Before Suffering in Corner Cases Hell

[Bash Manual](!https://www.gnu.org/software/bash/manual/html_node/index.html) Is All You Need

# Implementations

## Frontend

### Lexer

Tokenizes the user input `command string` into a `tokens list`.

> In the Lexer module, we solely perform tokenization without any syntax checking.

#### Support `Token` Types

In addition to the mandatory parts, in this project, we implemented all functionalities of subshell and AND OR operators as per the Bash POSIX manual.

* `END`: This token type represents the end of the input string or the end of a command. It indicates that there are no more tokens to process.
* `NONE`: This token type is used to signify an undefined or invalid token. It may indicate an error in the lexer or parser.
* `WORD`: This token type is used for general words in the command, such as command names, arguments, or parameters. It encompasses alphanumeric characters and some special characters.
* `ASSIGNMENT_WORD`: This token type is used for assignment words, which typically occur in variable assignments. For example, in the command VAR=value, VAR is an assignment word.
* `RED_IN`: This token type represents input redirection, indicating that the command should read input from a file specified in the command.
* `RED_OUT`: This token type represents output redirection, indicating that the command should write output to a file specified in the command.
* `PIPE`: This token type represents a pipe, which is used to redirect the output of one command as input to another command.
* `HERE_DOC`: This token type represents a "here document" redirection, which allows providing input to a command inline within the script or command.
* `APPEND`: This token type represents append redirection, indicating that the output should be appended to a file rather than overwriting it.
* `OR`: This token type represents the logical OR operator, typically used in conditional statements or command chaining.
* `AND`: This token type represents the logical AND operator, also used in conditional statements or command chaining.
* `L_BRACKET`: This token type represents a left bracket, which may be used to denote the start of a group or condition in certain contexts.
* `R_BRACKET`: This token type represents a right bracket, used to denote the end of a group or condition in corresponding contexts.

### Parser

Analyzes the token list generated by the Lexer, identifies syntax errors, and produces either an Abstract Syntax Tree (AST) or a list of command tables as output.

> In the parser stage, **we deliberately avoid performing any expansion**. This decision is made to prevent incorrect behavior that may arise due to expansion at this stage. Expansion involves processes such as variable expansion, command substitution, arithmetic expansion, and pathname expansion, which can significantly alter the structure of the input command. Performing expansion at this early stage could lead to misinterpretation of the command's structure, potentially resulting in errors or unexpected behavior during parsing and subsequent execution. Therefore, expansion is deferred to later stages in the shell processing pipeline where it can be executed accurately within the appropriate context.

#### Why We Choose `Shift-Reduced` as Parsing Algorithm?

In our custom parser, we have opted to use the shift-reduce parsing algorithm. We believe this choice provides an excellent opportunity to delve into compiler frontend development. This algorithm is widely applicable in implementing frontends for various programming languages. One of the advantages of using the shift-reduce algorithm is that it avoids handling syntax error cases individually. When the parsing table cannot find a corresponding action for the current state and symbol, it signifies an error message. This approach not only simplifies the implementation process but also helps in understanding how compilers handle syntax parsing efficiently.

Moreover, by implementing a shift-reduce parser, we gain insights into fundamental concepts such as tokenization, grammar rules, parsing tables, and error handling mechanisms. This knowledge can be applied not only to shell scripting but also to the development of compilers for other languages. Through this project, we aim to provide a hands-on learning experience in compiler frontend development, fostering a deeper understanding of language processing techniques.

#### How `Shift-Reduced` Algorithm Works?

The shift-reduce parsing algorithm is a type of bottom-up parsing technique commonly used in the development of compiler frontends. It operates by shifting input tokens onto a stack until a reduction rule can be applied. Here's how it works:
* Input Tokens: The algorithm starts with a sequence of input tokens to be parsed, typically generated by the lexer.
* Stack: It maintains a stack to keep track of the tokens and partial parse trees during the parsing process.
* Shift Operation: During the shift operation, the algorithm takes the next token from the input sequence and pushes it onto the stack. This process continues until a reduction can be applied.
* Reduce Operation: When a reduction is possible, the algorithm applies a production rule to a portion of the stack. This involves popping a set of tokens from the stack and replacing them with a non-terminal symbol that represents a higher-level construct in the grammar.
* Parsing Table: The decision to shift or reduce is guided by a parsing table constructed based on the grammar rules of the language. This table determines the action to be taken based on the current state of the stack and the next input token.
* Error Handling: If the parsing table cannot find a valid action for the current state and input token, it indicates a syntax error, and the parser may attempt error recovery strategies such as discarding tokens or inserting missing tokens to continue parsing.
* Accept: The parsing process continues until the entire input sequence is processed, and the stack contains a single parse tree representing the input according to the grammar rules.
* Output: Finally, the parser may generate an abstract syntax tree (AST) or perform additional semantic analysis based on the parse tree to further process the input.

Overall, the shift-reduce parsing algorithm efficiently constructs a parse tree by iteratively shifting input tokens onto a stack and applying reduction rules based on the grammar of the language. It's widely used due to its simplicity and effectiveness in parsing context-free grammars.

Reference: https://github.com/twagger/minishell

![shift_reduce_alg](doc/images/shift_reduce_alg.png)

#### Do I Really Need a AST tree or Command Table List?

`AST tree`:
An Abstract Syntax Tree (AST) is useful for representing the hierarchical structure of a program or command, aiding in semantic analysis, optimization, and code generation.

`Command Table List`:
A Command Table List organizes parsed commands for execution, simplifying processing and facilitating error checking and debugging.

If you don't need to implement subshell functionality, the structure of a Command Table List is sufficient for your requirements. However, if handling hierarchical information is necessary, choosing an AST can significantly reduce complexity. We regret opting for a Command Table List, as it made our subprocess flow design less elegant.

![crash_cmd_table](doc/images/crash_cmd_table.png)

Reference: https://www.cs.purdue.edu/homes/grr/SystemsProgrammingBook/Book/Chapter5-WritingYourOwnShell.pdf
![cmd_table](doc/images/cmd_table.png)

##### How to Generate Parsing Table

Pre-requirement: GNU M4 1.4 and bison, [check here](https://chat.openai.com/share/06ff7af8-0ab0-477e-a2e9-aa095199a704).

1. Design parsing rule, look more detail in our [parsing rule](meta/parsing_rule.bnf).
2. Use `bison` tool to generate parsing table by the rules, and check your output `<PARSING_RULES>`.output

```
> bison -v <PARSING_RULES>.y
```

> check our parsing rules [here](meta/parsing%20rules/index.md) (ref: [online BNF generator](https://www.bottlecaps.de/rr/ui))

> use online tool to check input command parsing tree with BNF [here](http://lab.antlr.org/).

3. Convert [parsing table](meta/parsing_rule.output) for `Shift-Reduce` algorithm.
    - We have implemented a [simple converter](meta/gen_action_table.py) in Python to transform `parsing_rule.output` into a table suitable for referencing in code.

## Backend

### Executor
### Builtins
### Redirection

## Cross-end

### Expander

### Signal

# DevOPS Spirit

## Basic Cowork Flow and Git Command

### Git Workflow

We choose `Feature Branching Git Workflow` as our cowork flow in the project.

![Diagram](doc/images/gitflow.png)

#### Step 0.

Checkout to main branch to pull the latest update.

```
> git checkout main
> git pull
```

#### Step 1.

Create new feature branch for each feature, the feature develop life cycle should be around hours work.

```
> git checkout -b feat-<NAME>
```

#### Step 2.

After your work, checkout back to the main branch and align with the latest version again. Then checkout to feature branch and rebase with main branch.

```
> git checkout main
> git pull

> git checkout feat-<NAME>
> git rebase main
```

#### Step 2.a

No confiliction happend! Go to the Step 3.

#### Step 2.b

Occur confiliction when rebase...

1. First, git will pause the rebase and allow you to fix the conflict. You can see which files contain conflicts by running git status.

2. Open the file with conflicts. Git marks conflicts in the source code with <<<<<<<, =======, and >>>>>>>. The code between <<<<<<< and ======= is your local changes and the code between ======= and >>>>>>> is the incoming changes. You need to manually edit the file to resolve the conflict.

3. After you've resolved the conflict, you need to add the resolved files to the staging area and continue the rebase process.

```
> git add <filename>
> git rebase --continue
```

#### Step 3

Push the feature branch to the remote repository branch
PS: Because we use `rebase` to change the history, so it's necessary force push.

```
> git push origin feat-<NAME> --force
```

#### Step 4

Make a pull request and wait for the review and merge by your pear.

### Shared Google Doc

[Link](https://docs.google.com/document/d/1zbVAnrPLIJIaJ28Th6ddv0U3SJ_CSCF7k0x34StQpSE/edit)
