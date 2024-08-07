import click
import re
import copy


ACTION_TYPES = {'accept': 0, 'shift': 0b001, 'reduce': 0b010, 'goto': 0b100}

TOKEN_TYPES = ['WORD', 'ASSIGNMENT_WORD',
                'RED_IN', 'RED_OUT', 'PIPE',
                'HERE_DOC', 'APPEND',
                'OR', 'AND',
                'L_PAREN', 'R_PAREN']

TOKEN_TYPES = {key: i for i, key in enumerate(TOKEN_TYPES)}
TOKEN_TYPES['T_END'] = -2
TOKEN_TYPES['$end'] = TOKEN_TYPES['T_END']

PARSER_ELEMENTS = ['and_or', 'pipe_sequence', 'command',
              'subshell', 'simple_command',
              'cmd_name', 'cmd_word', 'cmd_prefix', 'cmd_suffix',
              'redirect_list', 'io_redirect', 'io_file',
              'filename', 'io_here', 'here_end']
PARSER_ELEMENTS = {key: i for i, key in enumerate(PARSER_ELEMENTS, 100)}


# Function to map a string to an int, with an optional verbose mode
def map_string_to_int(string, mapping, verbose=False):
    if verbose:
        return string
    return mapping.get(string, 'None' if verbose else -1)


def parse_state(state_str: str) -> int:
    return int(state_str.split()[1])


def get_token_type(token: str, verbose: bool = False) -> int:
    return map_string_to_int(token, TOKEN_TYPES, verbose)


def get_action_type(action: str, verbose: bool = False) -> int:
    return map_string_to_int(action, ACTION_TYPES, verbose)


def get_next_state(action: str, verbose: bool = False) -> int:
    if 'go to state' in action:
        return int(action.split()[-1])
    elif 'reduce using rule' in action:
        tmp = action.split()[-1].strip('()')
        return tmp if verbose else PARSER_ELEMENTS[tmp]
    else:
        return 'None' if verbose else -1

# TODO: !!miss $end token!!
def parse_action(action, verbose: bool = False):
    action_term = action.split(", and go to state ")
    action_term[0] = action_term[0].strip()
    if action_term[0].startswith("go to"):
        action_term[0] = 'goto'
    action_type = map_string_to_int(action_term[0] if action_term else action.split()[0].strip(), ACTION_TYPES, verbose)
    next_state = get_next_state(action, verbose)
    return (action_type, next_state, -1)


def parse_parsing_table(parsing_table: str, verbose: bool = False):
    lines = parsing_table.split("\n")
    action_table = {}
    current_state = None
    for line in lines:
        if line.startswith("state"):
            current_state = parse_state(line)
            action_table[current_state] = {}
        elif len(line.split()) and line.split()[0].isdigit():
            pass
        elif line.strip().startswith("$default"):
            term = line.split()
            action_table[current_state][-1] = (get_action_type(term[1], verbose), get_next_state(line, verbose), -1)
        elif line.strip() and current_state is not None:
            parts = line.split()
            token_type = map_string_to_int(parts[0], TOKEN_TYPES, verbose)
            if token_type == -1:
                token_type = map_string_to_int(parts[0], PARSER_ELEMENTS, verbose)
            action = parse_action(" ".join(parts[1:]), verbose)
            if (isinstance(token_type, str) and token_type != 'None') or \
                (isinstance(token_type, int) and token_type != -1):
                action_table[current_state][token_type] = action
    return action_table


def action_table_to_c_array(action_table):
    c_array = "const int\tg_parsing_table[][5] = {\\\n"
    for state, actions in action_table.items():
        for element, (action_type, next_state, num_reduced_tokens) in actions.items():
            c_array += f"\t{{{state}, {element}, {action_type}, {next_state}, {num_reduced_tokens}}}, \\\n"
    c_array += "};"
    return c_array


def action_table_to_md(action_table):
    md_table = "| State | Element | Action | Next State | Number of Reduced Tokens |\n|-------|------------|--------|------------|-------------------------|\n"
    for state, actions in action_table.items():
        for element, (action_type, action_state, num_reduced_tokens) in actions.items():
            md_table += f"| {state} | {element} | {action_type} | {action_state if action_state is not None else ''} | {num_reduced_tokens} |\n"
    return md_table


def parse_grammar(input_string):
    result = {}
    lines = input_string.split("\n")
    while True:
        line = lines.pop(0)
        if line.strip().startswith("Grammar"):
            break
    for line in lines:
        line = line.strip()
        if line.startswith("Terminals"):
            break
        if not line:
            continue
        key, rest = re.split(':|\|', line)
        key = int(key.split()[0].strip())
        values = rest.strip().split(' ')
        result[key] = values
    return result

def get_reduced_item(input_string, grammer_table, state):
    lines = input_string.split("\n")
    while True:
        line = lines.pop(0)
        if line.strip().startswith(f"state {state}"):
            break
    while True:
        line = lines.pop(0)
        line = line.strip()
        if line.startswith("$default") and 'reduce' in line:
            break
    match = re.search(r'rule (\d+)', line)
    rule_number = int(match.group(1))
    return grammer_table[rule_number]


def tune_action_table(input_string, action_table, verbose=False):
    grammer_table = parse_grammar(input_string)
    for state, actions in action_table.items():
        for element, (action_type, action_state, num_reduced_tokens) in actions.items():
            if (action_type == 2 or action_type == "reduce") and num_reduced_tokens == -1:
                redueced_item = get_reduced_item(input_string, grammer_table, state)
                num_reduced_tokens = redueced_item if verbose else len(redueced_item)
                action_table[state][element] = (action_type, action_state, num_reduced_tokens)
    return action_table



@click.command()
@click.argument('input_file', type=click.Path(exists=True))
@click.argument('output_file', type=click.Path())
@click.option('-v', '--verbose', is_flag=True, help='Enable verbose mode')
def main(input_file, output_file, verbose):
    click.echo(f"Input file: {input_file}")
    click.echo(f"Output file: {output_file}")
    click.echo(f"Verbose mode: {'Enabled' if verbose else 'Disabled'}")

    with open(input_file, "r") as in_file:
        input_string = in_file.read()
        action_table = parse_parsing_table(input_string, verbose)
        action_table = tune_action_table(input_string, action_table, verbose)
        md_table = action_table_to_md(action_table)
        if not verbose:
            with open(f'{output_file}.c', "w") as out_file_c:
                c_array_str = action_table_to_c_array(action_table)
                out_file_c.write(c_array_str)
        with open(f'{output_file}.md', "w") as out_file_md:
            out_file_md.write(md_table)


if __name__ == '__main__':
    main()
