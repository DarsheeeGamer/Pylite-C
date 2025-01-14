#pragma once
#include <vector>
#include <string>
#include "../include/token.h"
#include <stdexcept>

class LexerError : public std::runtime_error {
public:
    LexerError(int code, const std::string& message, int line)
        : std::runtime_error(message), code(code), line(line) {}
    int code;
    int line;
};

class PyLiteLexer {
public:
    PyLiteLexer(const std::string& source_code);
    std::vector<Token> tokenize();
private:
    const std::string& source_code;
    size_t pos = 0;
    std::vector<Token> tokens;
    int line = 1;
    char peek(size_t offset) const;
    Token tokenize_number();
    Token tokenize_identifier();
    Token tokenize_string(char quote_char);
    Token tokenize_operator();
};