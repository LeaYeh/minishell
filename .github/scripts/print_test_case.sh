#!/bin/bash

test_number=$(echo "$LINE" | grep -oP '\d+(?=:)' | head -1 || true)
line_number=$(echo "$LINE" | grep -oP '\d+' | tail -1 || true)
file_path=$(echo "$LINE" | grep -oP '\s*'"$HOME"'/42_minishell_tester/cmds/.*\.sh' || true)
file_basename=$(basename "${file_path%.*}")
file_dirname=$(basename "$(dirname "$file_path")")
output_file_path="${TESTER_OUTPUT_DIR}/${file_dirname}/${file_basename}"

print_output()
{
  local output_type=$1
  local file_minishell="${output_file_path}/${output_type}_minishell_${test_number}"
  local file_bash="${output_file_path}/${output_type}_bash_${test_number}"

  # Print diff of output between bash and minishell
  if [[ -f $file_minishell && -f $file_bash ]]; then
    echo -e "\e[0;36m---------------------------------------------------------------------------------\e[1;97m"
    if [[ $output_type == "stdout" ]]; then
      echo -e "\e[1;36mDIFF OF \e[1;34m${output_type^^}\e[1;36m BETWEEN BASH AND MINISHELL:\e[1;97m"
    elif [[ $output_type == "stderr" ]]; then
      echo -e "\e[1;36mDIFF OF \e[1;33m${output_type^^}\e[1;36m BETWEEN BASH AND MINISHELL:\e[1;97m"
    fi
    diff -u0 --color=always "$file_bash" "$file_minishell"
    echo -e "\e[0;36m---------------------------------------------------------------------------------\e[1;97m"
  fi
  # Print output of minishell
  if [[ -f $file_minishell ]]; then
    echo -e "\e[0;91m---------------------------------------------------------------------------------\e[1;97m"
    echo -e "\e[1;91m${output_type^^} OF MINISHELL:\e[1;97m"
    cat "$file_minishell"
    echo -e "\e[0;91m---------------------------------------------------------------------------------\e[1;97m"
  fi
  # Print output of bash
  if [[ -f $file_bash ]]; then
    echo -e "\e[0;92m---------------------------------------------------------------------------------\e[1;97m"
    echo -e "\e[1;92m${output_type^^} OF BASH:\e[1;97m"
    cat "$file_bash"
    echo -e "\e[0;92m---------------------------------------------------------------------------------\e[1;97m"
  fi
}

print_valgrind_output()
{
  local file_valgrind="${output_file_path}/valgrind_out_${test_number}"

  # Print valgrind output
  if [[ -f $file_valgrind ]]; then
    echo -e "\e[0;91m---------------------------------------------------------------------------------\e[1;97m"
    echo -e "\e[1;91mVALGRIND OUTPUT:\e[1;97m"
    cat "$file_valgrind"
    echo -e "\e[0;91m---------------------------------------------------------------------------------\e[1;97m"
  fi
}

if [[ -n $line_number && -n $file_path ]]; then
  # Print test case
  echo -e "\e[0;93m---------------------------------------------------------------------------------\e[1;97m"
  echo -e "\e[1;93mTEST CASE $test_number FROM $file_dirname/$file_basename AT LINE $line_number:\e[1;97m"
  sed -n "${line_number},\$p" "$file_path" | awk 'NF {p=1} !NF {if(p) exit} {if(p) print}'
  echo -e "\e[0;93m---------------------------------------------------------------------------------\e[1;97m"

  # Check all arguments for the -v flag
  if [[ " $* " =~ " -v " ]]; then
    # Remove -v from arguments
    set -- "${@//-v/}"
    print_valgrind_output
  else
    for output_type in stdout stderr; do
      print_output $output_type
    done
  fi

  echo -e "\e[1;95m=================================================================================\e[0m"
fi
