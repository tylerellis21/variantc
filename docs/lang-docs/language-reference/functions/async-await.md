# Asynchronous Functions

## Overview

Asynchronous functions in Variant C allow non-blocking operations, enabling efficient execution of tasks that may take time to complete, such as file I/O or network requests.

## Syntax

The basic syntax for defining an asynchronous function is:

```plaintext
async def <identifier>() <return type> { <stmt-body> }
```

## Examples

### Simple Asynchronous Function

Here’s a basic example of an asynchronous function:

```plaintext
async def test() void {
    // Asynchronous code can be added here
}
```

### Asynchronous Function with Return Value

An asynchronous function can return a value wrapped in a task, as shown below:

```plaintext
async def asyncIncrement(i32 value) Task<i32> {
    return i += value;
}
```

### File I/O Example

An asynchronous function for file operations could look like this:

```plaintext
def async fileOpenAsync() Task<i32> {
    // Insert asynchronous file I/O code here
    return 0;
}
```

### Awaiting a Task in Asynchronous Function

You can await a task in an asynchronous function. Here’s an example that attempts to open a file asynchronously:

```plaintext
async def asyncFileOpen(utf8 filePath) Task<[bool, File*]> {
    File* file = await file::openAsync(filePath);
    if (file == 0) {
        return [false, 0]; // File not found
    }
    return [true, file]; // Return the opened file
}
```
