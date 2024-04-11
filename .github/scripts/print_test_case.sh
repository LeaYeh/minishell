#!/bin/bash

print_output()
{
  local output_type=$1
  local file_minishell="${output_file_path}/${output_type}_minishell_${test_number}"
  local file_bash="${output_file_path}/${output_type}_bash_${test_number}"

  # Print diff of output between bash and minishell
  if [[ -f $file_minishell && -f $file_bash ]]; then
    echo -e "\e[1;36mDIFF OF \e[1;34m${output_type^^}\e[1;36m BETWEEN BASH AND MINISHELL:\e[1;97m"
    diff -u0 --color=always "$file_bash" "$file_minishell"
    echo -e "\e[0;36m---------------------------------------------------------------------------------\e[1;97m"
  fi
  # Print output of minishell
  if [[ -f $file_minishell ]]; then
    echo -e "\e[1;91m${output_type^^} OF MINISHELL:\e[1;97m"
    cat "$file_minishell"
    echo -e "\e[0;91m---------------------------------------------------------------------------------\e[1;97m"
  fi
  # Print output of bash
  if [[ -f $file_bash ]]; then
    echo -e "\e[1;92m${output_type^^} OF BASH:\e[1;97m"
    cat "$file_bash"
    echo -e "\e[0;92m---------------------------------------------------------------------------------\e[1;97m"
  fi
}

line=$1
test_number=$(echo "$line" | grep -oP '\d+(?=:)' | head -1 || true)
line_number=$(echo "$line" | grep -oP '\d+' | tail -1 || true)
file_path=$(echo "$line" | grep -oP '\s*'"$HOME"'/42_minishell_tester/cmds/.*\.sh' || true)
file_basename=$(basename "${file_path%.*}")
file_dirname=$(basename "$(dirname "$file_path")")
output_file_path="./tester_output/${file_dirname}/${file_basename}"

if [[ -n $line_number && -n $file_path ]]; then
  # Print test case
  echo -e "\e[0;93m---------------------------------------------------------------------------------\e[1;97m"
  echo -e "\e[1;93mTEST CASE $test_number FROM $file_dirname/$file_basename AT LINE $line_number:\e[1;97m"
  sed -n "${line_number},\$p" "$file_path" | awk 'NF {p=1} !NF {if(p) exit} {if(p) print}'
  echo -e "\e[0;93m---------------------------------------------------------------------------------\e[1;97m"

  for output_type in stdout stderr; do
    print_output $output_type
  done

  echo -e "\e[1;95m=================================================================================\e[0m"
fi
