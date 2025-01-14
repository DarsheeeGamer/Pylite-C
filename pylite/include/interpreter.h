#pragma once
#include <vector>
#include <string>
#include <map>
#include "../include/ast.h"


class PyLiteInterpreter {
public:
    PyLiteInterpreter();
    void interpret(const std::vector<ASTNode>& ast);
private:
    std::map<std::string, double> variables;
    std::map<std::string, ASTNode> functions;
    std::map<std::string, ASTNode> modules;
    double evaluate(const ASTNode& node, std::map<std::string, double> function_scope = {});
};