import re

# =========================
# AST Node Definitions
# =========================

class Node:
    pass


class Print(Node):
    def __init__(self, expr):
        self.expr = expr


class StringLiteral(Node):
    def __init__(self, value):
        self.value = value


class If(Node):
    def __init__(self, cond, body):
        self.cond = cond
        self.body = body


class Var(Node):
    def __init__(self, name, value, type_):
        self.name = name
        self.value = value
        self.type = type_


# =========================
# IR Loader
# =========================

def load_ir(filename):
    with open(filename, "r") as f:
        return f.read()


# =========================
# Expression Parser
# =========================
def parse_expr(expr):
    expr = expr.strip()

    # String literal
    m = re.search(r"EXPR_STRING_LITERAL=\((.*?)\)END", expr)
    if m:
        return StringLiteral(m.group(1))

    # Number
    if expr.isdigit():
        return int(expr)

    # 修正: Java残骸から文字列を抽出してStringLiteralとして扱う
    if "System.out.println" in expr:
        m = re.search(r'System\.out\.println\(\s*"(.*?)"\s*\)', expr)
        if m:
            return StringLiteral(m.group(1))
        return ("PRINT_RAW", expr)

    return expr


# =========================
# Line Parser
# =========================

def parse_line(line):
    line = line.strip()

    if line.startswith("print"):
        expr = line.replace("print", "").strip()
        return Print(parse_expr(expr))

    if line.startswith("if"):
        cond = line.replace("if", "").strip(" ()")
        return ("IF", cond)

    if line == "BEGIN":
        return "BEGIN"

    if line == "END":
        return "END"

    if line.startswith("var"):
        return ("VAR", line)

    return None


# =========================
# VAR block parser
# =========================

def parse_var_block(text):
    m = re.search(r"\[(.*?)\]", text)
    if not m:
        return []

    inside = m.group(1)
    parts = [p.strip() for p in inside.split(";") if p.strip()]

    nodes = []

    for p in parts:
        if "=" in p and "System.out.println" not in p:
            name, value = p.split("=")
            nodes.append(Var(name.strip(), value.strip(), "int"))

        elif p.startswith("System.out.println"):
            nodes.append(Print(parse_expr(p)))

    return nodes


# =========================
# AST Reconstruction
# =========================

def reconstruct_ast(ir_text):
    lines = [l.strip() for l in ir_text.split("\n") if l.strip()]

    stack = []
    current = []

    i = 0
    while i < len(lines):
        parsed = parse_line(lines[i])

        # PRINT
        if isinstance(parsed, Print):
            current.append(parsed)

        # IF
        elif isinstance(parsed, tuple) and parsed[0] == "IF":
            cond = parsed[1]
            stack.append((current, cond))
            current = []

        # VAR
        elif isinstance(parsed, tuple) and parsed[0] == "VAR":
            block = []

            while i < len(lines):
                l = lines[i].strip()
                if l in ["BEGIN", "END"]:
                    break
                block.append(l)
                i += 1

            current.extend(parse_var_block(" ".join(block)))
            continue

        # BEGIN
        elif parsed == "BEGIN":
            pass

        # END
        elif parsed == "END":
            prev, cond = stack.pop()
            prev.append(If(cond, current))
            current = prev

        i += 1

    return current


# =========================
# Debug Print
# =========================

def print_ast(ast, indent=0):
    pad = "  " * indent

    for node in ast:
        if isinstance(node, Print):
            if isinstance(node.expr, StringLiteral):
                print(pad + f'[PRINT] "{node.expr.value}"')
            else:
                print(pad + f"[PRINT] {node.expr}")

        elif isinstance(node, Var):
            print(pad + f"[VAR] {node.name}={node.value}:{node.type}")

        elif isinstance(node, If):
            print(pad + f"[IF] ({node.cond})")
            print_ast(node.body, indent + 1)


# =========================
# MIPS Code Generator
# =========================

def generate_code(ast):
    lines = []
    reg_counter = 0

    def new_reg():
        nonlocal reg_counter
        r = f"$t{reg_counter}"
        reg_counter += 1
        return r

    for node in ast:

        # PRINT
        if isinstance(node, Print):
            expr = node.expr

            if isinstance(expr, StringLiteral):
                label = "msg"
                lines.append(f'{label}: .asciiz "{expr.value}"')
                lines.append("li $v0, 4")
                lines.append(f"la $a0, {label}")
                lines.append("syscall")

            elif isinstance(expr, int):
                r = new_reg()
                lines.append(f"li {r}, {expr}")
                lines.append("li $v0, 1")
                lines.append(f"move $a0, {r}")
                lines.append("syscall")

            elif isinstance(expr, tuple) and expr[0] == "PRINT_RAW":
                continue

        # VAR
        elif isinstance(node, Var):
            r = new_reg()
            lines.append(f"li {r}, {node.value}")

        # IF
        elif isinstance(node, If):
            r = new_reg()
            lines.append(f"li {r}, {node.cond}")
            lines.append(f"beq {r}, $zero, L_end")

            for stmt in node.body:
                lines.extend(generate_code([stmt]))

            lines.append("L_end:")

    return lines


# =========================
# Java Generator (debug)
# =========================

def generate_code_java(ast, indent=0):
    pad = "    " * indent
    lines = []

    for node in ast:

        if isinstance(node, Print):
            if isinstance(node.expr, StringLiteral):
                lines.append(pad + f'System.out.println("{node.expr.value}");')
            else:
                lines.append(pad + f"System.out.println({node.expr});")

        elif isinstance(node, Var):
            lines.append(pad + f"{node.type} {node.name} = {node.value};")

        elif isinstance(node, If):
            lines.append(pad + f"if ({node.cond}) {{")
            lines.extend(generate_code_java(node.body, indent + 1))
            lines.append(pad + "}")

    return lines


# =========================
# Main
# =========================

if __name__ == "__main__":
    ir = load_ir("output.txt")

    ast = reconstruct_ast(ir)

    print("===== RECONSTRUCTED AST =====")
    print_ast(ast)

    print("\n===== RECONSTRUCTED CODE =====")
    print("\n".join(generate_code(ast)))
