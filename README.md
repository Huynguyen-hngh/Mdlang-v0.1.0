
# MDlang (v0.1.0)

A tiny interpreted programming language written in C++20.

## Features

* Lexer / Parser / AST
* Tree-walking interpreter
* Dynamic values (number, string)
* Basic arithmetic + function call (`println`)
* Custom `.mdl` script execution

## Build

```bash
g++ -std=c++20 -Wall -Wextra -Wpedantic -O2 -I. *.cpp -o mdlang.exe
```

## Run

```bash
mdlang.exe test.mdl
```

## Example

```
println << "Hello Mdlang" << linedone;
```

## Roadmap

* [ ] Variables
* [ ] Control flow (`if`)
* [ ] Functions
* [ ] Bytecode VM
