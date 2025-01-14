// pylite/src/compiler.cpp
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include "../include/lexer.h"
#include "../include/parser.h"
#include "../include/ast.h"
#include <chrono>
#include "../include/compiler.h"
#include "../include/interpreter.h"

using namespace std::chrono;


void compile_pylite_code(const std::string& source_code, const std::string& output_file_path) {
    try {
        auto start = high_resolution_clock::now();
        PyLiteLexer lexer(source_code);
        std::vector<Token> tokens = lexer.tokenize();
        PyLiteParser parser(tokens);
        std::vector<ASTNode> ast = parser.parse();
         PyLiteInterpreter interpreter;
        interpreter.interpret(ast);
        auto stop = high_resolution_clock::now();
         auto duration = duration_cast<microseconds>(stop - start);
        std::cout << "Compilation Time: " << duration.count() << " microseconds" << std::endl;
        std::ofstream outfile(output_file_path);

        if(outfile.is_open()){
            for (const auto& node : ast) {
                 outfile << node.toString() << std::endl;
             }
            outfile.close();
            std::cout << "Compilation Complete. Compiled file stored in " << output_file_path << std::endl;
        }
       else
        {
             throw std::runtime_error("Unable to open output file");
        }

    } catch (const std::exception& e) {
        std::cerr << "Compilation Error: " << e.what() << std::endl;
    }
}