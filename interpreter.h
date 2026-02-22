#pragma once
#include "ast.h"
#include "environment.h"
#include "value.h"
#include <vector>
#include <string>
#include <memory>

class Interpreter {
private:
    const std::vector<std::unique_ptr<Stmt>>& program;
    std::shared_ptr<Environment> environment; // Environment hi?n t?i

    void execute(const Stmt* stmt);
    void executeBlock(const std::vector<std::unique_ptr<Stmt>>& stmts);
    Value eval(const Expr* expr);

public:
    Interpreter(const std::vector<std::unique_ptr<Stmt>>& program);
    void run();
};