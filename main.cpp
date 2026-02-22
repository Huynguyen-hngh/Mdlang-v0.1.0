#include <fstream>
#include <sstream>
#include <iostream>
#include "lexer.h"
#include "parser.h"
#include "interpreter.h"

int main() {
    std::ifstream file("test.mdl");
    if (!file) {
        std::cerr << "Cannot open test.mdl\n";
        return 1;
    }
    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string source = buffer.str();

    Lexer lexer(source);
    auto tokens = lexer.tokenize();

    Parser parser(tokens);
    auto program = parser.parse(); // program lúc này là std::vector<std::unique_ptr<Stmt>>

    Interpreter interpreter(program);
    interpreter.run();

    return 0;
}