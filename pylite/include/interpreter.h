// pylite/include/interpreter.h
#pragma once

#include <vector>
#include <string>
#include "../include/ast.h"
#include <map>
#include <functional>
#include <unordered_map>
#include <variant>

class PyLiteInterpreter {
public:
     PyLiteInterpreter();
    void interpret(const std::vector<ASTNode>& ast);

private:
    using ValueType = std::variant<double, std::string, bool, std::unordered_map<std::string, double>, std::vector<double> >;

  std::unordered_map<std::string, ValueType> variables;
   std::unordered_map<std::string, ASTNode> functions;
    std::unordered_map<std::string, std::function<double(std::unordered_map<std::string, double>)>> coroutines;
  ValueType evaluate(const ASTNode& node, std::unordered_map<std::string, ValueType> function_scope = std::unordered_map<std::string, ValueType>());
   double yield_value = 0;


};