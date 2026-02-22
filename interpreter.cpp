#include "interpreter.h"
#include <iostream>

Interpreter::Interpreter(const std::vector<std::unique_ptr<Stmt>>& program)
    : program(program) {
    environment = std::make_shared<Environment>();
}

void Interpreter::run() {
    for (const auto& stmt : program) execute(stmt.get());
}

void Interpreter::execute(const Stmt* stmt) {
    if (auto d = dynamic_cast<const DeclareStmt*>(stmt)) {
        Value val = eval(d->value.get());
        environment->define(d->name, val);
    } 
    else if (auto a = dynamic_cast<const AssignStmt*>(stmt)) {
        Value val = eval(a->value.get());
        environment->assign(a->name, val);
    } 
    else if (auto p = dynamic_cast<const PrintStmt*>(stmt)) {
        for (const auto& expr : p->expressions) {
            std::cout << eval(expr.get()).toString();
        }
        std::cout << std::endl;
    } 
    else if (auto w = dynamic_cast<const WhileStmt*>(stmt)){
    	while (eval(w->condition.get()).isTruthy()){
    		executeBlock(w->body);
		}
	}
	else if (auto i = dynamic_cast<const IfStmt*>(stmt)) {
        if (eval(i->condition.get()).isTruthy()) {
            executeBlock(i->ifBlock);
        } else {
            bool done = false;
            for (size_t j = 0; j < i->elifConditions.size(); ++j) {
                if (eval(i->elifConditions[j].get()).isTruthy()) {
                    executeBlock(i->elifBlocks[j]);
                    done = true; break;
                }
            }
            if (!done && !i->elseBlock.empty()) executeBlock(i->elseBlock);
        }
    }
}

void Interpreter::executeBlock(const std::vector<std::unique_ptr<Stmt>>& stmts) {
    auto previous = environment;
    environment = std::make_shared<Environment>(previous);
    try {
        for (const auto& s : stmts) execute(s.get());
    } catch (...) {
        environment = previous; throw;
    }
    environment = previous;
}

Value Interpreter::eval(const Expr* expr) {
    if (auto n = dynamic_cast<const NumberExpr*>(expr)) return Value(n->value);
    if (auto f = dynamic_cast<const FloatExpr*>(expr)) return Value(f->value);
    if (auto s = dynamic_cast<const StringExpr*>(expr)) return Value(s->value);
    if (auto v = dynamic_cast<const VarExpr*>(expr)) return environment->get(v->name);

    if (auto b = dynamic_cast<const BinaryExpr*>(expr)) {
        Value L = eval(b->left.get());
        Value R = eval(b->right.get());

        if (b->op == "+") {
            if (L.type == ValueType::STRING || R.type == ValueType::STRING)
                return Value(L.toString() + R.toString());
            if (L.type == ValueType::FLOAT || R.type == ValueType::FLOAT)
                return Value(L.asFloat() + R.asFloat());
            return Value(L.i32 + R.i32);
        }
        if (b->op == "-") {
            if (L.type == ValueType::FLOAT || R.type == ValueType::FLOAT)
                return Value(L.asFloat() - R.asFloat());
            return Value(L.i32 - R.i32);
        }
        if (b->op == "*") {
            if (L.type == ValueType::FLOAT || R.type == ValueType::FLOAT)
                return Value(L.asFloat() * R.asFloat());
            return Value(L.i32 * R.i32);
        }
        if (b->op == "/") {
            if (L.type == ValueType::FLOAT || R.type == ValueType::FLOAT)
                return Value(L.asFloat() / R.asFloat());
            return Value(L.i32 / R.i32);
        }
        if (b->op == "==") {
            if (L.type == ValueType::STRING || R.type == ValueType::STRING) 
                return Value(L.toString() == R.toString());
            return Value(L.asFloat() == R.asFloat());
        }
    }
    return Value();
}