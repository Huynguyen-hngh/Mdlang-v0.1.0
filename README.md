
# MDlang (v0.0.1)

A tiny interpreted programming language written in C++20.

## Features

* Lexer / Parser / AST
* Tree-walking interpreter
* Dynamic values (number, string)
* Basic arithmetic + function call (`print`)
* Custom `.mdl` script execution

## Build

```bash
g++ -std=c++20 -Wall -Wextra -Wpedantic -O2 -I. *.cpp -o mdlang
```

## Run

```bash
./mdlang test.mdl
```

## Example

```
print("Hello MDlang")
print(3.14 * 10)
```

## Roadmap

* [ ] Variables
* [ ] Control flow (`if`)
* [ ] Functions
* [ ] Bytecode VM
