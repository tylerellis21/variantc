# Types
* Types which are greater than i64/u64 or r512 are implemented in software, depending on hardware availability.

## General Types
- `void`
- `bool`

---

## Unsigned Integer Types
- `u8`
- `u16`
- `u32`
- `u64`
- `u128`
- `u256`
- `u512`
- `u1024`

---

## Signed Integer Types
- `i8`
- `i16`
- `i32`
- `i64`
- `i128`
- `i256`
- `i512`
- `i1024`

---

## Floating Point Types
- `r8`
- `r16`
- `r32`
- `r64`
- `r128`
- `r256`
- `r512`
- `r1024`

---

## Platform-Dependent Types
- `uint` (Unsigned Integer, size depends on platform)
- `int` (Signed Integer, size depends on platform)

---

## Fixed Point Types
- `decimal`

---

## String Types
- `char` (Single character, often platform-specific encoding)
- `rune` (Unicode code point)
- `cstr` (C-style null-terminated string)
- `utf8` (UTF-8 encoded string)
- `utf16` (UTF-16 encoded string)
- `utf32` (UTF-32 encoded string)

# More information
  * [Primitive Types](./language-reference/types/primitive-types.md)
  * [Arrays](./language-reference/types/arrays.md)
  * [Bit Fields](./language-reference/types/bit-fields.md)
  * [Enums](./language-reference/types/enums.md)
  * [Tuples](./language-reference/types/tuples.md)
  * [Structs](./language-reference/types/structs.md)
  * [Unions](./language-reference/types/unions.md)
