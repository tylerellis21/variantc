# Primitive Types

This document outlines the core primitive types supported by the language. These types are essential building blocks for variable declarations, memory manipulation, and basic arithmetic.

---

## 1. General Types
These types form the foundation of the type system.

- **void**
  Represents the absence of a type or return value. Used in functions that do not return a value.

- **bool**
  Boolean type used for true/false values. Only two possible values: `true` or `false`.

---

## 2. Unsigned Integer Types
These types are used for non-negative integer values. They do not support negative numbers.

| Type | Bit Width | Range                        |
|------|-----------|------------------------------|
| u8   | 8 bits    | 0 to 255                     |
| u16  | 16 bits   | 0 to 65,535                  |
| u32  | 32 bits   | 0 to 4,294,967,295           |
| u64  | 64 bits   | 0 to 18,446,744,073,709,551,615 |
| u128 | 128 bits  | 0 to (2^128 - 1)             |
| u256 | 256 bits  | 0 to (2^256 - 1)             |
| u512 | 512 bits  | 0 to (2^512 - 1)             |
| u1024| 1024 bits | 0 to (2^1024 - 1)            |

---

## 3. Signed Integer Types
Signed integers support both negative and positive values.

| Type | Bit Width | Range                           |
|------|-----------|---------------------------------|
| i8   | 8 bits    | -128 to 127                     |
| i16  | 16 bits   | -32,768 to 32,767               |
| i32  | 32 bits   | -2,147,483,648 to 2,147,483,647 |
| i64  | 64 bits   | -9,223,372,036,854,775,808 to 9,223,372,036,854,775,807 |
| i128 | 128 bits  | -2^127 to (2^127 - 1)           |
| i256 | 256 bits  | -2^255 to (2^255 - 1)           |
| i512 | 512 bits  | -2^511 to (2^511 - 1)           |
| i1024| 1024 bits | -2^1023 to (2^1023 - 1)         |

---

## 4. Floating Point Types
Floating-point numbers are used to represent real numbers, supporting decimal points.

| Type | Bit Width | Precision (approx)  |
|------|-----------|---------------------|
| r8   | 8 bits    | Very limited        |
| r16  | 16 bits   | Half precision      |
| r32  | 32 bits   | Single precision (7-8 decimal digits) |
| r64  | 64 bits   | Double precision (15-16 decimal digits)|
| r128 | 128 bits  | Quadruple precision (34-36 decimal digits) |
| r256 | 256 bits  | Extended precision  |
| r512 | 512 bits  | Extended precision  |
| r1024| 1024 bits | Extended precision  |

---

## 5. Platform Types
These types are dependent on the architecture of the system.

- **uint**
  Architecture-sized unsigned integer. It represents the native word size of the platform (32-bit or 64-bit).

- **int**
  Architecture-sized signed integer. Similar to `uint` but allows negative values.

---

## 6. Fixed Point Types
Fixed-point types are used for decimal numbers where a fixed number of digits follow the decimal point.

- **decimal**
  Fixed-point type with a high precision for decimal values, typically used in financial calculations.

---

## 7. String & Character Types
Types designed to handle textual data.

- **char**
  Represents a single character. Typically 1 byte (8 bits), depending on the encoding.

- **rune**
  Represents a Unicode code point. Useful for representing complex characters in multi-byte encodings.

- **cstr**
  C-style string, a null-terminated sequence of `char` types.

- **utf8**
  UTF-8 encoded string, supporting multi-byte characters.

- **utf16**
  UTF-16 encoded string, often used for handling multi-language texts.

- **utf32**
  UTF-32 encoded string, where each character is represented by a 32-bit integer.

---

## 8. Notes on Usage
- **Integer Types**: Use unsigned integers (`u8`, `u16`, etc.) when working with non-negative values like array indices or sizes. Use signed integers (`i8`, `i16`, etc.) when you expect both positive and negative values.
- **Floating Point**: Floating-point precision should be chosen carefully based on the application's requirements, as higher precision types (like `r128` or `r256`) can be significantly more costly in terms of performance.
- **String Types**: For textual data, choose `utf8` unless there's a need for higher memory or performance constraints, in which case `utf16` or `utf32` might be better suited.
