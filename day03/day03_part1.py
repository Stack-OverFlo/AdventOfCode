import sys

def do_mul(token):
    mul_start_index = token.find('mul(')
    if mul_start_index == -1:
        return 0
    mul_end_index = token.find(')', mul_start_index)
    if mul_end_index == -1:
        return 0
    inner_part = token[mul_start_index + 4:mul_end_index]
    if ',' not in inner_part or not all(c.isdigit() or c == ',' for c in inner_part):
        return 0
    operands_str = inner_part.split(',')
    if len(operands_str) != 2:
        return 0
    try:
        operand1 = int(operands_str[0])
        operand2 = int(operands_str[1])
    except ValueError:
        return 0
    result = operand1 * operand2
    return result

def handle_broken_mul(token, start, end):
    if start > end and token.rfind("mul(") < token.rfind(")"):
        return token[token.rfind("mul("):token.rfind(")") + 1]
    return ""

def check_double_mul(token):
    count_start = token.count("mul(")
    count_end = token.count(")")
    if count_start != count_end:
        new_token = handle_broken_mul(token, count_start, count_end)
        if new_token:
            return new_token
    return token

def find_all_mul(lines):
    total = 0
    for line in lines:
        start = 0
        while True:
            token_pos_start = line.find("mul(", start)
            if token_pos_start == -1:
                break
            token_pos_end = line.find(")", token_pos_start)
            if token_pos_end == -1:
                break
            token = line[token_pos_start:token_pos_end + 1]
            start = token_pos_end + 1
            token = check_double_mul(token)
            total += do_mul(token)
    print(total)

def read_input(input):
    with open(input) as file:
        lines = file.readlines()
        find_all_mul(lines)

def main():
    if len(sys.argv) != 2:
        print("Usage : python3 day03_part1.py <input_file>")
        return 1
    try:
        read_input(sys.argv[1])
    except FileNotFoundError:
        print(f"Error : File '{sys.argv[1]}' not found")
        return 1
    return 0

main()
