#include <iostream>
#include <fstream>
#include <sstream>
#include "../include/lexer.h"
#include "../include/parser.h"
#include "../include/interpreter.h"

int main(int argc, char* argv[]) {
    if (argc != 3 || std::string(argv[1]) != "--file") {
        std::cerr << "Usage: " << argv[0] << " --file <filename>" << std::endl;
        return 1;
    }

    std::ifstream file(argv[2]);
    if (!file.is_open()) {
        std::cerr << "Error opening file: " << argv[2] << std::endl;
        return 1;
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string source_code = buffer.str();

    PyLiteLexer lexer(source_code);
    std::vector<Token> tokens = lexer.tokenize();

    PyLiteParser parser(tokens);
    std::vector<ASTNode> ast = parser.parse();

   
    PyLiteInterpreter interpreter;
    interpreter.interpret(ast);

    return 0;
}