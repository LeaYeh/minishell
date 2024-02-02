#!/bin/bash

DIFF_OUTPUT=$(diff $HOME/target_test_result.txt $HOME/source_test_result.txt || true)

# Extract line numbers and file paths from diff output
while IFS= read -r line; do
  if [[ $line == "<"* ]]; then
    echo -e "\e[94mTarget branch: $line\e[0m"
  elif [[ $line == ">"* ]]; then
    echo -e "\e[93mSource branch: $line\e[0m"
    line_number=$(echo "$line" | grep -oP '\d+' | tail -1 || true)
    file_path=$(echo "$line" | grep -oP '\s*'"$HOME"'/42_minishell_tester/cmds/.*\.sh' || true)
  fi

  # Print test case
  if [[ -n $line_number && -n $file_path ]]; then
    echo -e "\e[93m----------------------------------------\e[1;97m"
    sed -n "${line_number},\$p" "$file_path" | awk 'NF {p=1} !NF {if(p) exit} {if(p) print}'
    echo -e "\e[0;93m---------------------------------------------------------------------------------\e[0m"
  fi

  line_number=""
  file_path=""
done <<< "$DIFF_OUTPUT"

# Exit with error code if there are differences
if [[ -n $DIFF_OUTPUT ]]; then
  exit 1
else
  exit 0
fi
