// pylite/src/lexer.cpp
#include "../include/lexer.h"
#include <iostream>
#include <stdexcept>
#include <cctype>

PyLiteLexer::PyLiteLexer(const std::string& source_code) : source_code(source_code), pos(0) {}

std::vector<Token> PyLiteLexer::tokenize() {
    while (pos < source_code.length()) {
        char char_ = source_code[pos];
        if (isspace(char_)) {
            pos++;
            continue;
        }
         else if (char_ == '#') {
            while (pos < source_code.length() && source_code[pos] != '\n') {
                pos++;
            }
            pos++;
            continue;
        }
        else if (isdigit(char_) || (char_ == '-' && isdigit(peek(1)))) {
             tokens.push_back(tokenize_number());
        }
        else if (isalpha(char_)) {
            tokens.push_back(tokenize_identifier());
        }
         else if (char_ == '"' || char_ == '\'') {
            tokens.push_back(tokenize_string(char_));
        }
        else if (strchr("+-*/%()=<>!:,;.{}]", char_)) {
             tokens.push_back(tokenize_operator());
        }
        else if (char_ == '\n') {
            tokens.push_back(Token(NEWLINE, "\n"));
            pos++;
        }
         else {
            throw std::runtime_error("Unexpected character '" + std::string(1, char_) + "' at position " + std::to_string(pos));
        }
    }
     tokens.push_back(Token(EOF_TOKEN));
    return tokens;
}

char PyLiteLexer::peek(size_t offset) const {
    if (pos + offset < source_code.length()) {
        return source_code[pos + offset];
    }
    return '\0';
}

Token PyLiteLexer::tokenize_number() {
    size_t start_pos = pos;
    bool decimal_point = false;
     while (pos < source_code.length() && (isdigit(source_code[pos]) || source_code[pos] == '.' || source_code[pos] == '-')) {
         if (source_code[pos] == '.') {
             if (decimal_point) {
                 throw std::runtime_error("Invalid number at position " + std::to_string(start_pos));
             }
             decimal_point = true;
         }
          pos++;
     }

    std::string value = source_code.substr(start_pos, pos - start_pos);
    if (decimal_point) {
        return Token(FLOAT, value);
    } else {
        return Token(INT, value);
    }
}

Token PyLiteLexer::tokenize_identifier() {
      size_t start_pos = pos;
      while(pos < source_code.length() && (isalnum(source_code[pos]) || source_code[pos] == '_')){
          pos++;
      }
      std::string value = source_code.substr(start_pos, pos-start_pos);
       if (value == "if" || value == "elif" || value == "else" || value == "while" || value == "print" ||
            value == "and" || value == "or" || value == "not" || value == "True" || value == "False" ||
            value == "len" || value == "int" || value == "float" || value == "str" || value == "input" ||
            value == "def" || value == "return" || value == "yield" || value == "dict" || value == "set" || value == "bool") {
            return Token(KEYWORD, value);
        } else {
            return Token(IDENTIFIER, value);
        }
}

Token PyLiteLexer::tokenize_string(char quote_char) {
    pos++;
    size_t start_pos = pos;
     while(pos < source_code.length() && source_code[pos] != quote_char){
         pos++;
     }
      if (pos == source_code.length()) {
          throw std::runtime_error("Unterminated String at position " + std::to_string(start_pos));
      }
      std::string value = source_code.substr(start_pos, pos - start_pos);
      pos++;
    return Token(STRING, value);

}
Token PyLiteLexer::tokenize_operator() {
    char char_ = source_code[pos];
    if (char_ == '=') {
        if (peek(1) == '=') {
            pos += 2;
            return Token(OPERATOR, "==");
        } else {
            pos++;
            return Token(OPERATOR, "=");
        }
    } else if (char_ == '!') {
          if (peek(1) == '=') {
              pos+=2;
              return Token(OPERATOR, "!=");
          } else {
               throw std::runtime_error("Unexpected character '" + std::string(1, char_) + "' at position " + std::to_string(pos));
          }
    } else if (char_ == '<') {
          if (peek(1) == '=') {
                pos+=2;
                return Token(OPERATOR, "<=");
          }
          else {
                pos++;
                return Token(OPERATOR, "<");
          }
    }
    else if (char_ == '>') {
        if (peek(1) == '=') {
              pos+=2;
              return Token(OPERATOR, ">=");
        }
        else {
              pos++;
              return Token(OPERATOR, ">");
        }
     } else if (strchr(":;,.", char_)) {
         pos++;
         return Token(OPERATOR, std::string(1, char_));
     } else if (strchr("{}:[]", char_)){
       pos++;
        return Token(OPERATOR, std::string(1, char_));
    }
    else {
        pos++;
        return Token(OPERATOR, std::string(1, char_));
    }
}