// pylite/src/ast.cpp
#include "../include/ast.h"
#include <sstream>

std::string ASTNode::toString() const {
    std::stringstream ss;
    ss << "ASTNode(";
    switch (type) {
        case INT_NODE: ss << "INT"; break;
        case FLOAT_NODE: ss << "FLOAT"; break;
        case STRING_NODE: ss << "STRING"; break;
        case BOOLEAN_NODE: ss << "BOOLEAN"; break;
        case IDENTIFIER_NODE: ss << "IDENTIFIER"; break;
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
        default: ss << "UNKNOWN"; break;
    }
    ss << ", " << value << ", [";
    for (size_t i = 0; i < children.size(); ++i) {
        ss << children[i].toString();
        if (i < children.size() - 1) ss << ", ";
    }
       if(!dict_value.empty()){
        ss << ", {";
          for (auto it = dict_value.begin(); it != dict_value.end(); ++it)
               ss << it->first << " : " << it->second.toString() << ", ";
           ss << "}";
       }
          if(!set_value.empty()){
            ss << ", {";
            for(size_t i=0; i < set_value.size(); ++i){
                 ss << set_value[i].toString();
               if (i < set_value.size() - 1) ss << ", ";
             }
           ss << "}";
       }
    ss << "])";
    return ss.str();
}