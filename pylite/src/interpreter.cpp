// pylite/src/interpreter.cpp
#include "../include/interpreter.h"
#include <iostream>
#include <stdexcept>
#include <sstream>
#include <cmath>


PyLiteInterpreter::PyLiteInterpreter() {}

void PyLiteInterpreter::interpret(const std::vector<ASTNode>& ast) {
    for (const auto& node : ast) {
        evaluate(node);
    }
}

double PyLiteInterpreter::evaluate(const ASTNode& node, std::map<std::string, double> function_scope) {
    if (node.type == INT_NODE) {
        return std::stod(node.value);
    } else if (node.type == FLOAT_NODE) {
        return std::stod(node.value);
    } else if (node.type == STRING_NODE) {
         return 0;
    } else if (node.type == BOOLEAN_NODE) {
        return node.value == "true" ? 1 : 0;
    } else if (node.type == IDENTIFIER_NODE) {
          if (function_scope.count(node.value)) {
                return function_scope.at(node.value);
           }
          else if (variables.count(node.value)) {
                return variables.at(node.value);
          }
        else {
            throw std::runtime_error("Undefined variable: " + node.value);
        }
    }
    else if (node.type == ASSIGNMENT_NODE) {
        double value = evaluate(node.children[0], function_scope);
          if(!function_scope.empty())
              function_scope[node.value] = value;
         else
            variables[node.value] = value;
        return value;
     } else if (node.type == UNARY_OP_NODE) {
        if (node.value == "-") {
            double value = evaluate(node.children[0], function_scope);
             return -value;
         }
         if (node.value == "not") {
            double value = evaluate(node.children[0], function_scope);
              return  !((bool)value);
         }
    } else if (node.type == BINARY_OP_NODE) {
        double left = evaluate(node.children[0], function_scope);
        double right = evaluate(node.children[1], function_scope);
        if (node.value == "+") return left + right;
        if (node.value == "-") return left - right;
        if (node.value == "*") return left * right;
        if (node.value == "/") {
             if(right == 0)
               throw std::runtime_error("Division by zero");
             return left / right;
        }
       if (node.value == "//") {
             if (right == 0)
                 throw std::runtime_error("Division by zero");
            return std::floor(left/right);
       }
        if(node.value == "%"){
            if (right == 0)
                throw std::runtime_error("Modulo by zero");
           return std::fmod(left, right);
        }
        if(node.value == "**") return std::pow(left, right);
        if (node.value == "==") return left == right;
        if (node.value == "!=") return left != right;
        if (node.value == "<") return left < right;
        if (node.value == ">") return left > right;
        if (node.value == "<=") return left <= right;
        if (node.value == ">=") return left >= right;
       if (node.value == "and") return left && right;
        if (node.value == "or") return left || right;


    } else if (node.type == PRINT_STATEMENT_NODE) {
        for(size_t i = 0; i < node.children.size(); ++i){
            if(node.children[i].type == STRING_NODE){
                std::cout << node.children[i].value;
            } else {
              std::cout <<  evaluate(node.children[i], function_scope);
            }
           if(i < node.children.size() - 1)
                std::cout << " ";
        }
        std::cout << std::endl;
    }
     else if (node.type == CALL_EXPRESSION_NODE) {
            double name = evaluate(node.children[0], function_scope);
            std::vector<double> args;
              for (size_t i = 0; i < node.children[1].children.size(); ++i){
                   args.push_back(evaluate(node.children[1].children[i], function_scope));
              }

               std::string function_name = node.children[0].value;
                 if (function_name == "len") {
                   if (args.size() != 1 || node.children[1].children[0].type != STRING_NODE){
                       throw std::runtime_error("Invalid args for len function: " );
                   }
                     return node.children[1].children[0].value.length();
                }
                else if (function_name == "int") {
                     if (args.size() != 1) {
                          throw std::runtime_error("Invalid number of arguments for int()");
                    }
                    try{
                        return (int)args[0];
                    } catch (std::exception const& e){
                        throw std::runtime_error("Invalid argument for int()");
                    }
                } else if (function_name == "float") {
                      if (args.size() != 1) {
                          throw std::runtime_error("Invalid number of arguments for float()");
                    }
                    try{
                        return (float)args[0];
                    }
                    catch (std::exception const& e){
                       throw std::runtime_error("Invalid argument for float()");
                   }
                } else if (function_name == "str") {
                    if (args.size() != 1) {
                          throw std::runtime_error("Invalid number of arguments for str()");
                     }
                     std::stringstream ss;
                     ss << args[0];
                     return 0;
                }
              else if (function_name == "input") {
                 if (args.size() > 1){
                     throw std::runtime_error("Invalid number of arguments for input()");
                 }
                std::string prompt = "";
                if(args.size() > 0){
                  std::stringstream ss;
                   ss << args[0];
                   prompt = ss.str();
                  }
                 std::cout << prompt;
                 std::string input_str;
                 std::getline(std::cin, input_str);
                 return 0;
              }
                 else if (functions.count(function_name)){
                    ASTNode func_node = functions[function_name];
                    std::vector<std::string> params;
                      for (size_t i=0; i < func_node.children[0].children.size(); ++i)
                        params.push_back(func_node.children[0].children[i].value);

                       std::map<std::string, double> func_scope;
                       if (params.size() != args.size())
                            throw std::runtime_error("Expected " + std::to_string(params.size()) + " arguments for function " + function_name + " but got " + std::to_string(args.size()));

                       for (size_t i =0; i < params.size(); ++i)
                            func_scope[params[i]] = args[i];

                        double return_value = 0;

                    for(size_t i = 1; i < func_node.children.size(); ++i){
                         double result = evaluate(func_node.children[i], func_scope);
                          if(func_node.children[i].type == RETURN_STATEMENT_NODE) {
                            return_value = result;
                            break;
                           }
                        }
                       return return_value;

                 } else {
                      throw std::runtime_error("Undefined function: " + function_name);
                 }

    }
    else if (node.type == IF_STATEMENT_NODE) {
        double condition = evaluate(node.children[0], function_scope);
        if (condition) {
             for(size_t i = 1; i < node.children[1].children.size(); ++i){
                 evaluate(node.children[1].children[i], function_scope);
             }
        }  else {
          std::vector<ASTNode> elif_blocks =  node.children[2].children[0].children[0].children;
         bool elif_executed = false;
           for (const ASTNode& elif_block: elif_blocks){
               double elif_condition = evaluate(elif_block.children[0], function_scope);
                if(elif_condition){
                    for(size_t i = 0; i < elif_block.children[1].children.size(); ++i)
                         evaluate(elif_block.children[1].children[i], function_scope);
                        elif_executed = true;
                        break;
                }
           }
            if(!elif_executed){
               for(const ASTNode& else_node :  node.children[2].children[0].children[1].children)
                     evaluate(else_node, function_scope);
            }


        }
    }
      else if (node.type == WHILE_STATEMENT_NODE) {
       while(evaluate(node.children[0], function_scope)){
         for(size_t i = 0; i < node.children[1].children.size(); ++i){
              evaluate(node.children[1].children[i], function_scope);
          }
       }
     }
        else if (node.type == FUNCTION_DEFINITION_NODE) {
            functions[node.value] = node;
     }
       else if (node.type == RETURN_STATEMENT_NODE){
           if(!node.children.empty()){
              return evaluate(node.children[0], function_scope);
           }
          return 0;
       }
     else {
         throw std::runtime_error("Unknown node type: " + std::to_string(node.type));
    }
    return 0;

}
