#!/bin/bash

test_log=$(cat "$LOG_FILE")
result=0
failed=0

# Check for options
#   `-v` to check for leaks and print valgrind output
#   `-c` to check for crashes
#   No option to check for any fail and print stdout and stderr output
if echo "$*" | grep -q '\-.*v'; then
  option="-v"
  pattern="LEAKS: ❌"
elif echo "$*" | grep -q '\-.*c'; then
  option="-c"
  pattern="CRASH: ❌"
else
  option=""
  pattern="❌"
fi

# Extract line numbers and file paths from test log
while IFS= read -r line; do
  # Strip ANSI colors for consistent pattern matching
  stripped_line=$(echo "$line" | sed 's/\x1b\[[0-9;]*m//g')

  # Check for the pattern and print the line and test case
  if [[ $stripped_line == *"$pattern"* ]]; then
    echo "$line"
    export LINE="$line"
    "$SCRIPTS_DIR/print_test_case.sh" $option
    ((failed++))
  fi

  # Check for the start of the result block and set the flag
  if [[ $line =~ ^\s*[🏁]+\s*$ ]]; then
    result=1
  fi
  # If the flag is set, print the line
  if [[ $result -ne 0 ]]; then
    echo "$line"
  fi
done <<< "$test_log"

if [[ -n $option && $failed -ne 0 ]]; then
  exit 1
else
  exit 0
fi
