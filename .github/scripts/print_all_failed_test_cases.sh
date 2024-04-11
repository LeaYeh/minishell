#!/bin/bash

TEST_OUTPUT=$(cat "$RESULT_FILE")
RESULT=0

# Extract line numbers and file paths from test output
while IFS= read -r line; do
  if [[ $line == *"❌"* ]]; then
    echo "$line"
    test_number=$(echo "$line" | grep -oP '\d+(?=:)' | head -1 || true)
    line_number=$(echo "$line" | grep -oP '\d+' | tail -1 || true)
    file_path=$(echo "$line" | grep -oP '\s*'"$HOME"'/42_minishell_tester/cmds/.*\.sh' || true)
    file_basename=$(basename "${file_path%.*}")
    file_dirname=$(basename $(dirname "$file_path"))
    output_file_path="./tester_output/${file_dirname}/${file_basename}"
  fi

  # Print test case
  if [[ -n $line_number && -n $file_path ]]; then
    echo -e "\e[0;93m---------------------------------------------------------------------------------\e[1;97m"
    echo -e "\e[1;93mTEST CASE $test_number FROM $file_dirname/$file_basename AT LINE $line_number:\e[1;97m"
    sed -n "${line_number},\$p" "$file_path" | awk 'NF {p=1} !NF {if(p) exit} {if(p) print}'
    echo -e "\e[0;93m---------------------------------------------------------------------------------\e[1;97m"

    stdout_file_minishell="${output_file_path}/stdout_minishell_${test_number}"
    stdout_file_bash="${output_file_path}/stdout_bash_${test_number}"
    stderr_file_minishell="${output_file_path}/stderr_minishell_${test_number}"
    stderr_file_bash="${output_file_path}/stderr_bash_${test_number}"

    # Print diff of stdout between bash and minishell
    if [[ -f $stdout_file_minishell && -f $stdout_file_bash ]]; then
      echo -e "\e[1;36mDIFF OF \e[1;34mSTDOUT\e[1;36m BETWEEN BASH AND MINISHELL:\e[1;97m"
      diff -u0 --color=always "$stdout_file_bash" "$stdout_file_minishell"
      echo -e "\e[0;36m---------------------------------------------------------------------------------\e[1;97m"
    fi
    # Print stdout of minishell
    if [[ -f $stdout_file_minishell ]]; then
      echo -e "\e[1;91mSTDOUT OF MINISHELL:\e[1;97m"
      cat "$stdout_file_minishell"
      echo -e "\e[0;91m---------------------------------------------------------------------------------\e[1;97m"
    fi
    # Print stdout of bash
    if [[ -f $stdout_file_bash ]]; then
      echo -e "\e[1;92mSTDOUT OF BASH:\e[1;97m"
      cat "$stdout_file_bash"
      echo -e "\e[0;92m---------------------------------------------------------------------------------\e[1;97m"
    fi
    # Print diff of stderr between bash and minishell
    if [[ -f $stderr_file_minishell && -f $stderr_file_bash ]]; then
      echo -e "\e[1;36mDIFF OF \e[1;33mSTDERR\e[1;36m BETWEEN BASH AND MINISHELL:\e[1;97m"
      diff -u0 --color=always "$stderr_file_bash" "$stderr_file_minishell"
      echo -e "\e[0;36m---------------------------------------------------------------------------------\e[1;97m"
    fi
    # Print stderr of minishell
    if [[ -f $stderr_file_minishell ]]; then
      echo -e "\e[1;91mSTDERR OF MINISHELL:\e[1;97m"
      cat "$stderr_file_minishell"
      echo -e "\e[0;91m---------------------------------------------------------------------------------\e[1;97m"
    fi
    # Print stderr of bash
    if [[ -f $stderr_file_bash ]]; then
      echo -e "\e[1;92mSTDERR OF BASH:\e[1;97m"
      cat "$stderr_file_bash"
      echo -e "\e[0;92m---------------------------------------------------------------------------------\e[1;97m"
    fi
    echo -e "\e[1;95m=================================================================================\e[0m"
  fi

  # Check for the start of the result block and set the flag
  if [[ $line =~ ^\s*[🏁]+\s*$ ]]; then
    RESULT=1
  fi
  # If the flag is set, print the line
  if [[ $RESULT -ne 0 ]]; then
    echo "$line"
  fi

  line_number=""
  file_path=""
done <<< "$TEST_OUTPUT"
