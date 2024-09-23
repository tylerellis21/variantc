# Enums

Enums define a set of named constants, enhancing code readability and maintainability.

## Syntax

```plaintext
enum <identifier> { <decl-body> }
enum <identifier> : <type> { <decl-body> }
```

## Example

```plaintext
enum Test {
    A,
    B,
    C
}

enum Foo : i32 {
    null = 0,
    one = 1,
    two = two
}
```

## Usage

Access enum values using the scope resolution operator:

```plaintext
Test t = Test::A;

Foo a = Foo::A;
Foo b = Foo::B;

// This is a valid cast, assuming we have the same types.
i32 value = a;

```
