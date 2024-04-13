#!/bin/bash

test_output=$(cat "$RESULT_FILE")
result=0

# Extract line numbers and file paths from test output
while IFS= read -r line; do
  if [[ $line == *"❌"* ]]; then
    echo "$line"
    export LINE="$line"
    "$HOME/print_test_case.sh"
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
