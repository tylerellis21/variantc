# Delegates and Function Pointers

## Overview

Delegates in Variant C provide a way to encapsulate method references, allowing for flexible callback mechanisms and event handling. They are similar to C# delegates, enabling a method to be assigned and invoked later.

## Delegate Syntax

### Defining a Delegate

To define a delegate, use the following syntax:

```plaintext
delegate <return type> <identifier>(<parameter types...>);
```

### Example

Here’s an example of a simple delegate that takes a string message as a parameter:

```plaintext
delegate void MessageDelegate(string message);
```

## Function Pointer Syntax

Function pointers allow you to reference and call functions dynamically.

### Defining a Function Pointer

The syntax for defining a function pointer is as follows:

```plaintext
delegate*<return type, <parameter types...>>;
```

### Example

Here’s how you can declare a function pointer for a function that takes three integer parameters:

```plaintext
delegate*<int, int, int> function_ptr_with_3_args;
```

## Example Functions

Below are some simple mathematical operations defined as functions:

```plaintext
def test() void {
    // A simple test function
}

def add(i32 x, i32 y) i32 {
    return x + y;
}

def sub(i32 x, i32 y) i32 {
    return x - y;
}

def mul(i32 x, i32 y) i32 {
    return x * y;
}

def div(i32 x, i32 y) i32 {
    return x / y;
}
```

## Using Function Pointers

Function pointers can be invoked like regular functions. Here’s an example of how to use them:

```plaintext
def main(int argc, char** args) i32 {
    // Define function pointers for each operation
    MessageDelegate messageDelegate = test;

    // Invoke the test function
    messageDelegate();

    delegate*<i32, i32, i32> addMethod = add;
    delegate*<i32, i32, i32> subMethod = sub;
    delegate*<i32, i32, i32> mulMethod = mul;
    delegate*<i32, i32, i32> divMethod = div;

    delegate*<i32, i32, i32>* functionList = malloc(sizeof(addMethod) * 4);
    functionList[0] = addMethod;
    functionList[1] = subMethod;
    functionList[2] = mulMethod;
    functionList[3] = divMethod;

    i32 x = 100;
    i32 y = 25;

    for (i32 i = 0; i < 4; i++) {
        delegate*<i32, i32, i32> method = functionList[i];

        i32 result = method(x, y);

        printf("Result: %i\n", result);
    }

    return 0;
}
```

## Conclusion

Delegates and function pointers in Variant C enhance flexibility in your code by allowing methods to be passed as parameters and invoked dynamically.
