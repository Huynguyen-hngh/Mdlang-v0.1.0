#include "lexer.h"
#include <cctype>

Lexer::Lexer(const std::string& s) : src(s), pos(0) {}

char Lexer::peek() { return (pos >= src.size()) ? '\0' : src[pos]; }
char Lexer::peekNext() { return (pos + 1 >= src.size()) ? '\0' : src[pos + 1]; }
char Lexer::advance() { return (pos >= src.size()) ? '\0' : src[pos++]; }

void Lexer::skipWhitespace() {
    while (pos < src.size() && isspace(peek())) advance();
}

Token Lexer::identifier() {
    std::string v;
    while (isalnum(peek()) || peek() == '_') v += advance();

    if (v == "func") return {TokenType::KEYWORD_FUNC, v};
    if (v == "if") return {TokenType::KEYWORD_IF, v};
    if (v == "elif") return {TokenType::KEYWORD_ELIF, v};
    if (v == "else") return {TokenType::KEYWORD_ELSE, v};
    if (v == "while") return {TokenType::KEYWORD_WHILE, v}; // Thêm nhận diện
    if (v == "integer") return {TokenType::KEYWORD_INTEGER, v};
    if (v == "float") return {TokenType::KEYWORD_FLOAT, v};
    if (v == "string") return {TokenType::KEYWORD_STRING, v};
    if (v == "println") return {TokenType::KEYWORD_PRINTLN, v};
    if (v == "linedone") return {TokenType::LINEDONE, v};
    
    return {TokenType::IDENTIFIER, v};
}

Token Lexer::number() {
    std::string v;
    while (isdigit(peek())) v += advance();
    if (peek() == '.' && isdigit(peekNext())) {
        v += advance();
        while (isdigit(peek())) v += advance();
        return {TokenType::FLOAT_LITERAL, v};
    }
    return {TokenType::NUMBER, v};
}

Token Lexer::string() {
    advance(); // bỏ qua " mở đầu
    std::string v;
    while (peek() != '"' && peek() != '\0') v += advance();
    advance(); // bỏ qua " kết thúc
    return {TokenType::STRING, v};
}

std::vector<Token> Lexer::tokenize() {
    std::vector<Token> t;
    while (pos < src.size()) {
        skipWhitespace();
        char c = peek();
        if (c == '\0') break;

        if (isalpha(c)) t.push_back(identifier());
        else if (isdigit(c)) t.push_back(number());
        else if (c == '"') t.push_back(string());
        else if (c == '+') { advance(); t.push_back({TokenType::PLUS, "+"}); }
        else if (c == '-') { advance(); t.push_back({TokenType::MINUS, "-"}); }
        else if (c == '*') { advance(); t.push_back({TokenType::STAR, "*"}); }
        else if (c == '/') { advance(); t.push_back({TokenType::SLASH, "/"}); }
        else if (c == '=' && peekNext() == '=') {
            advance(); advance();
            t.push_back({TokenType::EQEQ, "=="});
        }
        else if (c == '=') { advance(); t.push_back({TokenType::EQUAL, "="}); }
        else if (c == '<' && peekNext() == '<') {
            advance(); advance();
            t.push_back({TokenType::SHIFT, "<<"});
        }
        else if (c == '(') { advance(); t.push_back({TokenType::LPAREN, "("}); }
        else if (c == ')') { advance(); t.push_back({TokenType::RPAREN, ")"}); }
        else if (c == '{') { advance(); t.push_back({TokenType::LBRACE, "{"}); }
        else if (c == '}') { advance(); t.push_back({TokenType::RBRACE, "}"}); }
        else if (c == ';') { advance(); t.push_back({TokenType::SEMICOLON, ";"}); }
        else advance();
    }
    t.push_back({TokenType::END_OF_FILE, ""});
    return t;
}