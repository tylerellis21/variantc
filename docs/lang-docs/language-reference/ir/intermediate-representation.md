# Intermediate Representation

The intermediate representation used in the variantc compiler is very similar to the IR used in clang.

It uses a ssa format and we will eventually have a way to output and input said IR format as needed.

# Example
```vc
struct v2i {
    i32 x;
    i32 y;
}

def test(v2i lhs, v2i rhs) v2i result {
    result.x = lhs.x + rhs.x;
    result.y = lhs.y + rhs.y;
    return;
}
```

```vcir
struct v2i {
    $0 i32;
    $1 i32;
}

// result is implicitly allocated by the caller?
def test($0 i32, $1 i32) $3 i32 {
    // test
    $4 = add i32 $0, $1
    $5 = store i32 $4, $3
    ret
}

$0 = alloc i32
$1 = store_const i32 $0, 20
$2 = add i32 $0, $1
```