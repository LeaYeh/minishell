#!/bin/bash

diff_output=$(diff "$HOME/target_test_result.txt" "$HOME/source_test_result.txt" || true)

# Extract line numbers and file paths from diff output
while IFS= read -r line; do
  if [[ $line == "<"* ]]; then
    echo -e "\e[94m🎯 Target branch: $line\e[0m"
  elif [[ $line == ">"* ]]; then
    echo -e "\e[93m🌱 Source branch: $line\e[0m"
    export LINE="$line"
    "$HOME/print_test_case.sh"
  fi
done <<< "$diff_output"

# Exit with error code if there are differences
if [[ -n $diff_output ]]; then
  exit 1
else
  exit 0
fi
