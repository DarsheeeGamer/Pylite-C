#include "../include/parser.h"
#include "../include/ast.h"
#include <iostream>
#include <stdexcept>
#include <sstream>

PyLiteParser::PyLiteParser(std::vector<Token> tokens) : tokens(tokens) {}

std::vector<ASTNode> PyLiteParser::parse() {
    std::vector<ASTNode> statements;
    try {
        while (peek().type != EOF_TOKEN) {
             if(peek().type == KEYWORD && peek().value == "def"){
                statements.push_back(parse_function_definition());
              }
           else if(match(KEYWORD, "import")) { statements.push_back(parse_import_statement());}
            else if (peek().type != NEWLINE) { statements.push_back(parse_statement()); }
            else consume();
        }
    } catch (const ParserError& error) {
        throw error;
    }
    return statements;
}
Token PyLiteParser::peek(size_t offset) const {
    return (pos + offset < tokens.size()) ? tokens[pos + offset] : Token(EOF_TOKEN);
}

Token PyLiteParser::consume() {
    return (pos < tokens.size()) ? tokens[pos++] : Token(EOF_TOKEN);
}

bool PyLiteParser::match(TokenType type, std::string value) {
    if (peek().type == type && (value.empty() || peek().value == value)) { consume(); return true; }
    return false;
}

Token PyLiteParser::require(TokenType type, std::string value) {
    if (peek().type == type && (value.empty() || peek().value == value)) return consume();
    std::stringstream ss; ss << "Expected " << type;
    if (!value.empty()) ss << " with value " << value;
    ss << ", got " << peek().toString();
    throw ParserError(value.empty() ? 200 : 201, ss.str(), peek().line, traceback);
}

void PyLiteParser::push_traceback(const std::string& function_name) { traceback.push_back(function_name);}
void PyLiteParser::pop_traceback() { if (!traceback.empty()) traceback.pop_back(); }


ASTNode PyLiteParser::parse_function_definition() {
    push_traceback("function_definition");
    try {
        require(KEYWORD, "def");
        std::string name = require(IDENTIFIER).value;
        require(OPERATOR, "(");
        std::vector<std::pair<std::string, std::string>> params;
        while (peek().type == IDENTIFIER) {
            std::string paramName = require(IDENTIFIER).value;
            if (match(OPERATOR, ":")) params.emplace_back(paramName, require(KEYWORD).value);
             else params.emplace_back(paramName, "");
            if (peek().type == OPERATOR && peek().value != ")") require(OPERATOR, ",");
        }
        require(OPERATOR, ")"); require(OPERATOR, ":");
         std::vector<ASTNode> body;
        while (peek().type != EOF_TOKEN && peek().type != NEWLINE && !(peek().type == KEYWORD && peek().value == "def")) {
            body.push_back(parse_statement());
        }
        std::vector<ASTNode> params_node;
        for (const auto& param : params) params_node.emplace_back(IDENTIFIER_NODE, param.first);
        pop_traceback();
        return ASTNode::create_children_node(FUNCTION_DEFINITION_NODE, {
            ASTNode::create_children_node(IDENTIFIER_NODE, params_node),
            ASTNode::create_children_node(IDENTIFIER_NODE, body),
            ASTNode(IDENTIFIER_NODE, name)
        });
    } catch (ParserError& e) { e.traceback = traceback; throw e; }
}
ASTNode PyLiteParser::parse_statement() {
    try {
        if (match(KEYWORD, "if")) return parse_if_statement();
        if (match(KEYWORD, "while")) return parse_while_statement();
        if (match(KEYWORD, "print")) return parse_print_statement();
        if (match(KEYWORD, "return")) return parse_return_statement();
        if (match(KEYWORD, "yield")) return parse_yield_statement();
        return parse_expression();
    } catch (ParserError& e) { e.traceback = traceback; throw e; }
}

ASTNode PyLiteParser::parse_if_statement() {
    push_traceback("if_statement");
    try {
        require(OPERATOR, "("); ASTNode condition = parse_expression(); require(OPERATOR, ")"); require(OPERATOR, ":");
        std::vector<ASTNode> if_statements;
        while (peek().type != EOF_TOKEN && peek(1).type != KEYWORD && peek().type != NEWLINE) if_statements.push_back(parse_statement());
        std::vector<std::map<std::string, std::vector<ASTNode>>> elif_statements;
        while(match(KEYWORD, "elif")) {
            require(OPERATOR, "("); ASTNode elif_condition = parse_expression(); require(OPERATOR, ")"); require(OPERATOR, ":");
            std::vector<ASTNode> elif_block;
            while(peek().type != EOF_TOKEN && peek(1).type != KEYWORD && peek().type != NEWLINE) elif_block.push_back(parse_statement());
            elif_statements.push_back({{"condition", {elif_condition}}, {"statements", elif_block}});
        }

        std::vector<ASTNode> else_statements;
        if(match(KEYWORD, "else")) {
             require(OPERATOR, ":");
            while (peek().type != EOF_TOKEN && peek().type != NEWLINE) else_statements.push_back(parse_statement());
        }
          std::map<std::string, std::vector<ASTNode>> last_block;
        last_block["elif"] = {};
        for (auto const& elif_map : elif_statements) {
             last_block["elif"].push_back(ASTNode::create_children_node(IDENTIFIER_NODE, {elif_map.at("condition")[0], ASTNode::create_children_node(IDENTIFIER_NODE, elif_map.at("statements"))}));
        }

        last_block["else"] = else_statements;
        std::vector<ASTNode> if_node_children = {condition, ASTNode::create_children_node(IDENTIFIER_NODE, if_statements)};
          std::vector<ASTNode> elif_else_block;
           std::vector<ASTNode> elif_statements_vec;
          for (const auto& elif : last_block["elif"]) {
            elif_statements_vec.push_back(elif);
        }
        if (!elif_statements_vec.empty()) elif_else_block.push_back(ASTNode::create_children_node(IDENTIFIER_NODE, elif_statements_vec));
        if (!last_block["else"].empty()) elif_else_block.push_back(ASTNode::create_children_node(IDENTIFIER_NODE, last_block["else"]));
         if(!elif_else_block.empty()) if_node_children.push_back(ASTNode::create_children_node(IDENTIFIER_NODE, elif_else_block));
         pop_traceback();
        return ASTNode::create_children_node(IF_STATEMENT_NODE, if_node_children);
    } catch (ParserError& e) { e.traceback = traceback; throw e;}
}
ASTNode PyLiteParser::parse_while_statement() {
    push_traceback("while_statement");
    try {
        require(OPERATOR, "("); ASTNode condition = parse_expression(); require(OPERATOR, ")"); require(OPERATOR, ":");
        std::vector<ASTNode> while_statements;
         while(peek().type != EOF_TOKEN && peek().type != NEWLINE) while_statements.push_back(parse_statement());
        pop_traceback();
        return ASTNode::create_children_node(WHILE_STATEMENT_NODE, {condition, ASTNode::create_children_node(IDENTIFIER_NODE, while_statements)});
    } catch (ParserError& e) { e.traceback = traceback; throw e;}
}

ASTNode PyLiteParser::parse_print_statement() {
     push_traceback("print_statement");
    try {
          require(OPERATOR, "(");
        std::vector<ASTNode> expressions;
          if (peek().type != OPERATOR || peek().value != ")") {
              expressions.push_back(parse_expression());
                while (match(OPERATOR, ","))   expressions.push_back(parse_expression());
            }
            require(OPERATOR, ")");
          pop_traceback();
           return ASTNode::create_children_node(PRINT_STATEMENT_NODE, expressions);
    } catch (ParserError& e) {e.traceback = traceback; throw e;}
}

ASTNode PyLiteParser::parse_return_statement() {
     push_traceback("return_statement");
    try {
         ASTNode expression = ASTNode(IDENTIFIER_NODE);
         if (peek().type != NEWLINE)  expression = parse_expression();
         pop_traceback();
         return ASTNode::create_children_node(RETURN_STATEMENT_NODE, {expression});
    } catch (ParserError& e) {e.traceback = traceback; throw e;}
}
ASTNode PyLiteParser::parse_yield_statement() {
   push_traceback("yield_statement");
    try{
        ASTNode expression = ASTNode(IDENTIFIER_NODE);
        if(peek().type != NEWLINE) expression = parse_expression();
         pop_traceback();
        return ASTNode::create_children_node(YIELD_STATEMENT_NODE, {expression});
    } catch (ParserError& e) {e.traceback = traceback; throw e;}
}
ASTNode PyLiteParser::parse_typed_assignment() {
    push_traceback("typed_assignment");
    try {
         if (peek(1).value == ":" && peek(3).value == "=") {
             std::string identifier = require(IDENTIFIER).value;
             require(OPERATOR, ":"); require(KEYWORD);  require(OPERATOR, "=");
             ASTNode expression = parse_expression();
              pop_traceback();
              return ASTNode::create_children_node(ASSIGNMENT_NODE, {expression, ASTNode(IDENTIFIER_NODE, identifier)});
          }
         return parse_assignment();
     } catch (ParserError& e) {e.traceback = traceback; throw e;}
}

ASTNode PyLiteParser::parse_assignment() {
     push_traceback("assignment");
    try {
         if(peek(1).value == "=") {
              std::string identifier = require(IDENTIFIER).value;
              require(OPERATOR, "=");
             ASTNode expression = parse_expression();
             pop_traceback();
              return ASTNode::create_children_node(ASSIGNMENT_NODE, {expression, ASTNode(IDENTIFIER_NODE, identifier)});
         }
        return parse_expression();
    } catch (ParserError& e) {e.traceback = traceback; throw e;}
}
ASTNode PyLiteParser::parse_expression() {
    try {
        return parse_or_expression();
    } catch (ParserError& e) { e.traceback = traceback; throw e;}
}

ASTNode PyLiteParser::parse_or_expression() {
    push_traceback("or_expression");
     try {
         ASTNode left = parse_and_expression();
          while (match(KEYWORD, "or")) {
              Token operator_token = tokens[pos - 1];
             ASTNode right = parse_and_expression();
              left = ASTNode::create_children_node(BINARY_OP_NODE, {left, right, ASTNode(IDENTIFIER_NODE, operator_token.value)});
            }
         pop_traceback();
          return left;
      } catch (ParserError& e) {e.traceback = traceback; throw e;}
}

ASTNode PyLiteParser::parse_and_expression() {
    push_traceback("and_expression");
    try {
        ASTNode left = parse_not_expression();
           while (match(KEYWORD, "and")) {
              Token operator_token = tokens[pos - 1];
             ASTNode right = parse_not_expression();
             left = ASTNode::create_children_node(BINARY_OP_NODE, {left, right, ASTNode(IDENTIFIER_NODE, operator_token.value)});
        }
          pop_traceback();
         return left;
    } catch (ParserError& e) {e.traceback = traceback; throw e;}
}
ASTNode PyLiteParser::parse_not_expression() {
   push_traceback("not_expression");
    try {
           if (match(KEYWORD, "not")) {
            Token operator_token = tokens[pos - 1];
            ASTNode right = parse_not_expression();
            pop_traceback();
            return ASTNode::create_children_node(UNARY_OP_NODE, {right, ASTNode(IDENTIFIER_NODE, operator_token.value)});
         }
        return parse_comparison();
    } catch (ParserError& e) {e.traceback = traceback; throw e;}
}
ASTNode PyLiteParser::parse_comparison() {
   push_traceback("comparison");
    try {
         ASTNode left = parse_addition();
           while(peek().type == OPERATOR && (peek().value == "<" || peek().value == ">" || peek().value == "<=" || peek().value == ">=" || peek().value == "==" || peek().value == "!=" )) {
             Token operator_token = consume();
            ASTNode right = parse_addition();
             left = ASTNode::create_children_node(BINARY_OP_NODE, {left, right, ASTNode(IDENTIFIER_NODE, operator_token.value)});
         }
          pop_traceback();
          return left;
    } catch (ParserError& e) { e.traceback = traceback; throw e;}
}


ASTNode PyLiteParser::parse_addition() {
    push_traceback("addition");
    try {
        ASTNode left = parse_multiplication();
           while (peek().type == OPERATOR && (peek().value == "+" || peek().value == "-")) {
            Token operator_token = consume();
             ASTNode right = parse_multiplication();
             left = ASTNode::create_children_node(BINARY_OP_NODE, {left, right, ASTNode(IDENTIFIER_NODE, operator_token.value)});
        }
         pop_traceback();
          return left;
    } catch (ParserError& e) { e.traceback = traceback; throw e; }
}
ASTNode PyLiteParser::parse_multiplication() {
  push_traceback("multiplication");
    try {
          ASTNode left = parse_unary();
            while (peek().type == OPERATOR && (peek().value == "*" || peek().value == "/" || peek().value == "//" || peek().value == "%" || peek().value == "**")) {
            Token operator_token = consume();
            ASTNode right = parse_unary();
            left = ASTNode::create_children_node(BINARY_OP_NODE, {left, right, ASTNode(IDENTIFIER_NODE, operator_token.value)});
        }
          pop_traceback();
           return left;
    } catch (ParserError& e) { e.traceback = traceback; throw e;}
}
ASTNode PyLiteParser::parse_unary() {
  push_traceback("unary");
    try {
          if (peek().type == OPERATOR && (peek().value == "-" || peek().value == "!")) {
            Token operator_token = consume();
            ASTNode right = parse_unary();
              pop_traceback();
           return ASTNode::create_children_node(UNARY_OP_NODE, {right, ASTNode(IDENTIFIER_NODE, operator_token.value)});
         }
         return parse_call_expression();
    } catch (ParserError& e) {e.traceback = traceback; throw e; }
}

ASTNode PyLiteParser::parse_call_expression() {
    push_traceback("call_expression");
    try {
         ASTNode left = parse_primary_expression();
            while (peek().type == OPERATOR && peek().value == "(") {
                consume();
                std::vector<ASTNode> arguments;
                   while(peek().type != OPERATOR || peek().value != ")"){
                         arguments.push_back(parse_expression());
                        if(match(OPERATOR, ",")) {}

                   }
                 require(OPERATOR, ")");
               left = ASTNode::create_children_node(FUNCTION_CALL_NODE, {left, ASTNode::create_children_node(IDENTIFIER_NODE, arguments)});
           }
           pop_traceback();
           return left;
    } catch (ParserError& e) {e.traceback = traceback; throw e;}
}

ASTNode PyLiteParser::parse_primary_expression() {
     try {
        if (peek().type == IDENTIFIER)  return ASTNode(IDENTIFIER_NODE, consume().value);
        else if (peek().type == LITERAL) return ASTNode(LITERAL_NODE, consume().value);
         else if (peek().type == INT) return ASTNode(INT_NODE, consume().value);
        else if (peek().type == FLOAT) return ASTNode(FLOAT_NODE, consume().value);
        else if (peek().type == STRING)  return ASTNode(STRING_NODE, consume().value);
        else if (peek().type == BOOLEAN) return ASTNode(BOOLEAN_NODE, consume().value);
         else if (peek().type == OPERATOR && peek().value == "(") {
             consume(); ASTNode expression_node = parse_expression(); require(OPERATOR, ")"); return expression_node;
         }
          else if(peek().type == OPERATOR && peek().value == "[") {
            return parse_set_expression();
         }
          std::stringstream ss; ss << "Unexpected token: " << peek().toString();
         throw ParserError(202, ss.str(), peek().line, traceback);
      } catch (ParserError& e) {e.traceback = traceback; throw e;}
}
ASTNode PyLiteParser::parse_import_statement(){
    push_traceback("import_statement");
    try{
          require(KEYWORD, "import");
           std::string module_name = require(IDENTIFIER).value;
            pop_traceback();
             return ASTNode(IMPORT_STATEMENT_NODE, module_name);
    } catch (ParserError& e){
         e.traceback = this->traceback;
        throw e;
    }
}
ASTNode PyLiteParser::parse_function_call(ASTNode left) {
     push_traceback("function_call");
    try {
        require(OPERATOR, "(");
        std::vector<ASTNode> arguments;
        if (peek().type != OPERATOR || peek().value != ")") {
            arguments.push_back(parse_expression());
            while (match(OPERATOR, ",")) arguments.push_back(parse_expression());
        }
        require(OPERATOR, ")");
         pop_traceback();
       return ASTNode::create_children_node(FUNCTION_CALL_NODE, {left, ASTNode::create_children_node(IDENTIFIER_NODE, arguments)});
    }
    catch(ParserError& e){
        e.traceback = this->traceback;
         throw e;
    }
}
ASTNode PyLiteParser::parse_dict_expression() {
     push_traceback("dict_expression");
    try {
          require(OPERATOR, "{");
        std::vector<ASTNode> key_value_pairs;
        if (peek().type != OPERATOR || peek().value != "}") {
            key_value_pairs.push_back(parse_expression());
            while (match(OPERATOR, ",")) key_value_pairs.push_back(parse_expression());
        }
        require(OPERATOR, "}");
          pop_traceback();
        return ASTNode::create_children_node(DICT_NODE, key_value_pairs);
    } catch (ParserError& e) { e.traceback = traceback; throw e; }
}

ASTNode PyLiteParser::parse_set_expression() {
    push_traceback("set_expression");
    try {
        require(OPERATOR, "[");
        std::vector<ASTNode> set_items;
        if(peek().type != OPERATOR || peek().value != "]"){
             set_items.push_back(parse_expression());
               while (match(OPERATOR, ",")) set_items.push_back(parse_expression());
        }
        require(OPERATOR, "]");
        pop_traceback();
         return ASTNode::create_set_node(SET_NODE, set_items);
    } catch (ParserError& e) {e.traceback = traceback; throw e;}
}