# The basic syntax

* VariantC syntax is very similar to C/C++ and a mix of some C# and other language concepts.

** Here is a basic hello world program (subject to change with std library)


# Syntax Basics

## 1. Introduction
    - In this document we will cover some basics about the language.
    - For more specific information refer to the specific lang doc on the feature you want to learn more about.

## 2. Basic Program Structure
   - Example: Hello, World!
```
import std::io;

def main() void {
    printf("hello world!\n");
}
```

## 3. Keywords and Identifiers
   - Most of the standard c keywords with some additions.
   - [List of Keywords](../keywords.md)


## 4. Variables and Types
   - Example: Declaring Variables
```
    i32 x = 0;
    utf8 aString = "hello world";
```
   - [Builtin Types](../types.md)

## 5. Basic Operations
   - [List of Operators](../operators.md)

## 6. Control Flow
   - Conditionals: if/else
   - Loops: for, while, do-while

## 7. Functions
   - Example: Defining a Function
```
    def method() void { }
    def add(i32 x, i32 y) i32 result { result = x + y; return; }
```
## 8. Comments
   - Single-line
```
// This is a single line comment
```
   - Multi-line Comments
```
/*
    This is a
    multi line
    comment
*/
```

## 9. Whitespace and Indentation
   - Whitespace doesn't matter.