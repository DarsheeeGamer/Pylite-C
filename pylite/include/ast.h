// pylite/include/ast.h
#pragma once
#include <vector>
#include <string>

enum ASTNodeType {
    INT_NODE,
    FLOAT_NODE,
    STRING_NODE,
    BOOLEAN_NODE,
    IDENTIFIER_NODE,
    ASSIGNMENT_NODE,
    UNARY_OP_NODE,
    BINARY_OP_NODE,
    PRINT_STATEMENT_NODE,
    IF_STATEMENT_NODE,
    WHILE_STATEMENT_NODE,
    CALL_EXPRESSION_NODE,
    FUNCTION_DEFINITION_NODE,
    RETURN_STATEMENT_NODE,
};

struct ASTNode {
    ASTNodeType type;
    std::string value;
    std::vector<ASTNode> children;

    ASTNode() : type(IDENTIFIER_NODE) {} // Default constructor <------ THIS LINE WAS ADDED
    ASTNode(ASTNodeType type) : type(type), value("") {}
    ASTNode(ASTNodeType type, std::string value) : type(type), value(value) {}
    ASTNode(ASTNodeType type, std::vector<ASTNode> children) : type(type), value(""), children(children) {}
    ASTNode(ASTNodeType type, std::string value, std::vector<ASTNode> children) : type(type), value(value), children(children) {}
    std::string toString() const;

};