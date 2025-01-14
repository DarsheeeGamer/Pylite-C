#include "../include/ast.h"
#include <sstream>

std::string ASTNode::toString() const {
    std::stringstream ss;
    ss << "ASTNode(";

    // Switch based on node type and convert it to a string representation
    switch (type) {
        case INT_NODE: ss << "INT"; break;
        case FLOAT_NODE: ss << "FLOAT"; break;
        case STRING_NODE: ss << "STRING"; break;
        case BOOLEAN_NODE: ss << "BOOLEAN"; break;
        case IDENTIFIER_NODE: ss << "IDENTIFIER"; break;
        case KEYWORD_NODE: ss << "KEYWORD"; break;
        case OPERATOR_NODE: ss << "OPERATOR"; break;
        case NEWLINE_NODE: ss << "NEWLINE"; break;
        case ASSIGNMENT_NODE: ss << "ASSIGNMENT"; break;
        case UNARY_OP_NODE: ss << "UNARY_OP"; break;
        case BINARY_OP_NODE: ss << "BINARY_OP"; break;
        case PRINT_STATEMENT_NODE: ss << "PRINT_STATEMENT"; break;
        case IF_STATEMENT_NODE: ss << "IF_STATEMENT"; break;
        case WHILE_STATEMENT_NODE: ss << "WHILE_STATEMENT"; break;
        case CALL_EXPRESSION_NODE: ss << "CALL_EXPRESSION"; break;
        case FUNCTION_DEFINITION_NODE: ss << "FUNCTION_DEFINITION"; break;
        case RETURN_STATEMENT_NODE: ss << "RETURN_STATEMENT"; break;
        case YIELD_STATEMENT_NODE: ss << "YIELD_STATEMENT"; break;
        case DICT_NODE: ss << "DICT"; break;
        case SET_NODE: ss << "SET"; break;
        case LITERAL_NODE: ss << "LITERAL"; break;
        case FUNCTION_CALL_NODE: ss << "FUNCTION_CALL"; break;
           case IMPORT_STATEMENT_NODE: ss << "IMPORT_STATEMENT"; break;
        default: ss << "UNKNOWN"; break;
    }

    ss << ", " << value << ", [";

    // Print all children nodes
    for (size_t i = 0; i < children.size(); ++i) {
        ss << children[i].toString();
        if (i < children.size() - 1) ss << ", ";
    }

    // Print dictionary values if any
    if (!dict_value.empty()) {
        ss << ", {";
        for (auto it = dict_value.begin(); it != dict_value.end(); ++it) {
            ss << it->first << " : " << it->second.toString() << ", ";
        }
        ss << "}";
    }

    // Print set values if any
    if (!set_value.empty()) {
        ss << ", {";
        for (size_t i = 0; i < set_value.size(); ++i) {
            ss << set_value[i].toString();
            if (i < set_value.size() - 1) ss << ", ";
        }
        ss << "}";
    }

    ss << "])";
    return ss.str();
}

// Create a set node (set values)
ASTNode ASTNode::create_set_node(ASTNodeType type, std::vector<ASTNode> set_value, std::string value) {
    return ASTNode(type, std::move(set_value), value);  // Use the constructor for set nodes
}

// Create a node with children
ASTNode ASTNode::create_children_node(ASTNodeType type, std::vector<ASTNode> children) {
    // We create a temporary ASTNode and then move the children into it
   ASTNode temp(type);
   temp.children = std::move(children);
   return temp;

}

// Constructor for nodes with children
ASTNode::ASTNode(ASTNodeType type, std::vector<ASTNode> children)
    : type(type), value(""), children(std::move(children)) {}

// Constructor for nodes with no children
ASTNode::ASTNode(ASTNodeType type) : type(type), value(""){};

// Constructor for nodes with only type and value
ASTNode::ASTNode(ASTNodeType type, std::string value)
    : type(type), value(std::move(value)) {}

// Constructor for set nodes
ASTNode::ASTNode(ASTNodeType type, std::vector<ASTNode> set_value, std::string value)
    : type(type), value(std::move(value)), set_value(std::move(set_value)) {}

// Constructor for dictionary-based nodes
ASTNode::ASTNode(ASTNodeType type, std::map<std::string, ASTNode> dict_value)
    : type(type), dict_value(std::move(dict_value)) {}