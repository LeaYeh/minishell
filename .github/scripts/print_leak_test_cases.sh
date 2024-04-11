#!/bin/bash

TEST_OUTPUT=$(cat "$RESULT_FILE")
LEAKS=0
RESULT=0

# Extract line numbers and file paths from test output
while IFS= read -r line; do
  stripped_line=$(echo "$line" | sed 's/\x1b\[[0-9;]*m//g')
  if [[ $stripped_line == *"LEAKS: ❌"* ]]; then
    echo "$line"
    "$HOME/print_test_case.sh" -v "$line"
    ((LEAKS++))
  fi

  # Check for the start of the result block and set the flag
  if [[ $line =~ ^\s*[🏁]+\s*$ ]]; then
    RESULT=1
  fi
  # If the flag is set, print the line
  if [[ $RESULT -ne 0 ]]; then
    echo "$line"
  fi
done <<< "$TEST_OUTPUT"

if [[ $LEAKS -ne 0 ]] ; then
  exit 1
else
  exit 0
fi
