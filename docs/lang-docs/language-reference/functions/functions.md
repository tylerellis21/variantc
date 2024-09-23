# Functions

## Syntax

```plaintext
def <identifier>(<arguments...>) <return type> { <stmt-body> }
def <identifier>(<arguments...>) <return type> <identifier> { <stmt-body> }
```

## Example

Here is a simple function example:

```plaintext
def foo(i32 a, i32 b) i32 { return a + b; }
```

## Extension Methods

Extension methods allow packages to expand upon existing types. For example:

```plaintext
struct Foo {
    i32 x, y;
}

def Foo::sum() i32 {
    return this->x + this->y;
}

def usage() {
    Foo aFoo = { 1, 2 };
    i32 foosum = aFoo.sum();
}

```

## Named Returns

Named returns can be defined as follows:

```plaintext
def foo(i32 a, i32 b) i32 result {
    result = a + b;
    return;
}
```

## Generic Struct Example

Here's an example of a generic struct with an external method declaration:

```plaintext
struct Container<T> {
    T value;
}

def Container<T>::externalMethodDeclaration(i32 a, i32 b) i32 {
    return a + b;
}

def usage() void {
    Container<i32> intContainer = new();
    i32 a = intContainer.externalMethodDeclaration(1, 2);
}
```

## Multiple argument return

You can also define functions with tuple/multiple arguments:

```plaintext
def <identifier>(<arguments...>) [<typed-named-values>] { <body> }

Example:
def test(i32 x, i32 y) [i32 x, i32 y] {
    x = x - 1;
    y = y + 1;
}
```
