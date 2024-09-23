# Arrays in Variant C

Arrays in Variant C are declared similarly to C-like languages, with one key difference: the array modifier binds to the type itself.

## Syntax

```plaintext
<type> [ <array-length> ] <identifier>;
<type> [ <array-length> ] <identifier> = <expression>;
```

## Examples

```plaintext
i32[10] values;
i32[10] values = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
```

### Key Point

The array modifier binds to the type itself, meaning the following declarations create variables of the same type:

```plaintext
i32[16] x, y;
r32[16] matrix_x, matrix_y;
```

In this case, `x` and `y` are both arrays of `i32`, while `matrix_x` and `matrix_y` are arrays of `r32`.

Another key point is that unlike c, arrays that are typed with a length don't collaps to a raw pointer.
