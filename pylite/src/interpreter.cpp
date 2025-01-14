#include "../include/interpreter.h"
#include "../include/ast.h"
#include <iostream>
#include <stdexcept>
#include <sstream>
#include <cmath>
#include <fstream>
#include "../include/lexer.h"
#include "../include/parser.h"


PyLiteInterpreter::PyLiteInterpreter() {}

void PyLiteInterpreter::interpret(const std::vector<ASTNode>& ast) {
    for (const auto& node : ast) {
        evaluate(node);
    }
}

double PyLiteInterpreter::evaluate(const ASTNode& node, std::map<std::string, double> function_scope) {
    try {
        switch (node.type) {
        case INT_NODE:          return std::stod(node.value);
        case FLOAT_NODE:        return std::stod(node.value);
        case STRING_NODE:       return 0;
        case BOOLEAN_NODE:      return node.value == "true" ? 1 : 0;
        case IDENTIFIER_NODE: {
            if (function_scope.count(node.value)) return function_scope.at(node.value);
            if (variables.count(node.value))   return variables.at(node.value);
            throw std::runtime_error("Undefined variable: " + node.value);
        }
        case ASSIGNMENT_NODE: {
            double value = evaluate(node.children[0], function_scope);
            if(!function_scope.empty()) function_scope[node.value] = value;
            else variables[node.value] = value;
            return value;
        }
        case UNARY_OP_NODE: {
            double value = evaluate(node.children[0], function_scope);
            if (node.value == "-") return -value;
            if (node.value == "not") return !((bool)value);
            throw std::runtime_error("Unknown unary operator: " + node.value);
        }
        case BINARY_OP_NODE: {
            double left = evaluate(node.children[0], function_scope);
            double right = evaluate(node.children[1], function_scope);
             if (node.value == "+") return left + right;
            if (node.value == "-") return left - right;
            if (node.value == "*") return left * right;
            if (node.value == "/") {
                if (right == 0) throw std::runtime_error("Division by zero");
                return left / right;
            }
            if (node.value == "//") {
                if (right == 0) throw std::runtime_error("Division by zero");
                return std::floor(left/right);
            }
             if (node.value == "%") {
                if (right == 0) throw std::runtime_error("Modulo by zero");
                return std::fmod(left, right);
             }
              if (node.value == "**") return std::pow(left, right);
            if (node.value == "==") return left == right;
             if (node.value == "!=") return left != right;
            if (node.value == "<")  return left < right;
            if (node.value == ">")  return left > right;
             if (node.value == "<=") return left <= right;
            if (node.value == ">=") return left >= right;
              if (node.value == "and") return left && right;
            if (node.value == "or") return left || right;
              throw std::runtime_error("Unknown binary operator: " + node.value);
        }
        case PRINT_STATEMENT_NODE: {
           for (size_t i = 0; i < node.children.size(); ++i) {
              if (node.children[i].type == STRING_NODE) {
                 std::cout << node.children[i].value;
                } else {
                 std::cout << evaluate(node.children[i], function_scope);
                }
                if(i < node.children.size() - 1) std::cout << " ";
             }
             std::cout << std::endl;
             return 0;
          }
          case CALL_EXPRESSION_NODE: {
           std::string function_name = node.children[0].value;
           std::vector<double> args;
              for (size_t i = 0; i < node.children[1].children.size(); ++i) {
                  args.push_back(evaluate(node.children[1].children[i], function_scope));
                }
                if(function_name == "len"){
                   if (args.size() != 1) throw std::runtime_error("Invalid args for len function");
                   return node.children[1].children[0].value.length();
               } else if(function_name == "int"){
                  if (args.size() != 1) throw std::runtime_error("Invalid number of arguments for int()");
                   try{ return (int)args[0]; }
                    catch (const std::exception&){throw std::runtime_error("Invalid argument for int()");}

                 }else if(function_name == "float"){
                      if (args.size() != 1)  throw std::runtime_error("Invalid number of arguments for float()");
                       try{ return (float)args[0];}
                       catch (const std::exception&){throw std::runtime_error("Invalid argument for float()");}
                 }
                  else if (function_name == "str") {
                    if (args.size() != 1)  throw std::runtime_error("Invalid number of arguments for str()");
                       std::stringstream ss; ss << args[0]; return 0;
                  }
                else if(function_name == "input"){
                     if (args.size() > 1) throw std::runtime_error("Invalid number of arguments for input()");
                    std::string prompt = args.empty() ? "" : std::to_string(args[0]);
                      std::cout << prompt;
                     std::string input_str; std::getline(std::cin, input_str);  return 0;
                    }

                else if (functions.count(function_name)){
                    ASTNode func_node = functions[function_name];
                     std::vector<std::string> params;
                      for (size_t i = 0; i < func_node.children[0].children.size(); ++i)
                          params.push_back(func_node.children[0].children[i].value);
                      if (params.size() != args.size()) {
                         throw std::runtime_error("Expected " + std::to_string(params.size()) +
                                                " arguments for function " + function_name + " but got " + std::to_string(args.size()));
                         }
                    std::map<std::string, double> func_scope;
                     for (size_t i = 0; i < params.size(); ++i)
                           func_scope[params[i]] = args[i];
                     double return_value = 0;
                      for (const auto& body_statement : func_node.children[1].children) {
                           double result = evaluate(body_statement, func_scope);
                            if (body_statement.type == RETURN_STATEMENT_NODE) {
                                 return_value = result;  break;
                            }
                        }
                      return return_value;
                    } else if (modules.count(function_name)){
                       ASTNode module_node = modules[function_name];
                       if(!args.empty()) throw std::runtime_error("Imported modules cannot be called with parameters");
                       for(const auto& statement: module_node.children) {
                            evaluate(statement);
                        } return 0;
                   } else {
                    throw std::runtime_error("Undefined function or module: " + function_name);
                    }
            }
            case IF_STATEMENT_NODE: {
                double condition = evaluate(node.children[0], function_scope);
               if(condition) {
                     for (size_t i = 1; i < node.children[1].children.size(); ++i) {
                        evaluate(node.children[1].children[i], function_scope);
                    }
                }else {
                      std::vector<ASTNode> elif_blocks = node.children[2].children[0].children[0].children;
                       bool elif_executed = false;
                         for(const ASTNode& elif_block: elif_blocks){
                              double elif_condition = evaluate(elif_block.children[0], function_scope);
                             if(elif_condition){
                                 for (size_t i = 0; i < elif_block.children[1].children.size(); ++i)
                                      evaluate(elif_block.children[1].children[i], function_scope);
                                       elif_executed = true;
                                       break;
                             }
                       }
                        if(!elif_executed){
                           for(const ASTNode& else_node: node.children[2].children[0].children[1].children)
                                 evaluate(else_node, function_scope);
                        }
                }
                return 0;
              }
          case WHILE_STATEMENT_NODE: {
               while (evaluate(node.children[0], function_scope)) {
                 for (size_t i = 0; i < node.children[1].children.size(); ++i) {
                        evaluate(node.children[1].children[i], function_scope);
                     }
                }
              return 0;
          }
           case FUNCTION_DEFINITION_NODE: {
               if(!function_scope.empty()) functions[node.value] = node;
               else functions[node.value] = node;
                 return 0;
            }

          case IMPORT_STATEMENT_NODE: {
               std::string module_name = node.value;
               std::string filename = module_name + ".pylite";
               std::ifstream file(filename);
                if (!file.is_open()) throw std::runtime_error("Could not open module file: " + filename);
                 std::stringstream buffer;  buffer << file.rdbuf();
               std::string source_code = buffer.str();

                PyLiteLexer lexer(source_code);
                std::vector<Token> tokens = lexer.tokenize();

                PyLiteParser parser(tokens);
                std::vector<ASTNode> ast = parser.parse();
                modules[module_name] = ASTNode::create_children_node(IDENTIFIER_NODE, ast);
                 return 0;
             }

          case RETURN_STATEMENT_NODE: {
             return node.children.empty() ? 0 : evaluate(node.children[0], function_scope);
           }

           default:
                throw std::runtime_error("Unknown node type: " + std::to_string(node.type));
            }
    } catch(const std::exception& e){
       throw std::runtime_error(std::string("Evaluation Error: ") + e.what());
    }


}