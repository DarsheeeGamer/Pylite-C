#pragma once
#include <vector>
#include <map>
#include <string>

// Define the AST node types
enum ASTNodeType {
    INT_NODE,
    FLOAT_NODE,
    STRING_NODE,
    BOOLEAN_NODE,
    IDENTIFIER_NODE,
    KEYWORD_NODE,
    OPERATOR_NODE,
    NEWLINE_NODE,
    ASSIGNMENT_NODE,
    UNARY_OP_NODE,
    BINARY_OP_NODE,
    PRINT_STATEMENT_NODE,
    IF_STATEMENT_NODE,
    WHILE_STATEMENT_NODE,
    CALL_EXPRESSION_NODE,
    FUNCTION_DEFINITION_NODE,
    RETURN_STATEMENT_NODE,
    YIELD_STATEMENT_NODE,
    DICT_NODE,
    SET_NODE,
    LITERAL_NODE,
    FUNCTION_CALL_NODE,
     IMPORT_STATEMENT_NODE
};

// Forward declaration for ASTNode
struct ASTNode {
    ASTNodeType type;
    std::string value;
    std::vector<ASTNode> children;
    std::vector<ASTNode> set_value;       // For nodes that represent sets
    std::map<std::string, ASTNode> dict_value;  // For dictionary-based nodes

    // Constructor for nodes with children
    ASTNode(ASTNodeType type, std::vector<ASTNode> children);
     // Constructor for nodes with no children and no value
    ASTNode(ASTNodeType type);
     // Constructor for nodes with only type and value
    ASTNode(ASTNodeType type, std::string value);
    // Constructor for set nodes
    ASTNode(ASTNodeType type, std::vector<ASTNode> set_value, std::string value = "");

    // Constructor for dictionary-based nodes
    ASTNode(ASTNodeType type, std::map<std::string, ASTNode> dict_value);

    // Default constructor
    ASTNode() : type(IDENTIFIER_NODE), value("") {}

    // Function to convert ASTNode to a string for debugging/printing
    std::string toString() const;

    // Helper functions to create nodes
    static ASTNode create_set_node(ASTNodeType type, std::vector<ASTNode> set_value, std::string value = "");
    static ASTNode create_children_node(ASTNodeType type, std::vector<ASTNode> children);
};