// pylite/include/interpreter.h
#pragma once

#include <vector>
#include <string>
#include "../include/ast.h"
#include <map>

class PyLiteInterpreter {
public:
     PyLiteInterpreter();
    void interpret(const std::vector<ASTNode>& ast);

private:
   std::map<std::string, double> variables;
   std::map<std::string, ASTNode> functions;
   double evaluate(const ASTNode& node, std::map<std::string, double> function_scope = std::map<std::string,double>());

};
