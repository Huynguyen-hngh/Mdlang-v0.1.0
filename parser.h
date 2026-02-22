#pragma once
#include <vector>
#include <memory>
#include "lexer.h"
#include "ast.h"

class Parser {
public:
    Parser(const std::vector<Token>& tokens);
    std::vector<std::unique_ptr<Stmt>> parse();

private:
    const std::vector<Token>& tokens;
    size_t pos;

    const Token& peek();
    const Token& advance();
    bool match(TokenType type);

    std::unique_ptr<Stmt> parseStatement();
    std::unique_ptr<Stmt> parseDeclare();
    std::unique_ptr<Stmt> parsePrint();
    std::unique_ptr<Stmt> parseIf();
    std::unique_ptr<Stmt> parseAssign();
    std::unique_ptr<Stmt> parseWhile();
    std::unique_ptr<Expr> parseExpression();
    std::unique_ptr<Expr> parseEquality();
    std::unique_ptr<Expr> parseTerm();
    std::unique_ptr<Expr> parseFactor();
    std::unique_ptr<Expr> parsePrimary();
};