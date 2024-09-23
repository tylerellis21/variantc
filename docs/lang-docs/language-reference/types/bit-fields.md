# Bit fields

Bitfields allows you to specified the number of bits a specified field takes up.

## Example: Struct with Union

```plaintext
struct Test {
    u64 number;
    union {
        bool firstFlag : 1;
        bool secondFlag : 1;
        u8 b : 2;
        u8 c : 2;
        u8 d : 2;
        u8[4] remBytes;
    } named_union;
}
```

### Usage of Union in a Function

Here's how to use the `named_union` within a function:

```plaintext
def using_union_example() void {
    Test a;

    a.named_union.firstFlag = true;
    a.named_union.secondFlag = true;

    a.named_union.b = 0;
    a.named_union.c = 0;
    a.named_union.d = 0;

    a.named_union.remBytes = {10, 20, 30, 40};
}
```

## Explanation

- **Struct**: The `Test` struct contains a `u64` number and a union.
- **Union**: The `named_union` can hold multiple flags and a byte array. Only one of these can be active at a time, making it memory efficient.
- **Bit Fields**: Flags `firstFlag`, `secondFlag`, `b`, `c`, and `d` are defined with specific bit widths, allowing fine-grained control over memory usage.
