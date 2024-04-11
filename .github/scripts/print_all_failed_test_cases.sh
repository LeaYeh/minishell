#!/bin/bash

TEST_OUTPUT=$(cat "$RESULT_FILE")
RESULT=0

# Extract line numbers and file paths from test output
while IFS= read -r line; do
  if [[ $line == *"❌"* ]]; then
    echo "$line"
    test_number=$(echo "$line" | grep -oP '\d+' | head -1 || true)
    line_number=$(echo "$line" | grep -oP '\d+' | tail -1 || true)
    file_path=$(echo "$line" | grep -oP '\s*'"$HOME"'/42_minishell_tester/cmds/.*\.sh' || true)
    file_basename=$(basename "${file_path%.*}")
    file_dirname=$(basename $(dirname "$file_path"))
  fi

  # Print test case
  if [[ -n $line_number && -n $file_path ]]; then
    echo -e "\e[0;94m---------------------------------------------------------------------------------\e[1;97m"
    echo -e "\e[1;94mTEST CASE $test_number FROM $file_dirname/$file_basename AT LINE $line_number:\e[1;97m"
    sed -n "${line_number},\$p" "$file_path" | awk 'NF {p=1} !NF {if(p) exit} {if(p) print}'
    echo -e "\e[0;94m---------------------------------------------------------------------------------\e[1;97m"

    # Print stdout and stderr outputs
    for output_type in stdout stderr; do
      for shell_type in minishell bash; do
        output_file_name="${output_type}_${shell_type}_${test_number}"
        output_file="./tester_output/${file_dirname}/${file_basename}/$output_file_name"
        if [[ -f $output_file ]]; then
          echo -e "\e[1;91m${output_type^^} OF ${shell_type^^}:\e[1;97m"
          cat "$output_file"
          echo -e "\e[0;91m---------------------------------------------------------------------------------\e[1;97m"
        fi
      done
    done
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
