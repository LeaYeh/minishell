#!/bin/bash

TEST_OUTPUT=$(cat "$RESULT_FILE")

# Extract line numbers and file paths from test output
while IFS= read -r line; do
  stripped_line=$(echo "$line" | sed 's/\x1b\[[0-9;]*m//g')
  if [[ $stripped_line == *"LEAKS: ❌"* ]]; then
    echo "$line"
    line_number=$(echo "$line" | grep -oP '\d+' | tail -1 || true)
    file_path=$(echo "$line" | grep -oP '\s*'"$HOME"'/42_minishell_tester/cmds/.*\.sh' || true)
  fi

  # Print test case
  if [[ -n $line_number && -n $file_path ]]; then
    echo -e "\e[91m---------------------------------------------------------------------------------\e[1;97m"
    sed -n "${line_number},\$p" "$file_path" | awk 'NF {p=1} !NF {if(p) exit} {if(p) print}'
    echo -e "\e[0;91m=================================================================================\e[0m"
  fi

  line_number=""
  file_path=""
done <<< "$TEST_OUTPUT"
