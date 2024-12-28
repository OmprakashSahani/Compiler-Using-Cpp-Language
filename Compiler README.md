# Compiler-Using-Cpp-Language
Arithmetic Expression Evaluator with Code Generation

Overview:
This project implements an arithmetic expression evaluator that can parse and evaluate expressions involving addition, subtraction, multiplication, division, and parentheses. 
The program also includes a basic code generator that simulates generating assembly-like code for the evaluation process.

The system uses a simple lexer (tokenizer) to break down the expression into tokens and a parser to evaluate the result based on operator precedence. 
Additionally, a code generator simulates the generation of assembly instructions for the computation.

Features:
1. Lexer (Tokenizer): Breaks the input expression into meaningful tokens such as numbers, operators, and parentheses.
2. Parser: Evaluates arithmetic expressions based on operator precedence (multiplication/division before addition/subtraction).
3. Code Generator: Outputs assembly-like instructions for the evaluated result.
4. Error Handling: The program handles syntax errors and invalid tokens gracefully, reporting issues when the expression is malformed.

Technologies Used:

C++ Programming Language

Basic concepts of lexical analysis, parsing, and code generation.

How to Use:
1. Compile the Program: To compile the C++ program, use the following command in your terminal:
   g++ -o ExpressionEvaluator ExpressionEvaluator.cpp

2. Run the Program: After compiling, run the program with the following command:
   ./ExpressionEvaluator

3. Input an Expression: When prompted, enter an arithmetic expression (e.g., 3 + 5 * (2 - 8)).

4. View the Result: The program will evaluate the expression and print the result. Additionally, it will simulate generating assembly-like code for the computation process.


Example Usage:

Input:

Enter an arithmetic expression: 3 + 5 * (2 - 8)

Output:

MOV R0, 3

MOV R1, 5

MOV R2, 2

MOV R3, 8

SUB R4, R2, R3

MUL R5, R1, R4

ADD R6, R0, R5

Result in register R0

Result: -13

Code Explanation:

1. Lexer:

The Lexer class reads the input string and generates tokens for numbers, operators, and parentheses. It uses nextToken() to return the next token and number() to parse numbers.

2. Parser:

The Parser class uses recursive descent parsing to evaluate the expression based on operator precedence. The expression(), term(), and factor() methods handle the different levels of precedence for addition/subtraction and multiplication/division.

3. Code Generator:

The CodeGenerator class generates simulated assembly-like instructions for the expression evaluation. It uses registers (R0, R1, R2, etc.) to store intermediate results and outputs instructions like MOV, ADD, SUB, MUL, and DIV.

4. Main Program:

The main function reads an expression from the user, creates a Lexer and Parser, evaluates the result, and then generates the corresponding code.

Error Handling:

Syntax Errors: If there is an error in the syntax (e.g., missing operators or parentheses), the program prints an error message indicating the expected token and the actual token found.

Invalid Tokens: The lexer handles invalid characters by returning an "INVALID" token.

Example of Error Handling:

Invalid Input:

Enter an arithmetic expression: 3 + 5 * & (2 - 8)
Syntax error: Expected NUMBER but found &

Notes:

The program supports basic arithmetic operations with correct operator precedence.
It simulates the process of generating assembly code for an expression evaluation, though it does not actually execute these instructions.
This project can be expanded to support more complex expressions, variables, or more advanced features like error recovery and optimization.
