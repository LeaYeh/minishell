#!/bin/bash

TEST_OUTPUT=$(cat "$RESULT_FILE")
RESULT=0

# Extract line numbers and file paths from test output
while IFS= read -r line; do
  if [[ $line == *"❌"* ]]; then
    echo "$line"
    "$HOME/print_test_case.sh" "$line" "$TESTER_OUTPUT_DIR"
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
