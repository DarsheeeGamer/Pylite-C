 // pylite/include/token.h
#pragma once

#include <string>

enum TokenType {
    INT,
    FLOAT,
    STRING,
    BOOLEAN,
    IDENTIFIER,
    KEYWORD,
    OPERATOR,
    NEWLINE,
    EOF_TOKEN
};

struct Token {
    TokenType type;
    std::string value;

    Token(TokenType type, std::string value) : type(type), value(value) {}
    Token(TokenType type) : type(type), value("") {}

    std::string toString() const;
};
