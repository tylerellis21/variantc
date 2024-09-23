# Lambda Functions

## Syntax

Lambda functions allow for concise function definitions. The basic syntax is as follows:

```plaintext
def <identifier>(<arguments...>) => { <stmt-body> }
```

## Examples

### Basic Lambda Definition

Here is a simple example of a lambda function:

```plaintext
def lambda_test() void {
    def add(i32 x, i32 y) => x + y;

    i32 result = add(1, 2);
}
```

### Anonymous Lambda/Auto-typed Lambda

For auto-typed lambdas, the syntax is:

```plaintext
auto lambda (i32 x, i32 y) => {
    return x + y;
}
```

### Lambda Wrapper Example

You can also wrap lambdas in other functions:

```plaintext
def lambda_wrapper(i32 x, i32 y) => lambda(10, 10);
```

### Using Auto Lambda

An example of an auto lambda:

```plaintext
def auto_lambda => (i32 a, i32 b) {
    return a + b;
}

def usage() void {
    auto a = lambda();
    auto b = auto_lambda(10, 20);
}
```
