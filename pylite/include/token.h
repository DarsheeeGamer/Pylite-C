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
    EOF_TOKEN,
    LITERAL
};

struct Token {
    TokenType type;
    std::string value;
    int line;

    Token(TokenType type, std::string value, int line) : type(type), value(value), line(line) {}
    Token(TokenType type, int line) : type(type), value(""), line(line) {}
     Token(TokenType type) : type(type), value(""), line(0) {}

    std::string toString() const;
};