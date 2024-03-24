# 🌊rash Minishell | @42Vienna

This project aims to not only provide a functional shell interpreter but also serve as a learning platform where users can grasp the intricacies of shell scripting, parsing, and execution. By adopting principles akin to those of an interpreter or compiler, this project offers a unique perspective on shell development and empowers users to navigate through the complexities of system interaction with confidence.

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
| Backend    | Redirection | IO Redirection         | Redirected 'STDIN' with input redirection by '<' operator.                                              | ✅      |
|            |             |                        | Redirected 'HEREDOC' with input redirection by '<<' operator.                                             | ✅      |
|            |             |                        | Redirected 'STDOUT' with output redirection by '>' operator.                                              | ✅      |
|            |             |                        | Redirected 'STDOUT' append with output redirection by '>>' operator.                                      | ✅      |
|            |             | Subsell Redirection    | Implement redirections and pipes (\| character).                                                         | ✅      |
|            |             | Pipe Redirection       | Redirected 'STDIN'/'STDOUT' by 'pipe()'.                                                                 | ✅      |
| Cross-end  | Signal      | Signal Handling        | Handled 'ctrl-C' as 'SIGINT' as bash behavior.                                                           | ✅      |
|            |             |                        | Handled 'ctrl-D' as 'EOF' as bash behavior.                                                              | ✅      |
|            |             |                        | Handled 'ctrl-\\' as 'SIGQUIT' as bash behavior.                                                         | ✅      |
|            |             | Exception Handling     | Ignored 'SIGPIPE' in internal process and set it back as default in external commands sub-process.       | ✅      |
|            |             |                        | Used 'SIGABRT' and 'SIGTERM' to raise internal critical error to all related process and handle it depends on scenario.       | ✅      |


# The Challenges

## How Does Bash Work

## What Should You Know Before Suffering in Corner Cases Hell

[Bash Manual](!https://www.gnu.org/software/bash/manual/html_node/index.html) Is All You Need

# Implementations

## Frontend

### Lexer

### Parser

#### Generate parsing table

Pre-requirement: GNU M4 1.4 and bison, [check here](https://chat.openai.com/share/06ff7af8-0ab0-477e-a2e9-aa095199a704).

1. Design parsing rule, look more detail in our [parsing rule](data/parsing_rule.y).
    - TODO: need to check rule about expandtion nearby redirect.
        * ... (some examples...)
2. Use `bison` tool to generate parsing table by the rules, and check your output `<PARSING_RULES>`.output

```
> bison -v <PARSING_RULES>.y
```

> check our parsing rules [here](data/parsing%20rules/index.md) (ref: [online BNF generator](https://www.bottlecaps.de/rr/ui))

> use online tool to check input command parsing tree with BNF [here](http://lab.antlr.org/).

3. Convert parsing table to fit your data structure

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

![Diagram](data/images/gitflow.png)

#### Step 0.

Checkout to main branch to pull the latest update.

```
> git checkout main
> git pull
```

#### bison -v parsing_rule.yStep 1.

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
