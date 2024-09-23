# Structs

Structs are user-defined types that allow the grouping of related data together. They are useful for creating complex data types that can encapsulate various attributes.

## Syntax
```
struct <identifier> { <decl-body> }
```

## Example
```
struct Foo { i32 x, i32 y; }
```

### Components
- **identifier**: The name of the struct. It should follow the naming conventions of the language.
- **decl-body**: A comma-separated list of member declarations, which can include various types and their identifiers.

## Member Functions
Structs can also have member functions, which are functions that operate on the data contained within the struct. They can access the struct's members directly.

### Example
```
struct Foo {
    i32 x;
    i32 y;

    def test() {
        return this->x + this->y;
    }
}
```

### Notes on Member Functions
- In member functions, the `this` pointer is available, allowing access to the struct's members.
- This is in contrast to standalone functions, where `this` is not implicitly available.

## Extension Methods
Extension methods allow you to add new methods to existing structs without modifying their original definitions. These methods can access the `this` pointer.

### Syntax
```
def <struct-identifier>::<method-name>() { <method-body> }
```

### Example
```
def Foo::print() {
    printf("Foo: x = %d, y = %d\n", this->x, this->y);
}
```
