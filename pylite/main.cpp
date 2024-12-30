// pylite/main.cpp
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include "../include/lexer.h"
#include "../include/parser.h"
#include "../include/interpreter.h"

void run_pylite_code(const std::string& code) {
    try {
        PyLiteLexer lexer(code);
        std::vector<Token> tokens = lexer.tokenize();
        PyLiteParser parser(tokens);
        std::vector<ASTNode> ast = parser.parse();
         PyLiteInterpreter interpreter;
        interpreter.interpret(ast);


    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}

int main(int argc, char* argv[]) {
    if (argc > 1) {
        std::string file_path = argv[1];
        if (file_path.length() < 7 || file_path.substr(file_path.length() - 7) != ".pylite") {
            std::cerr << "Error: only .pylite files are allowed" << std::endl;
             return 1;
        }
        std::ifstream file(file_path);
         if(!file.is_open()){
            std::cerr << "Error: File not found '" << file_path << "'" << std::endl;
            return 1;
         }
        std::stringstream buffer;
        buffer << file.rdbuf();
        std::string code = buffer.str();
        run_pylite_code(code);
    } else {
        PyLiteInterpreter interpreter;
        std::string code;
        while(true){
           std::cout << ">>> ";
            std::getline(std::cin, code);
            if(code == "exit()"){
                break;
            }
              run_pylite_code(code);
        }

    }
     return 0;
}
