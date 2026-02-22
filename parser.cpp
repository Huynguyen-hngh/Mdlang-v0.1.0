#include "parser.h"
#include <stdexcept>

Parser::Parser(const std::vector<Token>& t) : tokens(t), pos(0) {}

const Token& Parser::peek() { 
    if (pos >= tokens.size()) return tokens.back();
    return tokens[pos]; 
}

const Token& Parser::advance() { 
    const Token& t = peek();
    if (pos < tokens.size()) pos++;
    return t; 
}

bool Parser::match(TokenType t) { 
    if (peek().type == t) { advance(); return true; } 
    return false; 
}

std::vector<std::unique_ptr<Stmt>> Parser::parse() {
    std::vector<std::unique_ptr<Stmt>> program;
    while (peek().type != TokenType::END_OF_FILE) {
        if (match(TokenType::KEYWORD_FUNC)) {
            advance(); // bỏ qua tên hàm
            match(TokenType::LPAREN); match(TokenType::RPAREN);
            match(TokenType::LBRACE);
            while (peek().type != TokenType::RBRACE && peek().type != TokenType::END_OF_FILE) {
                program.push_back(parseStatement());
            }
            match(TokenType::RBRACE);
        } else {
            advance();
        }
    }
    return program;
}

std::unique_ptr<Stmt> Parser::parseStatement() {
    TokenType t = peek().type;
    if (t == TokenType::KEYWORD_INTEGER || t == TokenType::KEYWORD_FLOAT || t == TokenType::KEYWORD_STRING) 
        return parseDeclare();
    if (t == TokenType::KEYWORD_IF) return parseIf();
    if (t == TokenType::KEYWORD_WHILE) return parseWhile();
    if (t == TokenType::KEYWORD_PRINTLN) return parsePrint();
    
    return parseAssign();
}

std::unique_ptr<Stmt> Parser::parseDeclare() {
    std::string type = advance().value; // integer, float, or string
    std::string name = advance().value;
    match(TokenType::EQUAL);
    auto value = parseExpression();
    match(TokenType::SEMICOLON);
    return std::make_unique<DeclareStmt>(type, name, std::move(value));
}

std::unique_ptr<Stmt> Parser::parseAssign() {
    std::string name = advance().value;
    match(TokenType::EQUAL);
    auto value = parseExpression();
    match(TokenType::SEMICOLON);
    return std::make_unique<AssignStmt>(name, std::move(value));
}

std::unique_ptr<Stmt> Parser::parsePrint() {
    advance(); // skip println
    std::vector<std::unique_ptr<Expr>> exprs;
    while (match(TokenType::SHIFT)) { // match <<
        if (peek().type == TokenType::LINEDONE) {
            advance(); // handle linedone
        } else {
            exprs.push_back(parseExpression());
        }
    }
    match(TokenType::SEMICOLON);
    return std::make_unique<PrintStmt>(std::move(exprs));
}

std::unique_ptr<Stmt> Parser::parseIf() {
    advance(); // skip if
    match(TokenType::LPAREN);
    auto condition = parseExpression();
    match(TokenType::RPAREN);
    
    match(TokenType::LBRACE);
    std::vector<std::unique_ptr<Stmt>> ifBlock;
    while (peek().type != TokenType::RBRACE) ifBlock.push_back(parseStatement());
    match(TokenType::RBRACE);

    auto stmt = std::make_unique<IfStmt>();
    stmt->condition = std::move(condition);
    stmt->ifBlock = std::move(ifBlock);

    while (match(TokenType::KEYWORD_ELIF)) {
        match(TokenType::LPAREN);
        stmt->elifConditions.push_back(parseExpression());
        match(TokenType::RPAREN);
        match(TokenType::LBRACE);
        std::vector<std::unique_ptr<Stmt>> elifBlock;
        while (peek().type != TokenType::RBRACE) elifBlock.push_back(parseStatement());
        match(TokenType::RBRACE);
        stmt->elifBlocks.push_back(std::move(elifBlock));
    }

    if (match(TokenType::KEYWORD_ELSE)) {
        match(TokenType::LBRACE);
        while (peek().type != TokenType::RBRACE) stmt->elseBlock.push_back(parseStatement());
        match(TokenType::RBRACE);
    }

    return stmt;
}

std::unique_ptr<Stmt> Parser::parseWhile() {
    advance(); // skip while
    match(TokenType::LPAREN);
    auto condition = parseExpression();
    match(TokenType::RPAREN);
    match(TokenType::LBRACE);
    std::vector<std::unique_ptr<Stmt>> body;
    while (peek().type != TokenType::RBRACE) body.push_back(parseStatement());
    match(TokenType::RBRACE);
    return std::make_unique<WhileStmt>(std::move(condition), std::move(body));
}

// Expressions parsing
std::unique_ptr<Expr> Parser::parseExpression() {
    return parseEquality();
}

std::unique_ptr<Expr> Parser::parseEquality() {
    auto left = parseTerm();
    while (peek().type == TokenType::EQEQ) {
        std::string op = advance().value;
        left = std::make_unique<BinaryExpr>(op, std::move(left), parseTerm());
    }
    return left;
}

std::unique_ptr<Expr> Parser::parseTerm() {
    auto left = parseFactor();
    while (peek().type == TokenType::PLUS || peek().type == TokenType::MINUS) {
        std::string op = advance().value;
        left = std::make_unique<BinaryExpr>(op, std::move(left), parseFactor());
    }
    return left;
}

std::unique_ptr<Expr> Parser::parseFactor() {
    auto left = parsePrimary();
    while (peek().type == TokenType::STAR || peek().type == TokenType::SLASH) {
        std::string op = advance().value;
        left = std::make_unique<BinaryExpr>(op, std::move(left), parsePrimary());
    }
    return left;
}

std::unique_ptr<Expr> Parser::parsePrimary() {
    Token t = advance();
    if (t.type == TokenType::NUMBER) return std::make_unique<NumberExpr>(std::stoi(t.value));
    if (t.type == TokenType::FLOAT_LITERAL) return std::make_unique<FloatExpr>(std::stod(t.value));
    if (t.type == TokenType::STRING) return std::make_unique<StringExpr>(t.value);
    if (t.type == TokenType::IDENTIFIER) return std::make_unique<VarExpr>(t.value);
    
    throw std::runtime_error("Unexpected token in expression: " + t.value);
}