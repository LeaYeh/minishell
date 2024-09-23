#!/bin/bash

diff_output=$(diff "$TARGET_LOG_FILE" "$SOURCE_LOG_FILE" || true)

# Extract line numbers and file paths from diff output
while IFS= read -r line; do
  if [[ $line == "<"* ]]; then
    echo -e "\001\e[94m\002🎯 Target branch: $line\001\e[0m\002"
  elif [[ $line == ">"* ]]; then
    echo -e "\001\e[93m\002🌱 Source branch: $line\001\e[0m\002"
    export LINE="$line"
    "$SCRIPTS_DIR/print_test_case.sh"
  fi
done <<< "$diff_output"

# Exit with error code if there are differences
if [[ -n $diff_output ]]; then
  exit 1
else
  exit 0
fi
