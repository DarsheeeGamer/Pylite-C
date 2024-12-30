// pylite/include/parser.h
#pragma once
#include <vector>
#include "../include/token.h"
#include "../include/ast.h"
#include <map>

class PyLiteParser {
public:
    PyLiteParser(std::vector<Token> tokens);
    std::vector<ASTNode> parse();
private:
     std::vector<Token> tokens;
     size_t pos;
     std::map<std::string, ASTNode> functions;
     Token peek(size_t offset = 0);
     Token consume();
    bool match(TokenType type, std::string value = "");
    Token require(TokenType type, std::string value = "");
    ASTNode parse_statement();
     ASTNode parse_function_definition();
    ASTNode parse_if_statement();
    ASTNode parse_while_statement();
    ASTNode parse_print_statement();
    ASTNode parse_return_statement();
    ASTNode parse_assignment();
    ASTNode parse_expression();
      ASTNode parse_call_expression();
    ASTNode parse_or_expression();
    ASTNode parse_and_expression();
    ASTNode parse_not_expression();
    ASTNode parse_comparison();
    ASTNode parse_addition();
    ASTNode parse_multiplication();
    ASTNode parse_unary();
    ASTNode parse_primary();

};
