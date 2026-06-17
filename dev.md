# 🌱 Lumo — Developer Documentation

Lumo is a **real compiled programming language** written in C.

It compiles directly to **x86_64 assembly**, then to a native executable.

---

# ⚙️ Compilation Pipeline

```
.lumo source
    ↓
lexer (C)
    ↓
parser (minimal AST)
    ↓
assembly generator
    ↓
nasm
    ↓
ld
    ↓
native executable
```

---

# 📦 File Extension

```
.lumo
```

---

# 🚀 How to Build Compiler

```bash
gcc compiler.c -o lumo
```

---

# 🚀 How to Compile a Program

```bash
./lumo main.lumo
```

This produces:

```
program
```

---

# ▶️ Run Program

```bash
./program
```

---

# 📌 Language Syntax (v2)

## Variables

```lumo
let x = 10;
```

Only one variable currently exists:

```
x
```

---

## Print

```lumo
print x;
```

---

# ⚠️ Current Limitations

Lumo is early-stage:

- Only supports integer variable `x`
- No expressions (`x + y` not supported yet)
- No functions
- No if/while
- Print is raw syscall-based
- Very minimal parser

---

# 🧠 Internal Design

## Lexer
Converts text → tokens:
- let
- print
- numbers
- identifiers

## Code Generator
Directly emits x86_64 assembly:

```
mov qword [x], 10
```

---

# 🔮 Roadmap

### v3
- multiple variables
- expressions
- stack memory

### v4
- if / while
- functions

### v5
- proper type system
- strings

### v6
- full standard library

---

# 💡 Design Philosophy

Lumo is built to be:

- minimal
- fast
- easy to compile
- close to hardware
