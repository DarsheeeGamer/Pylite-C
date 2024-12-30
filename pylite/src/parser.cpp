// pylite/src/parser.cpp
#include "../include/parser.h"
#include <iostream>
#include <stdexcept>


PyLiteParser::PyLiteParser(std::vector<Token> tokens) : tokens(tokens), pos(0) {}

std::vector<ASTNode> PyLiteParser::parse() {
    std::vector<ASTNode> statements;
      while(pos < tokens.size() && peek().type != EOF_TOKEN){
         if (peek().type == KEYWORD && peek().value == "def") {
              statements.push_back(parse_function_definition());
         } else {
              statements.push_back(parse_statement());
        }

    }
    return statements;
}

Token PyLiteParser::peek(size_t offset) {
    if (pos + offset < tokens.size()) {
        return tokens[pos + offset];
    }
    return Token(EOF_TOKEN);
}
Token PyLiteParser::consume() {
    Token token = tokens[pos];
    pos++;
    return token;
}
bool PyLiteParser::match(TokenType type, std::string value) {
    if (peek().type == type && (value.empty() || peek().value == value)) {
        consume();
        return true;
    }
    return false;
}
Token PyLiteParser::require(TokenType type, std::string value) {
    if (peek().type == type && (value.empty() || peek().value == value)) {
        return consume();
    }
    if (value.empty()) {
       throw std::runtime_error("Expected " + std::to_string(type) + ", got " + peek().toString());
    } else {
          throw std::runtime_error("Expected " + std::to_string(type) + " with value " + value + ", got " + peek().toString());
    }

}

ASTNode PyLiteParser::parse_function_definition(){
       require(KEYWORD, "def");
        std::string name = require(IDENTIFIER).value;
        require(OPERATOR, "(");
        std::vector<std::string> params;
        while (peek().type == IDENTIFIER) {
            params.push_back(require(IDENTIFIER).value);
            if (!match(OPERATOR, ",")) {
                break;
            }
        }
        require(OPERATOR, ")");
        require(OPERATOR, ":");

        std::vector<ASTNode> body;
        while(pos < tokens.size() && peek().type != EOF_TOKEN && peek(0).type != NEWLINE && !(peek().type == KEYWORD && peek().value == "def")){
          body.push_back(parse_statement());
        }

        return ASTNode(FUNCTION_DEFINITION_NODE, name,  {ASTNode(IDENTIFIER_NODE, "", std::vector<ASTNode>()), body});
}


ASTNode PyLiteParser::parse_statement() {
    if (match(KEYWORD, "if")) {
        return parse_if_statement();
    }
     if (match(KEYWORD, "while")) {
        return parse_while_statement();
    }
     if (match(KEYWORD, "print")) {
        return parse_print_statement();
    }
     if (match(KEYWORD, "return")) {
         return parse_return_statement();
     }

    return parse_assignment();
}

ASTNode PyLiteParser::parse_if_statement() {
     require(OPERATOR, "(");
     ASTNode condition = parse_expression();
      require(OPERATOR, ")");
     require(OPERATOR, ":");

     std::vector<ASTNode> if_statements;
     while(pos < tokens.size() && peek().type != EOF_TOKEN && peek(1).type != KEYWORD && peek(0).type != NEWLINE){
           if_statements.push_back(parse_statement());
     }

     std::vector<std::map<std::string, std::vector<ASTNode>>> elif_statements;
     while(match(KEYWORD, "elif")){
          require(OPERATOR, "(");
          ASTNode elif_condition = parse_expression();
           require(OPERATOR, ")");
          require(OPERATOR, ":");
          std::vector<ASTNode> elif_block;
          while(pos < tokens.size() && peek().type != EOF_TOKEN && peek(1).type != KEYWORD && peek(0).type != NEWLINE){
               elif_block.push_back(parse_statement());
          }
         elif_statements.push_back({{"condition", {elif_condition}}, {"statements", elif_block}});
     }


     std::vector<ASTNode> else_statements;
     if(match(KEYWORD, "else")){
          require(OPERATOR, ":");
          while(pos < tokens.size() && peek().type != EOF_TOKEN && peek(0).type != NEWLINE){
               else_statements.push_back(parse_statement());
          }
     }


     std::map<std::string, std::vector<ASTNode>> last_block;
     last_block["elif"] = {};
     for (auto const& elif_map : elif_statements){
        last_block["elif"].push_back(ASTNode(IDENTIFIER_NODE, "", {elif_map.at("condition")[0], ASTNode(IDENTIFIER_NODE, "", elif_map.at("statements"))}));
     }

     last_block["else"] = else_statements;
     return ASTNode(IF_STATEMENT_NODE,  {condition, ASTNode(IDENTIFIER_NODE, "", if_statements), ASTNode(IDENTIFIER_NODE,"", std::vector<ASTNode>{
         ASTNode(IDENTIFIER_NODE, "", std::vector<ASTNode>{
             ASTNode(IDENTIFIER_NODE, "", last_block["elif"]),
             ASTNode(IDENTIFIER_NODE, "", last_block["else"])
         }
         )
     }
    )});
}

ASTNode PyLiteParser::parse_while_statement() {
       require(OPERATOR, "(");
     ASTNode condition = parse_expression();
       require(OPERATOR, ")");
       require(OPERATOR, ":");

       std::vector<ASTNode> while_statements;
        while(pos < tokens.size() && peek().type != EOF_TOKEN && peek(0).type != NEWLINE){
              while_statements.push_back(parse_statement());
        }
        return ASTNode(WHILE_STATEMENT_NODE, {condition, ASTNode(IDENTIFIER_NODE, "", while_statements)});
}

ASTNode PyLiteParser::parse_print_statement() {
        require(OPERATOR, "(");
         std::vector<ASTNode> expressions;
         if(peek().type != OPERATOR || peek().value != ")"){
              expressions.push_back(parse_expression());
               while(match(OPERATOR, ",")){
                   expressions.push_back(parse_expression());
               }
         }
         require(OPERATOR, ")");
        return ASTNode(PRINT_STATEMENT_NODE,  expressions);

}
ASTNode PyLiteParser::parse_return_statement() {
     ASTNode expression;
     if (peek().type != NEWLINE) {
          expression = parse_expression();
     }
     return ASTNode(RETURN_STATEMENT_NODE, {expression});
}


ASTNode PyLiteParser::parse_assignment() {
    if (peek(1).value == "=") {
        std::string identifier = require(IDENTIFIER).value;
         require(OPERATOR, "=");
         ASTNode expression = parse_expression();
         return ASTNode(ASSIGNMENT_NODE, identifier, {expression});
    }
    return parse_expression();
}
ASTNode PyLiteParser::parse_expression(){
    return parse_call_expression();
}

ASTNode PyLiteParser::parse_call_expression() {
    ASTNode left = parse_or_expression();
    if (match(OPERATOR, "(")) {
        std::vector<ASTNode> args;
         if (peek().type != OPERATOR || peek().value != ")") {
            args.push_back(parse_expression());
             while(match(OPERATOR, ","))
                  args.push_back(parse_expression());
         }
         require(OPERATOR, ")");
        return ASTNode(CALL_EXPRESSION_NODE,  {left, ASTNode(IDENTIFIER_NODE, "", args)});
    }
    return left;
}

ASTNode PyLiteParser::parse_or_expression() {
    ASTNode left = parse_and_expression();
     while(match(KEYWORD, "or")) {
        ASTNode right = parse_and_expression();
        left = ASTNode(BINARY_OP_NODE, "or", {left, right});
    }
    return left;
}

ASTNode PyLiteParser::parse_and_expression() {
    ASTNode left = parse_not_expression();
    while(match(KEYWORD, "and")){
        ASTNode right = parse_not_expression();
         left = ASTNode(BINARY_OP_NODE, "and", {left, right});
    }
    return left;
}

ASTNode PyLiteParser::parse_not_expression() {
    if(match(KEYWORD, "not")) {
         ASTNode expression = parse_not_expression();
        return ASTNode(UNARY_OP_NODE, "not", {expression});
    }
    return parse_comparison();
}

ASTNode PyLiteParser::parse_comparison() {
   ASTNode left = parse_addition();
   while(peek().type == OPERATOR && (peek().value == "==" || peek().value == "!=" ||
        peek().value == "<" || peek().value == ">" || peek().value == "<=" || peek().value == ">=")){
         std::string op = consume().value;
         ASTNode right = parse_addition();
           left = ASTNode(BINARY_OP_NODE, op, {left, right});
   }
    return left;
}


ASTNode PyLiteParser::parse_addition() {
     ASTNode left = parse_multiplication();
     while(peek().type == OPERATOR && (peek().value == "+" || peek().value == "-")) {
          std::string op = consume().value;
          ASTNode right = parse_multiplication();
          left = ASTNode(BINARY_OP_NODE, op, {left, right});
     }
     return left;
}

ASTNode PyLiteParser::parse_multiplication() {
    ASTNode left = parse_unary();
     while(peek().type == OPERATOR && (peek().value == "*" || peek().value == "/" ||
        peek().value == "//" || peek().value == "%" || peek().value == "**")) {
          std::string op = consume().value;
          ASTNode right = parse_unary();
           left = ASTNode(BINARY_OP_NODE, op, {left, right});
     }
    return left;
}
ASTNode PyLiteParser::parse_unary() {
      if (peek().type == OPERATOR && peek().value == "-") {
           consume();
           ASTNode expression = parse_unary();
            return ASTNode(UNARY_OP_NODE, "-", {expression});
      }
     return parse_primary();
}

ASTNode PyLiteParser::parse_primary() {
    if (peek().type == INT) {
         return ASTNode(INT_NODE, consume().value);
    }
    if (peek().type == FLOAT) {
          return ASTNode(FLOAT_NODE, consume().value);
    }
    if (peek().type == STRING) {
         return ASTNode(STRING_NODE, consume().value);
    }
    if (peek().type == KEYWORD && peek().value == "True") {
        consume();
        return ASTNode(BOOLEAN_NODE, "true");
    }
      if (peek().type == KEYWORD && peek().value == "False") {
          consume();
          return ASTNode(BOOLEAN_NODE, "false");
    }
      if(peek().type == IDENTIFIER){
            return ASTNode(IDENTIFIER_NODE, consume().value);
      }
    if(match(OPERATOR, "(")) {
        ASTNode expression = parse_expression();
        require(OPERATOR, ")");
        return expression;
    }

     throw std::runtime_error("Expected an expression, got " + peek().toString());
}
