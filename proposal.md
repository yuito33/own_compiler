# Compiler Project – Initial Definition

## 1. Student Information
- **Name:** Yuito Sugimoto
- **Program:** 406C
- **Course:** Compiler Design
- **Semester / Year:** Spring / 2026

## 2. Project Overview
Provide a brief description of your compiler project (1–2 paragraphs). 
- In this project, I will design and implement a simple compiler that translates a subset of the Java programming to MIPS code.

What problem does it solve? What kind of language are you designing or compiling?
- The compiler can handle a subset of Java program. It recognizes a few of functions of Java.

Include the Programming language you will use to implement the compiler (e.g., C, C++, Java, Python, Rust, etc.)
- The compiler will be implemented in C.

## 3. Source Language
- **Name of the source code language:** Java

## 4. Target / Output Language
- **Output of the compiler:**  MIPS code

- **Reason for choosing this output language:** I learned about MIPS in the class Computer Organization CSC252, in the last semester. So, I have knowledge of it.

## 5. Compiler Features (Planned)
List the features you plan to implement.
- Lexical analysis -- Tokenization of Java source code.
- Syntax analysis (parser type, if known) 
- Semantic analysis -- including type checking and so on.
- Intermediate representation
- Optimizations (if any)
- Code generation -- Generation of MIPS code.

## 6. Tools and Libraries
List any tools, frameworks, or libraries you plan to use:
- Lexical analysis
 LEX
- Build tools
 Flex
- Testing frameworks
 Using MARS that can process MIPS code.

## 7. Repository Information
- **Repository hosting service:**  
  GitHub
- **Repository URL:**  
  https://github.com/yuito33/own_compiler

## 8. Project Status
- [x] Repository created
- [x] README file added
- [x] Initial project structure committed

## 9. Additional Notes
Any additional comments, assumptions, or ideas related to the project.
