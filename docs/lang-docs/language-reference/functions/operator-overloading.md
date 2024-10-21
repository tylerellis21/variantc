# Operator overloading.
Operator overloading is still a WIP.

## Overview

## Syntax

## Examples

### Basic vector struct/class

```
struct v3i {
    r32 x;
    r32 y;
    r32 z;
}

def operator+(v3f* lhs, v3f* rhs) v3f result {
    result.x = lhs.x + rhs.x;
    result.y = lhs.y + rhs.y;
    result.z = lhs.z + rhs.z;
    return result;
}

```