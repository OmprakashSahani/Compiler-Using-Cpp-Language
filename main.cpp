#include <iostream>
#include <vector>
#include <string>
#include <cctype>
using namespace std;

enum TokenType {
    NUMBER, PLUS, MINUS, MULTIPLY, DIVIDE, LPAREN, RPAREN, END, INVALID
};

struct Token {
    TokenType type;
    string value;
};

class Lexer {
public:
    Lexer(const string& input) : input(input), index(0) {}

    Token nextToken() {
        while (index < input.size() && isspace(input[index])) {
            index++;  // Skip whitespace
        }

        if (index == input.size()) {
            return Token{END, ""};
        }

        char current = input[index];
        if (isdigit(current)) {
            return number();
        }
        if (current == '+') {
            index++;
            return Token{PLUS, "+"};
        }
        if (current == '-') {
            index++;
            return Token{MINUS, "-"};
        }
        if (current == '*') {
            index++;
            return Token{MULTIPLY, "*"};
        }
        if (current == '/') {
            index++;
            return Token{DIVIDE, "/"};
        }
        if (current == '(') {
            index++;
            return Token{LPAREN, "("};
        }
        if (current == ')') {
            index++;
            return Token{RPAREN, ")"};
        }

        return Token{INVALID, string(1, current)};  // Invalid token
    }

private:
    string input;
    size_t index;

    Token number() {
        string value;
        while (index < input.size() && isdigit(input[index])) {
            value += input[index];
            index++;
        }
        return Token{NUMBER, value};
    }
};

class Parser {
public:
    Parser(Lexer& lexer) : lexer(lexer), currentToken(lexer.nextToken()) {}

    int parse() {
        return expression();
    }

private:
    Lexer& lexer;
    Token currentToken;

    void eat(TokenType type) {
        if (currentToken.type == type) {
            currentToken = lexer.nextToken();
        } else {
            cerr << "Syntax error: Expected " << tokenTypeToString(type) << " but found " << currentToken.value << endl;
            while (currentToken.type != type && currentToken.type != END) {
                currentToken = lexer.nextToken();
            }
        }
    }

    string tokenTypeToString(TokenType type) {
        switch (type) {
            case NUMBER: return "NUMBER";
            case PLUS: return "PLUS";
            case MINUS: return "MINUS";
            case MULTIPLY: return "MULTIPLY";
            case DIVIDE: return "DIVIDE";
            case LPAREN: return "LPAREN";
            case RPAREN: return "RPAREN";
            case END: return "END";
            case INVALID: return "INVALID";
            default: return "UNKNOWN";
        }
    }

    int factor() {
        if (currentToken.type == NUMBER) {
            int value = stoi(currentToken.value);
            eat(NUMBER);
            return value;
        } else if (currentToken.type == LPAREN) {
            eat(LPAREN);
            int result = expression();
            eat(RPAREN);
            return result;
        } else {
            cerr << "Syntax error: Expected number or '(' but found " << currentToken.value << endl;
            exit(1);
        }
    }

    int term() {
        int result = factor();
        while (currentToken.type == MULTIPLY || currentToken.type == DIVIDE) {
            if (currentToken.type == MULTIPLY) {
                eat(MULTIPLY);
                int operand = factor();
                result *= operand;
            } else if (currentToken.type == DIVIDE) {
                eat(DIVIDE);
                int operand = factor();
                result /= operand;
            }
        }
        return result;
    }

    int expression() {
        int result = term();
        while (currentToken.type == PLUS || currentToken.type == MINUS) {
            if (currentToken.type == PLUS) {
                eat(PLUS);
                int operand = term();
                result += operand;
            } else if (currentToken.type == MINUS) {
                eat(MINUS);
                int operand = term();
                result -= operand;
            }
        }
        return result;
    }
};

class CodeGenerator {
public:
    CodeGenerator() : registerCount(0) {}

    void generateCode(int result) {
        cout << "MOV R0, " << result << endl;
        cout << "Result in register R0\n";
    }

    void generateInstruction(const string& instruction, int operand1, int operand2) {
        cout << instruction << " R" << registerCount << ", " << operand1 << ", " << operand2 << endl;
        registerCount++;
    }

    void loadConstant(int value) {
        cout << "MOV R" << registerCount << ", " << value << endl;
        registerCount++;
    }

private:
    int registerCount;
};

int main() {
    string expression;
    cout << "Enter an arithmetic expression: ";
    getline(cin, expression);

    Lexer lexer(expression);
    Parser parser(lexer);
    int result = parser.parse();

    CodeGenerator codeGen;
    codeGen.generateCode(result);

    cout << "\nResult: " << result << endl;

    return 0;
}
