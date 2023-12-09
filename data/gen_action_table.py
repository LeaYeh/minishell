ACTION_TYPES = {
    'accept': 0,
    'shift': 1,
    'reduce': 2,
}

TOKEN_TYPES = ['WORD', 'ASSIGNMENT_WORD',
                'RED_IN', 'RED_OUT',
                'HEREDOC', 'APPEND',
                'PIPE', 'OR', 'AND',
                'L_BRACKET', 'R_BRACKET']

TOKEN_TYPES = {key: i for i, key in enumerate(TOKEN_TYPES)}

RULE_NAMES = ['pipe_sequence', 'and_or', 'subshell',
              'command', 'redirect_list', 'simple_command',
              'cmd_name', 'cmd_word', 'cmd_prefix', 'cmd_suffix',
              'io_redirect', 'io_file', 'filename', 'io_here', 'here_end']
RULE_NAMES = {key: i for i, key in enumerate(RULE_NAMES, 100)}

def parse_state(state: str) -> int:
    state_num = int(state.split()[1])
    return state_num

def get_token_type(token: str) -> int:
    if token in TOKEN_TYPES.keys():
        return TOKEN_TYPES[token]
    elif token in RULE_NAMES.keys():
        return RULE_NAMES[token]
    return -1

def get_action_type(action: str) -> int:
    if action in ACTION_TYPES.keys():
        return ACTION_TYPES[action]
    return -1

def get_next_state(action: str) -> int:
    if 'go to state' in action:
        return int(action.split()[-1])
    return -1

def parse_action(action):
    action_term = action.split(", and go to state ")
    if len(action_term) > 1:
        # action_type = get_action_type(action_term[0].strip())
        action_type = action_term[0].strip() if get_action_type(action_term[0].strip()) > -1 else -1
    else:
        action_term = action.split()
        # action_type = get_action_type(action_term[0].strip())
        action_type = action_term[0].strip() if get_action_type(action_term[0].strip()) > -1 else -1
    next_state = get_next_state(action)
    return (action_type, next_state, -1)
    #     action_state = int(action[1])
    #     num_reduced_tokens = len(action[0].split())
    # else:
    #     action_state = None
    #     num_reduced_tokens = 0
    # return (action_type, action_state, num_reduced_tokens)

def parse_parsing_table(parsing_table):
    lines = parsing_table.split("\n")
    action_table = {}
    current_state = None
    for line in lines:
        if '11' in line:
            print(line)
        if line.startswith("state"):
            current_state = parse_state(line)
            action_table[current_state] = {}
        elif line.strip().startswith("$default"):
            term = line.split()
            action_table[current_state][-1] = (term[1], -1, -1)
            # action_table[current_state][-1] = (get_action_type(term[1]), -1, -1)
        elif line.strip() and current_state is not None:
            parts = line.split()
            # token_type = get_token_type(parts[0])
            token_type = parts[0] if get_token_type(parts[0]) > -1 else -1
            action = parse_action(" ".join(parts[1:]))
            if get_token_type(parts[0]) > -1:
                action_table[current_state][token_type] = action
    return action_table


def action_table_to_md(action_table):
    md_table = "| State | Token Type | Action | Next State | Number of Reduced Tokens |\n|-------|------------|--------|------------|-------------------------|\n"
    for state, actions in action_table.items():
        for symbol, (action_type, action_state, num_reduced_tokens) in actions.items():
            md_table += f"| {state} | {symbol} | {action_type} | {action_state if action_state is not None else ''} | {num_reduced_tokens} |\n"
    return md_table

with open("data/parsing_rule.output", "r") as in_file:
    with open("data/parsing_table.md", "w") as out_file:
        action_table = parse_parsing_table(in_file.read())
        md_table = action_table_to_md(action_table)
        out_file.write(md_table)
