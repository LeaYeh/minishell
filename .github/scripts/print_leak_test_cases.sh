#!/bin/bash

TEST_OUTPUT=$(cat "$RESULT_FILE")
LEAKS=0
RESULT=0

# Extract line numbers and file paths from test output
while IFS= read -r line; do
  stripped_line=$(echo "$line" | sed 's/\x1b\[[0-9;]*m//g')
  if [[ $stripped_line == *"LEAKS: ❌"* ]]; then
    echo "$line"
    line_number=$(echo "$line" | grep -oP '\d+' | tail -1 || true)
    file_path=$(echo "$line" | grep -oP '\s*'"$HOME"'/42_minishell_tester/cmds/.*\.sh' || true)
    ((LEAKS++))
  fi

  # Print test case
  if [[ -n $line_number && -n $file_path ]]; then
    echo -e "\e[91m---------------------------------------------------------------------------------\e[1;97m"
    sed -n "${line_number},\$p" "$file_path" | awk 'NF {p=1} !NF {if(p) exit} {if(p) print}'
    echo -e "\e[0;91m=================================================================================\e[0m"
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

if [[ $LEAKS -ne 0 ]] ; then
  exit 1
else
  exit 0
fi
