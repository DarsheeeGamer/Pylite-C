// pylite/src/interpreter.cpp
#include "../include/interpreter.h"
#include <iostream>
#include <stdexcept>
#include <sstream>
#include <cmath>
#include <unordered_set>

PyLiteInterpreter::PyLiteInterpreter() {}

void PyLiteInterpreter::interpret(const std::vector<ASTNode>& ast) {
    for (const auto& node : ast) {
        evaluate(node);
    }
     while(!coroutines.empty()){
          for (auto it = coroutines.begin(); it!= coroutines.end();){
                double result = std::get<double>(it->second(std::unordered_map<std::string, ValueType>()));
                 if (result == std::numeric_limits<double>::infinity()) {
                    it = coroutines.erase(it);
                   }
                else {
                   it++;
                }
        }

    }

}

PyLiteInterpreter::ValueType PyLiteInterpreter::evaluate(const ASTNode& node, std::unordered_map<std::string, ValueType> function_scope) {
    if (node.type == INT_NODE) {
        return std::stod(node.value);
    } else if (node.type == FLOAT_NODE) {
        return std::stod(node.value);
    } else if (node.type == STRING_NODE) {
         return node.value;
    } else if (node.type == BOOLEAN_NODE) {
        return node.value == "true" ? true : false;
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
        ValueType value = evaluate(node.children[0], function_scope);
          if(!function_scope.empty()){
              function_scope[node.value] = value;
            }
        else
            variables[node.value] = value;
        return value;
     } else if (node.type == UNARY_OP_NODE) {
        if (node.value == "-") {
            double value = std::get<double>(evaluate(node.children[0], function_scope));
             return -value;
         }
         if (node.value == "not") {
            bool value = std::get<bool>(evaluate(node.children[0], function_scope));
              return  !value;
         }
    } else if (node.type == BINARY_OP_NODE) {
        double left = std::get<double>(evaluate(node.children[0], function_scope));
        double right = std::get<double>(evaluate(node.children[1], function_scope));
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
       if (node.value == "and") return std::get<bool>(evaluate(node.children[0], function_scope)) && std::get<bool>(evaluate(node.children[1], function_scope));
        if (node.value == "or") return std::get<bool>(evaluate(node.children[0], function_scope)) || std::get<bool>(evaluate(node.children[1], function_scope));


    } else if (node.type == PRINT_STATEMENT_NODE) {
        for(size_t i = 0; i < node.children.size(); ++i){
          ValueType value = evaluate(node.children[i], function_scope);
            if (std::holds_alternative<std::string>(value)) {
                 std::cout << std::get<std::string>(value);
            } else if(std::holds_alternative<double>(value)){
              std::cout <<  std::get<double>(value);
             } else if (std::holds_alternative<bool>(value)) {
                 std::cout << (std::get<bool>(value) ? "true" : "false");
            }
               else{
                std::cout << "unsupported type";
             }
           if(i < node.children.size() - 1)
                std::cout << " ";
        }
        std::cout << std::endl;
    }
     else if (node.type == CALL_EXPRESSION_NODE) {
          ValueType name = evaluate(node.children[0], function_scope);
           std::vector<ValueType> args;
              for (size_t i = 0; i < node.children[1].children.size(); ++i){
                   args.push_back(evaluate(node.children[1].children[i], function_scope));
              }
               std::string function_name = std::get<std::string>(name);
                 if (function_name == "len") {
                   if (args.size() != 1 || !std::holds_alternative<std::string>(args[0])){
                       throw std::runtime_error("Invalid args for len function: " );
                   }
                   return (double)std::get<std::string>(args[0]).length();
                }
                else if (function_name == "int") {
                     if (args.size() != 1) {
                          throw std::runtime_error("Invalid number of arguments for int()");
                    }
                    try{
                        return (double)(int)std::get<double>(args[0]);
                    } catch (std::exception const& e){
                        throw std::runtime_error("Invalid argument for int()");
                    }
                } else if (function_name == "float") {
                      if (args.size() != 1) {
                          throw std::runtime_error("Invalid number of arguments for float()");
                    }
                    try{
                        return (double)std::get<double>(args[0]);
                    }
                    catch (std::exception const& e){
                       throw std::runtime_error("Invalid argument for float()");
                   }
                } else if (function_name == "str") {
                    if (args.size() != 1) {
                          throw std::runtime_error("Invalid number of arguments for str()");
                     }
                    if (std::holds_alternative<double>(args[0])){
                           std::stringstream ss;
                           ss << std::get<double>(args[0]);
                           return ss.str();
                    }
                    if (std::holds_alternative<bool>(args[0])){
                      return std::get<bool>(args[0]) ? "true" : "false";
                    }

                    if (std::holds_alternative<std::string>(args[0])){
                          return std::get<std::string>(args[0]);
                    }
                      throw std::runtime_error("Invalid argument for str()");

                }
              else if (function_name == "input") {
                 if (args.size() > 1){
                     throw std::runtime_error("Invalid number of arguments for input()");
                 }
                std::string prompt = "";
                if(args.size() > 0){
                  if (std::holds_alternative<std::string>(args[0]))
                      prompt = std::get<std::string>(args[0]);
                   else if (std::holds_alternative<double>(args[0])){
                           std::stringstream ss;
                           ss << std::get<double>(args[0]);
                           prompt = ss.str();
                       }
                  }
                 std::cout << prompt;
                 std::string input_str;
                 std::getline(std::cin, input_str);
                return input_str;
              }
                 else if (functions.count(function_name)){
                    ASTNode func_node = functions[function_name];
                    std::vector<std::pair<std::string,std::string>> params;
                    for (size_t i=0; i < func_node.children[0].children.size(); ++i) {
                        params.push_back(std::make_pair(func_node.children[0].children[i].value, func_node.children[0].children[i].value));
                    }
                       std::unordered_map<std::string, ValueType> func_scope;
                       if (params.size() != args.size())
                            throw std::runtime_error("Expected " + std::to_string(params.size()) + " arguments for function " + function_name + " but got " + std::to_string(args.size()));

                       for (size_t i =0; i < params.size(); ++i){
                            func_scope[params[i].first] = args[i];
                        }
                        auto generator =  [&, func_node, func_scope, args](std::unordered_map<std::string, ValueType> arg){
                          double return_value = 0;
                            for(size_t i = 1; i < func_node.children.size() -1; ++i){
                               ValueType result = evaluate(func_node.children[i], func_scope);
                               if(func_node.children[i].type == RETURN_STATEMENT_NODE) {
                                   if(std::holds_alternative<double>(result))
                                      return_value = std::get<double>(result);
                                   else if(std::holds_alternative<bool>(result)){
                                     return_value = (double)std::get<bool>(result);
                                   }
                                   else if (std::holds_alternative<std::string>(result)){
                                     std::stringstream ss;
                                     ss << std::get<std::string>(result);
                                     return_value =  std::stod(ss.str());

                                   }

                                 break;
                               }
                               if(func_node.children[i].type == YIELD_STATEMENT_NODE) {
                                 if(std::holds_alternative<double>(result))
                                      yield_value = std::get<double>(result);
                                   else if(std::holds_alternative<bool>(result)){
                                     yield_value = (double)std::get<bool>(result);
                                   }
                                    else if (std::holds_alternative<std::string>(result)){
                                     std::stringstream ss;
                                     ss << std::get<std::string>(result);
                                     yield_value =  std::stod(ss.str());

                                   }
                                   return yield_value;
                                }
                            }
                           return std::numeric_limits<double>::infinity();
                       };

                    if (coroutines.count(function_name)){
                            return coroutines[function_name](func_scope);
                    }
                    else{
                     coroutines[function_name] = generator;
                       return generator(func_scope);
                    }


                 } else {
                      throw std::runtime_error("Undefined function: " + function_name);
                 }

    }
    else if (node.type == IF_STATEMENT_NODE) {
        bool condition = std::get<bool>(evaluate(node.children[0], function_scope));
        if (condition) {
             for(size_t i = 1; i < node.children[1].children.size(); ++i){
                 evaluate(node.children[1].children[i], function_scope);
             }
        }  else {
          std::vector<ASTNode> elif_blocks =  node.children[2].children[0].children[0].children;
         bool elif_executed = false;
           for (const ASTNode& elif_block: elif_blocks){
               bool elif_condition = std::get<bool>(evaluate(elif_block.children[0], function_scope));
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
        while(std::get<bool>(evaluate(node.children[0], function_scope))){
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
    else if (node.type == YIELD_STATEMENT_NODE){
        if(!node.children.empty()){
               return evaluate(node.children[0], function_scope);
        }
          return 0;
    }
     else if (node.type == DICT_NODE){
        return node.dict_value;
    }
      else if (node.type == SET_NODE){
          std::vector<double> set_vals;
          for (const ASTNode& item : node.set_value)
             set_vals.push_back(std::get<double>(evaluate(item, function_scope)));
          return set_vals;

      }
     else {
         throw std::runtime_error("Unknown node type: " + std::to_string(node.type));
    }
     return 0;

}