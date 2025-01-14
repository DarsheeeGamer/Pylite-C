#pragma once
#include <vector>
#include "../include/token.h"
#include "../include/ast.h"
#include <map>
#include <stdexcept>
#include <string>

class ParserError : public std::runtime_error {
public:
    ParserError(int code, const std::string& message, int line, std::vector<std::string> traceback = {})
        : std::runtime_error(message), code(code), line(line), traceback(traceback) {}
    int code;
    int line;
    std::vector<std::string> traceback;

};

class PyLiteParser {
public:
    PyLiteParser(std::vector<Token> tokens);
    std::vector<ASTNode> parse();
    void push_traceback(const std::string& function_name);
    void pop_traceback();
private:
    std::vector<Token> tokens;
    size_t pos = 0;
     std::map<std::string, ASTNode> functions;
    std::vector<std::string> traceback;

    Token peek(size_t offset = 0) const;
    Token consume();
    bool match(TokenType type, std::string value = "");
    Token require(TokenType type, std::string value = "");

    ASTNode parse_statement();
    ASTNode parse_function_definition();
    ASTNode parse_if_statement();
    ASTNode parse_while_statement();
    ASTNode parse_print_statement();
    ASTNode parse_return_statement();
     ASTNode parse_yield_statement();
      ASTNode parse_import_statement();
    ASTNode parse_assignment();
    ASTNode parse_typed_assignment();
    ASTNode parse_expression();
     ASTNode parse_dict_expression();
     ASTNode parse_set_expression();
    ASTNode parse_call_expression();
    ASTNode parse_or_expression();
    ASTNode parse_and_expression();
     ASTNode parse_not_expression();
    ASTNode parse_comparison();
    ASTNode parse_addition();
    ASTNode parse_multiplication();
     ASTNode parse_unary();
    ASTNode parse_primary_expression();
    ASTNode parse_function_call(ASTNode left);
    ASTNode parse_primary();
};