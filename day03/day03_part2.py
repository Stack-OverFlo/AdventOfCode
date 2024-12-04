import sys

def do_op(operand1, operand2):
    return operand1 * operand2

def check_mul(token):
    mul_start_index = token.find('mul(')
    if mul_start_index == -1:
        return None
    mul_end_index = token.find(')', mul_start_index)
    if mul_end_index == -1:
        return None
    inner_part = token[mul_start_index + 4:mul_end_index]
    if not all(c.isdigit() or c == ',' for c in inner_part):
        return None
    operands_str = inner_part.split(',')
    if len(operands_str) != 2:
        return None
    try:
        operand1, operand2 = map(int, operands_str)
    except ValueError:
        return None
    return operand1, operand2

def handle_broken_mul(token, start, end):
    if (start > end and token.rfind("mul(") < token.rfind(")")):
        return token[token.rfind("mul("):token.rfind(")") + 1]
    else:
        return ""

def check_double_mul(token):
    count_start = token.count("mul(")
    count_end = token.count(")")
    if count_start != count_end:
        new_token = handle_broken_mul(token, count_start, count_end)
        if new_token:
            return new_token
    return token

def extract_numbers(token):
    if token.startswith("mul(") and token.endswith(")"):
        inner_part = token[4:-1]
        parts = inner_part.split(',')
        if len(parts) == 2:
            try:
                x = int(parts[0].strip())
                y = int(parts[1].strip())
                return x, y
            except ValueError:
                return None, None
    return None, None

def find_all_mul(buffer):                                                                         
    total = 0
    start = 0                                                  
    buffer_length = len(buffer)
    
    while True:
        mul_pos = buffer.find("mul(", start)                                            
        if mul_pos == -1:                                                                         
            break                                                                                 
        process_mul = True
        token_start = mul_pos                                                                     
        token_end = buffer.find(")", token_start)
        do_pos = buffer.rfind("do()", 0, mul_pos)
        dont_pos = buffer.rfind("don't()", 0, mul_pos)
        if do_pos > dont_pos:                                                                    
            process_mul = True
        elif dont_pos > do_pos:                                                                   
            process_mul = False
        else:                                                                                     
            process_mul = True
        token = buffer[token_start:token_end + 1]                                                 
        start = token_end + 1                                                                     
        if process_mul:                                                                           
            token = check_double_mul(token)                                                       
            operands = check_mul(token)                                                           
            if operands is None:                                                                  
                continue                                                                          
            op1, op2 = operands                                                                   
            result = do_op(op1, op2)                                                              
            total += result                                                                       
        else:                                                                                     
            pass                                                                                  
    print(f"Total: {total}")
    return total

def read_input(input):                                                                            
    with open(input, 'r') as file:                                                                
        buffer = file.read()                                                                      
    find_all_mul(buffer)

def main():
    if len(sys.argv) != 2:
        print("Usage: python3 day03_part2.py <input_file>")
        return 1
    try:
        read_input(sys.argv[1])
    except FileNotFoundError:
        print(f"Error: File '{sys.argv[1]}' not found")
        return 1
    return 0

main()
