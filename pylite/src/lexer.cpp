#include "../include/lexer.h"
#include <iostream>
#include <stdexcept>
#include <cctype>
#include <cstring>
#include <sstream>

PyLiteLexer::PyLiteLexer(const std::string& source_code) : source_code(source_code) {}

std::vector<Token> PyLiteLexer::tokenize() {
    while (pos < source_code.length()) {
        char char_ = source_code[pos];
        if (isspace(char_)) {pos++; continue;}
         else if (char_ == '#') {while (pos < source_code.length() && source_code[pos] != '\n') pos++; pos++; line++; continue;}
        else if (isdigit(char_) || (char_ == '-' && isdigit(peek(1)))) {tokens.push_back(tokenize_number());}
        else if (isalpha(char_)) {tokens.push_back(tokenize_identifier());}
         else if (char_ == '"' || char_ == '\'') {tokens.push_back(tokenize_string(char_));}
        else if (strchr("+-*/%()=<>!:,;.", char_)) {tokens.push_back(tokenize_operator());}
        else if (char_ == '\n') {tokens.push_back(Token(NEWLINE, "\n", line)); pos++; line++;}
        else if(char_ == '[' || char_ == ']'){ tokens.push_back(Token(OPERATOR, std::string(1, char_), line)); pos++;}
         else {
           std::stringstream ss; ss << "Unexpected character '" << char_ << "' at position " << pos;
           throw LexerError(100, ss.str(), line);
         }
    }
     tokens.push_back(Token(EOF_TOKEN, line));
    return tokens;
}

char PyLiteLexer::peek(size_t offset) const {
    return (pos + offset < source_code.length()) ? source_code[pos + offset] : '\0';
}

Token PyLiteLexer::tokenize_number() {
    size_t start_pos = pos;
    bool decimal_point = false;
     while (pos < source_code.length() && (isdigit(source_code[pos]) || source_code[pos] == '.' || source_code[pos] == '-')) {
         if (source_code[pos] == '.') {
             if (decimal_point) {
                  std::stringstream ss; ss << "Invalid number at position " << start_pos;
                 throw LexerError(101, ss.str(), line);
             }
             decimal_point = true;
         }
          pos++;
     }
    std::string value = source_code.substr(start_pos, pos - start_pos);
    return decimal_point ? Token(FLOAT, value, line) : Token(INT, value, line);
}

Token PyLiteLexer::tokenize_identifier() {
      size_t start_pos = pos;
      while(pos < source_code.length() && (isalnum(source_code[pos]) || source_code[pos] == '_'))  pos++;
      std::string value = source_code.substr(start_pos, pos-start_pos);
       if (value == "if" || value == "elif" || value == "else" || value == "while" || value == "print" ||
            value == "and" || value == "or" || value == "not" || value == "True" || value == "False" ||
            value == "len" || value == "int" || value == "float" || value == "str" || value == "input" ||
             value == "def" || value == "return" || value == "yield" || value == "import") {
            return Token(KEYWORD, value, line);
        } else {
            return Token(IDENTIFIER, value, line);
        }
}

Token PyLiteLexer::tokenize_string(char quote_char) {
    pos++; size_t start_pos = pos;
    while(pos < source_code.length() && source_code[pos] != quote_char)  pos++;
      if (pos == source_code.length()) {
           std::stringstream ss;  ss << "Unterminated String at position " << start_pos;
           throw LexerError(102, ss.str(), line);
      }
      std::string value = source_code.substr(start_pos, pos - start_pos);
      pos++;
    return Token(STRING, value, line);
}

Token PyLiteLexer::tokenize_operator() {
    char char_ = source_code[pos];
    if (char_ == '=') {
        if (peek(1) == '=') { pos += 2; return Token(OPERATOR, "==", line); }
        else { pos++; return Token(OPERATOR, "=", line); }
    } else if (char_ == '!') {
         if (peek(1) == '=') { pos+=2; return Token(OPERATOR, "!=", line); }
         else { std::stringstream ss; ss << "Unexpected character '" << char_ << "' at position " << pos;
                 throw LexerError(103, ss.str(), line); }
    } else if (char_ == '<') {
         if (peek(1) == '=') { pos+=2; return Token(OPERATOR, "<=", line); }
         else { pos++; return Token(OPERATOR, "<", line); }
    }
    else if (char_ == '>') {
        if (peek(1) == '=') { pos+=2; return Token(OPERATOR, ">=", line); }
        else { pos++; return Token(OPERATOR, ">", line); }
    } else if (strchr(":;,.", char_)) {
        pos++; return Token(OPERATOR, std::string(1, char_), line);
    }
    else {
        pos++;
        return Token(OPERATOR, std::string(1, char_), line);
    }
}