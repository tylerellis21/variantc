# Plain Old Data Types

## Signed Integers
- `i8`
- `i16`
- `i32`
- `i64`
- `i128`

## Unsigned Integers
- `u8`
- `u16`
- `u32`
- `u64`
- `u128`

## Other Types
- `void`
- `bool`

## Floating Point Types
- `r16`
- `r32`
- `r64`
- `r128`
- `r256`

## Architecture-Sized Types
- `uint`: Architecture-sized unsigned integer (32-bit or 64-bit).
- `int`: Architecture-sized integer (32-bit or 64-bit).
- `uptr`: Architecture-sized pointer.

## [Reference additional types here](../../types.md)

## Variable Declarations

In Variant C, variables are declared similarly to C-like languages. The basic syntax is:

```plaintext
<type> <identifier>;
<type> <identifier> = <expression>;
```

### Examples
```plaintext
i32 x;
i32 x = 10;
```

## Initialization of Objects

Initialization works like in C++, using both stack and heap allocation. Initialization expressions can be named or unnamed.

### Syntax
```plaintext
<type> <identifier> = <initialization expression>;
<type> <identifier> = new { <initialization expression> };
```

### Example
```plaintext
IList<u32> unsignedIntegerList = new IList<u32>();
// The above can be shortened to:
IList<u32> unsignedIntegerList = new();
```

It's preferred to initialize with the first method if the declaration is separate from the initialization, allowing easier type inference. The second method is convenient for inline initialization.

## Struct Example

```plaintext
struct Vector2f { r32 x, y; }
```

### Stack Allocation
```plaintext
def stack() void {
    // Unnamed initialization
    Vector2f a = Vector2f{ 0.f, 0.f };
    Vector2f b = { 0.f, 0.f };
    Vector2f d;
}
```

### Heap Allocation
```plaintext
def heap() void {
    // Unnamed initialization
    Vector2f* a = new Vector2f{ 10.f, 10.f };
    Vector2f* b = new { 10.f, 10.f };
}
```

## Named Initialization
When initializing a type, you can specify the variable names.

### Example
```plaintext
def foo() void {
    // Named initialization
    Vector2f value = { x: 10.f, y: 10.f };
}
```

## Initializer Lists

Initializer lists are a method of constructing structures. Here’s an example:

```plaintext
struct Foo {
    i32 x;
    i32 y;
}

def test1() void {
    Foo bar;

    // Standard initialization
    bar.x = 1;
    bar.y = 1;

    // Using initializer lists
    bar = { 1, 1 };  // Default initialization
    bar = { y: 10, x: 10 };  // Named initializer
}
```

## Summary

Unnamed and named initialization in Variant C mirrors C-like languages, providing flexibility in object construction and variable management.
