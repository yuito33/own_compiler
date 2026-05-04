# Java-to-MIPS Compiler

## Overview
This project is a simple Java-to-MIPS compiler prototype. It targets a small subset of Java and currently uses a combination of C/Flex/Bison and Python for compiler components.

---

## Features
- Lexical analysis for Java-like input
- Syntax analysis with Bison grammars
- Semantic routines and AST reconstruction
- Intermediate representation (IR) support
- Code generation to MIPS assembly
- Simple support for `print`, integer assignments, and `if` blocks

---

## Architecture
The compiler is organized into these main components:
1. Lexer: `scanner/` contains the Flex scanner and supporting C code.
2. Parser: `parser.bison`, `Parser/parser.bison`, and `SemanticRoutines/parser_ast.bison` define the grammar and parse input.
3. Semantic Analyzer / AST reconstruction: `SemanticRoutines/code_gen.py` reconstructs an AST from IR and applies semantic-style processing.
4. Code Generator: `CodeGenerator/code_gen.py` generates MIPS assembly from the reconstructed AST.

---

## Implementation Notes
- `CodeGenerator/code_gen.py` and `SemanticRoutines/code_gen.py` both parse an IR file (`output.txt` by default), reconstruct a simple AST, and emit MIPS code.
- The current MIPS generator supports string printing, integer constants, variable initialization, and basic `if` statements.
- Generated MIPS can be executed with MARS, QtSPIM, or another MIPS simulator.

---

## Tools & Requirements
- Python 3 for running the generator scripts
- C compiler and Flex/Bison if you want to rebuild scanner/parser components
- MARS or QtSPIM to run generated MIPS assembly

---

## How to Run
1. Produce an intermediate representation file named `output.txt` from the parser/semantic phase.
2. Run the generator script:
   - `python CodeGenerator/code_gen.py`
   - or `python SemanticRoutines/code_gen.py`
3. Copy the printed output into a `.s` file and load it in MARS or QtSPIM.

---

## Notes
This repository currently contains prototype implementations and duplicated code for experimentation. The generator scripts are a good starting point for extending the compiler with more Java constructs.


