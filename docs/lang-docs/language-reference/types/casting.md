# Type Conversion

Type conversion allows you to convert one type to another in Variant C.
This is useful for working with inheritance and polymorphism.

## Syntax

The syntax for converting a type is as follows:

```plaintext
as<Type>(value)
```

## Example Structures

Consider the following example with two structures, `Foo` and `Bar`, where `Bar` inherits from `Foo`:

```plaintext
struct Foo {
    // Members of Foo
}

struct Bar : Foo {
    // Members of Bar
}
```

## Type Conversion Example

```plaintext
def main() void {
    // Create a new instance of Bar
    Bar* bar = new Bar;

    // Convert Bar pointer to Foo pointer using 'as<Type>'
    Foo* foo = as<Foo*>(bar);
}
```

### Key Points
- Use `as<Type>(value)` for explicit type conversion.
- Ensure that the conversion is valid, especially when dealing with inheritance.

