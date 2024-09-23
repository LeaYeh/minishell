#!/bin/bash

test_number=$(echo "$LINE" | grep -oP '\d+(?=:)' | head -1 || true)
line_number=$(echo "$LINE" | grep -oP '\d+' | tail -1 || true)
file_path=$(echo "$LINE" | grep -oP '\s*'"$TESTER_DIR"'/cmds/.*\.sh' || true)
file_basename=$(basename "${file_path%.*}")
file_dirname=$(basename "$(dirname "$file_path")")
output_file_path="${TESTER_OUTPUT_DIR}/${file_dirname}/${file_basename}"

print_output()
{
  local output_type=$1
  local file_minishell="${output_file_path}/${test_number}_${output_type}_minishell"
  local file_bash="${output_file_path}/${test_number}_${output_type}_bash"

  # Print diff of output between bash and minishell
  if [[ -f $file_minishell && -f $file_bash ]]; then
    echo -e "\001\e[0;36m\002---------------------------------------------------------------------------------\001\e[1;97m\002"
    if [[ $output_type == "stdout" ]]; then
      echo -e "\001\e[1;36m\002DIFF OF \001\e[1;34m\002${output_type^^}\001\e[1;36m\002 BETWEEN BASH AND MINISHELL:\001\e[1;97m\002"
    elif [[ $output_type == "stderr" ]]; then
      echo -e "\001\e[1;36m\002DIFF OF \001\e[1;33m\002${output_type^^}\001\e[1;36m\002 BETWEEN BASH AND MINISHELL:\001\e[1;97m\002"
    fi
    diff -u0 --color=always "$file_bash" "$file_minishell"
    echo -e "\001\e[0;36m\002---------------------------------------------------------------------------------\001\e[1;97m\002"
  fi
  # Print output of minishell
  if [[ -f $file_minishell ]]; then
    echo -e "\001\e[0;91m\002---------------------------------------------------------------------------------\001\e[1;97m\002"
    echo -e "\001\e[1;91m\002${output_type^^} OF MINISHELL:\001\e[1;97m\002"
    cat "$file_minishell"
    echo -e "\001\e[0;91m\002---------------------------------------------------------------------------------\001\e[1;97m\002"
  fi
  # Print output of bash
  if [[ -f $file_bash ]]; then
    echo -e "\001\e[0;92m\002---------------------------------------------------------------------------------\001\e[1;97m\002"
    echo -e "\001\e[1;92m\002${output_type^^} OF BASH:\001\e[1;97m\002"
    cat "$file_bash"
    echo -e "\001\e[0;92m\002---------------------------------------------------------------------------------\001\e[1;97m\002"
  fi
}

print_valgrind_output()
{
  local file_valgrind="${output_file_path}/${test_number}_valgrind_out"

  # Print valgrind output
  if [[ -f $file_valgrind ]]; then
    echo -e "\001\e[0;91m\002---------------------------------------------------------------------------------\001\e[1;97m\002"
    echo -e "\001\e[1;91m\002VALGRIND OUTPUT:\001\e[1;97m\002"
    cat "$file_valgrind"
    echo -e "\001\e[0;91m\002---------------------------------------------------------------------------------\001\e[1;97m\002"
  fi
}

if [[ -n $line_number && -n $file_path ]]; then
  # Print test case
  echo -e "\001\e[0;93m\002---------------------------------------------------------------------------------\001\e[1;97m\002"
  echo -e "\001\e[1;93m\002TEST CASE \001\e[35m\002$test_number\001\e[93m\002 FROM $file_dirname/$file_basename AT LINE $line_number:\001\e[1;97m\002"
  sed -n "${line_number},\$p" "$file_path" | awk 'NF {p=1} !NF {if(p) exit} {if(p) print}'
  echo -e "\001\e[0;93m\002---------------------------------------------------------------------------------\001\e[1;97m\002"

  # Check all arguments for the -v flag
  if [[ " $* " =~ " -v " ]]; then
    # Remove -v from arguments
    set -- "${@//-v/}"
    print_valgrind_output
  elif [[ " $* " =~ " -c " ]]; then
    # Remove -c from arguments
    set -- "${@//-c/}"
    # Print no output
  else
    for output_type in stdout stderr; do
      print_output $output_type
    done
  fi

  echo -e "\001\e[1;95m\002=================================================================================\001\e[0m\002"
fi
