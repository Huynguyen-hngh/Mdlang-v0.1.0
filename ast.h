#pragma once
#include <string>
#include <vector>
#include <memory>

struct Expr { virtual ~Expr() = default; };

struct NumberExpr : Expr {
    int value;
    NumberExpr(int v) : value(v) {}
};

struct FloatExpr : Expr {
    double value;
    FloatExpr(double v) : value(v) {}
};

struct StringExpr : Expr {
    std::string value;
    StringExpr(const std::string& v) : value(v) {}
};

struct VarExpr : Expr {
    std::string name;
    VarExpr(const std::string& n) : name(n) {}
};

struct BinaryExpr : Expr {
    std::string op;
    std::unique_ptr<Expr> left, right;
    BinaryExpr(std::string o, std::unique_ptr<Expr> l, std::unique_ptr<Expr> r)
        : op(o), left(std::move(l)), right(std::move(r)) {}
};

struct Stmt { virtual ~Stmt() = default; };

struct DeclareStmt : Stmt {
    std::string type; 
    std::string name;
    std::unique_ptr<Expr> value;
    DeclareStmt(std::string t, std::string n, std::unique_ptr<Expr> v)
        : type(t), name(n), value(std::move(v)) {}
};

struct AssignStmt : Stmt {
    std::string name;
    std::unique_ptr<Expr> value;
    AssignStmt(std::string n, std::unique_ptr<Expr> v)
        : name(n), value(std::move(v)) {}
};

struct PrintStmt : Stmt {
    std::vector<std::unique_ptr<Expr>> expressions;
    PrintStmt(std::vector<std::unique_ptr<Expr>> exprs) : expressions(std::move(exprs)) {}
};

struct IfStmt : Stmt {
    std::unique_ptr<Expr> condition;
    std::vector<std::unique_ptr<Stmt>> ifBlock;
    std::vector<std::unique_ptr<Expr>> elifConditions;
    std::vector<std::vector<std::unique_ptr<Stmt>>> elifBlocks;
    std::vector<std::unique_ptr<Stmt>> elseBlock;
};

// Đã thêm: WhileStmt
struct WhileStmt : Stmt {
    std::unique_ptr<Expr> condition;
    std::vector<std::unique_ptr<Stmt>> body;

    WhileStmt(std::unique_ptr<Expr> cond, std::vector<std::unique_ptr<Stmt>> b)
        : condition(std::move(cond)), body(std::move(b)) {}
};