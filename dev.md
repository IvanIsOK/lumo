# 🌱 Lumo Language

Lumo is a lightweight compiled programming language designed to be simple, fast, and extensible.

It compiles to native executables using a C-based compiler.

---

## 📦 File Extension

```
.lumo
```

Example:

```
main.lumo
math.lumo
utils.lumo
```

---

## ⚙️ Build System

Lumo uses a single compiler:

```
compiler.c → lumo compiler
```

Compiled with:

```bash
gcc compiler.c -o lumo
```

---

## 🚀 Running a Program

```bash
./lumo main.lumo
```

This will:

- preprocess includes  
- compile Lumo → C  
- run GCC automatically  
- output executable program  

---

## 📂 Example Project Structure

```
project/
 ├── compiler.c
 ├── main.lumo
 ├── math.lumo
 ├── utils.lumo
 └── dev.md
```

---

## 📌 Language Syntax

### Variables

```
let x = 10;
```

### Print

```
print x;
```

### If

```
if x < 10 {
    print x;
}
```

### While

```
while x > 0 {
    x = x - 1;
}
```

---

## 📥 Includes

Lumo supports file includes:

```
#include "math.lumo"
#include "utils.lumo"
```

### Behavior

- Includes are processed BEFORE compilation  
- Files are merged into one compilation unit  
- Works like C includes (but simpler)  

---

## ⚠️ Notes

- Circular includes are not yet prevented  
- Includes are textual (not module-based yet)  
- No separate compilation units yet  

---

## 🧠 Compiler Pipeline

```
.lumo source
    ↓
preprocessor (#include)
    ↓
merged source
    ↓
C generator
    ↓
gcc
    ↓
binary (program)
```
