// pylite/src/token.cpp
#include "../include/token.h"

#include <sstream>

std::string Token::toString() const {
    std::stringstream ss;
    ss << "Token(";
    switch (type) {
        case INT: ss << "INT"; break;
        case FLOAT: ss << "FLOAT"; break;
        case STRING: ss << "STRING"; break;
        case BOOLEAN: ss << "BOOLEAN"; break;
        case IDENTIFIER: ss << "IDENTIFIER"; break;
        case KEYWORD: ss << "KEYWORD"; break;
        case OPERATOR: ss << "OPERATOR"; break;
        case NEWLINE: ss << "NEWLINE"; break;
        case EOF_TOKEN: ss << "EOF"; break;
        default: ss << "UNKNOWN"; break;
    }
    ss << ", " << value << ")";
    return ss.str();
}
