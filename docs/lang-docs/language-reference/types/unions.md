# Unions

Unions allow different data types to share the same memory space.
This can be useful for memory optimization and type flexibility.

## Example: Template Struct with Union

```plaintext
// Template Struct
struct<T> Vec3 {
    union {
        struct { T x, T y, T z; }
        struct { T t, T u, T v; }
    }
}

// Type Aliases
typedef Vec3<r32> vec3f;
typedef Vec3<r64> vec3d;
typedef Vec3<i32> vec3i;
```

### Usage in Functions

#### Example 1: Initializing a Vec3

```plaintext
def test1() void {
    vec3f test;

    test.x = 0;
    test.y = 0;
    test.z = 0;

    // Note: Initializer lists could cause ambiguity
    test = {1, 2, 3}; // Which version does this use?
}
```

#### Example 2: Size of Union

```plaintext
struct Test2 {
    union {
        i16 x;
        i32 y;
        i64 z;
    }
}

def test2() void {
    i32 size = sizeof(Test2);
    // Expecting size to be 8 bytes.
    assert(size == 8);
}
```

## Syntax

```plaintext
union <identifier> { <decl-body> }
```

### Example

```plaintext
union Foo {
    i32 x, y;
}
```

## Explanation

- **Template Struct**: `Vec3` is a template that can hold three values of type `T`, with two different struct representations.
- **Type Aliases**: `vec3f`, `vec3d`, and `vec3i` are type aliases for different precision vectors.
- **Union Usage**: In `Test2`, the union can hold a single value of either `i16`, `i32`, or `i64`, efficiently sharing memory.
- **Size Assertion**: The size of `Test2` is asserted to be 8 bytes, reflecting the largest member size in the union.
