#pragma once
#include <string>
#include <unordered_map>
#include <memory>
#include <stdexcept>
#include "value.h"

class Environment {
private:
    std::unordered_map<std::string, Value> values;
    std::shared_ptr<Environment> enclosing; // Trỏ về scope cha

public:
    Environment() : enclosing(nullptr) {}
    Environment(std::shared_ptr<Environment> enclosing) : enclosing(enclosing) {}

    void define(const std::string& name, Value value) {
        if (values.find(name) != values.end()) {
            throw std::runtime_error("Scope Error: Variable '" + name + "' already declared in this scope.");
        }
        values[name] = value;
    }

    void assign(const std::string& name, Value value) {
        if (values.find(name) != values.end()) {
            values[name] = value;
            return;
        }
        if (enclosing != nullptr) {
            enclosing->assign(name, value);
            return;
        }
        throw std::runtime_error("Scope Error: Undefined variable '" + name + "' during assignment.");
    }

    Value get(const std::string& name) {
        if (values.find(name) != values.end()) {
            return values.at(name);
        }
        if (enclosing != nullptr) {
            return enclosing->get(name);
        }
        throw std::runtime_error("Scope Error: Undefined variable '" + name + "'.");
    }
};