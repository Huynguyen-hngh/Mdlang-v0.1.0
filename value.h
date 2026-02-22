#pragma once
#include <string>
#include <stdexcept>

enum class ValueType { INTEGER, FLOAT, STRING, BOOLEAN, NIL };

struct Value {
    ValueType type;
    int i32;
    double f64;
    std::string s;
    bool b;

    Value() : type(ValueType::NIL) {}
    Value(int v) : type(ValueType::INTEGER), i32(v) {}
    Value(double v) : type(ValueType::FLOAT), f64(v) {}
    Value(std::string v) : type(ValueType::STRING), s(v) {}
    Value(bool v) : type(ValueType::BOOLEAN), b(v) {}

    bool isTruthy() const {
        if (type == ValueType::NIL) return false;
        if (type == ValueType::BOOLEAN) return b;
        return true;
    }

    std::string toString() const {
        if (type == ValueType::INTEGER) return std::to_string(i32);
        if (type == ValueType::FLOAT) {
            std::string res = std::to_string(f64);
            res.erase(res.find_last_not_of('0') + 1, std::string::npos);
            if (res.back() == '.') res.pop_back();
            return res;
        }
        if (type == ValueType::STRING) return s;
        if (type == ValueType::BOOLEAN) return b ? "true" : "false";
        return "nil";
    }

    double asFloat() const {
        if (type == ValueType::FLOAT) return f64;
        if (type == ValueType::INTEGER) return (double)i32;
        throw std::runtime_error("Cannot convert to float");
    }
};