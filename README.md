# Mdlang — A Programming Language for Mathematics

> Mdlang is an experimental programming language designed to express **mathematics directly as code**, not force mathematics into general-purpose programming syntax.

---

##  Vision

Most programming languages are built for software engineering.
Mdlang is built for **mathematical thinking**.

We want a language where writing code feels closer to:

* writing equations
* defining transformations
* expressing structures
* reasoning symbolically

Instead of:

* managing variables
* mutating state
* writing boilerplate loops

Mdlang explores what happens if a language is designed **for math first, programming second.**

---

##  Project Goals

Mdlang aims to become a lightweight platform for:

* Symbolic computation
* Exact arithmetic (not float-by-default)
* Algebraic transformations
* Functional mathematical modeling
* Clean expression trees
* Research and education in language design

This is **NOT** meant to compete with existing languages.
This is a playground for exploring new ideas in mathematical computation.

---

##  Design Philosophy

Mdlang follows these principles:

1. **Mathematics is immutable by nature**
   → Prefer expressions over state mutation.

2. **Symbolic before numeric**
   → `x^2 + 2x + 1` should exist as structure, not just a number.

3. **Minimal syntax, maximal meaning**
   → Avoid ceremony. Prefer declarative constructs.

4. **Expressions over statements**
   → Everything should evaluate cleanly.

5. **Language as a mathematical tool, not a scripting tool**

---

##  Current State (v0.1)

Mdlang currently includes:

* Lexer
* Parser
* AST construction
* Tree-walking interpreter
* Basic numeric & string handling
* Expression evaluation
* `println` output

This is an early foundation to experiment with semantics and structure.

---

##  Roadmap

We are actively exploring how Mdlang should evolve.

### Core Language

* [ ] Immutable bindings
* [ ] First-class functions
* [ ] Expression-only evaluation model
* [ ] Pattern matching
* [ ] Lazy evaluation options

### Mathematical Features

* [ ] Rational / exact number system
* [ ] Symbolic algebra engine
* [ ] Built-in summation / product constructs
* [ ] Tensor-style expressions
* [ ] Transformation rules (rewrite system)

### Runtime / Architecture

* [ ] Bytecode VM
* [ ] Optimized evaluator for symbolic trees
* [ ] Pluggable math backends

---

##  Open Research Questions

We intentionally leave many questions open:

* Should Mdlang allow reassignment at all?
* How should symbolic values coexist with computed ones?
* What is the minimal core calculus?
* How do we represent infinite series?
* Should evaluation be strict, lazy, or hybrid?

Contributors are encouraged to help shape these answers.

---

## Contributing

We welcome contributors interested in:

* Programming language design
* Compilers / interpreters
* Symbolic computation
* Functional programming theory
* Mathematical structures

This project is **design-driven**, not just implementation-driven.

Before writing code, open a discussion or issue to explore the idea.

---

##  Building

```bash
git clone https://github.com/Huynguyen-hngh/Mdlang-v0.1.0
cd Mdlang-v0.1.0
mkdir build && cd build
cmake ..
make
```

---

## Why Mdlang Exists

Because mathematics deserves a language that understands it natively.

---

##  Status

Mdlang is experimental and unstable.
Expect breaking changes as the design evolves.

---

If you are curious about language design for mathematics,
join the discussion — the language is still being invented.
