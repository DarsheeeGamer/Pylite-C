// pylite/include/lexer.h
#pragma once
#include <vector>
#include <string>
#include "../include/token.h"

class PyLiteLexer {
public:
    PyLiteLexer(const std::string& source_code);
    std::vector<Token> tokenize();

private:
    const std::string& source_code;
    size_t pos;
    std::vector<Token> tokens;

    char peek(size_t offset) const;
    Token tokenize_number();
    Token tokenize_identifier();
    Token tokenize_string(char quote_char);
    Token tokenize_operator();
};
