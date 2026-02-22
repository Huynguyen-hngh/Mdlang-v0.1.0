#pragma once
#include <string>
#include <vector>

enum class TokenType {
    IDENTIFIER, NUMBER, FLOAT_LITERAL, STRING,
    KEYWORD_FUNC, KEYWORD_INTEGER, KEYWORD_FLOAT, KEYWORD_STRING,
    KEYWORD_PRINTLN, KEYWORD_IF, KEYWORD_ELIF, KEYWORD_ELSE,
    KEYWORD_WHILE, // Thêm keyword mới
    LINEDONE,
    LPAREN, RPAREN, LBRACE, RBRACE, SEMICOLON,
    EQUAL, PLUS, MINUS, STAR, SLASH, EQEQ, SHIFT,
    END_OF_FILE
};

struct Token {
    TokenType type;
    std::string value;
    Token(TokenType t, const std::string& v) : type(t), value(v) {}
};

class Lexer {
public:
    Lexer(const std::string& src);
    std::vector<Token> tokenize();
private:
    std::string src;
    size_t pos = 0;
    char peek();
    char peekNext();
    char advance();
    void skipWhitespace();
    Token identifier();
    Token number();
    Token string();
};