# Tuples and Multi-Return Values

In Variant C, tuples allow you to group multiple values together. This feature is useful for functions that need to return multiple values.

## Tuple Structure

The following is a simple example of a tuple structure:

```plaintext
struct Tuple<T, U> {
    union {
        struct {
            T x;
            U y;
        }
        struct {
            T a;
            U b;
        }
    }
}
```

### Typedef Example

You can create a type alias for a tuple as follows:

```plaintext
typedef [i32, i32] TypedTuple;
```

## Multi-Return Example

Functions can return tuples directly. Here’s an example of a function returning a tuple of two integers:

```plaintext
def multi_return_with_tuple() [i32, i32] {
    i32 x = 0;
    i32 y = 0;
    return (x, y);
}
```

### Note on Casting

In theory, the tuple structure can be cast to the `[i32, i32]` syntax, allowing for flexible use of tuples throughout your code.
