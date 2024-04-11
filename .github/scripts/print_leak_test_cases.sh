#!/bin/bash

test_output=$(cat "$RESULT_FILE")
leaks=0
result=0

# Extract line numbers and file paths from test output
while IFS= read -r line; do
  stripped_line=$(echo "$line" | sed 's/\x1b\[[0-9;]*m//g')
  if [[ $stripped_line == *"LEAKS: ❌"* ]]; then
    echo "$line"
    export LINE="$line"
    "$HOME/print_test_case.sh" -v
    ((leaks++))
  fi

  # Check for the start of the result block and set the flag
  if [[ $line =~ ^\s*[🏁]+\s*$ ]]; then
    result=1
  fi
  # If the flag is set, print the line
  if [[ $result -ne 0 ]]; then
    echo "$line"
  fi
done <<< "$test_output"

if [[ $leaks -ne 0 ]] ; then
  exit 1
else
  exit 0
fi
