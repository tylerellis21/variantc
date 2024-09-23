# Memory Alignment

Memory alignment is critical for optimizing performance and ensuring correct behavior in low-level operations. It is essential for the language to support alignment specifications when allocating memory.

## Structure Alignment

Structures can be defined with specific alignment requirements. For example, the following structure is aligned to 32 bits:

```plaintext
struct foo align(32) {
    // Structure members go here
}
```

### Packed Structure

You can also create packed structures with a specific alignment, as shown below:

```plaintext
struct packed_foo pack align(64) {
    i32 x;
    i32 y;
}
```

## Example Function

Here’s an example demonstrating how alignment works in practice:

```plaintext
def example_function() void {
    // Allocate 'foo' on the stack, aligned to 32 bits
    foo a;

    // Allocate 'foo' on the heap with specific alignment
    // The allocation function must be informed of the desired alignment
    foo* b = alloc<foo align(28)>();
}
```

### Key Points
- Structures can be defined with specific alignment requirements using the `align()` keyword.
- When allocating memory, you can specify the alignment to ensure proper memory alignment for performance optimization.
- It’s crucial to keep alignment in mind when designing data structures, especially in performance-critical applications.

