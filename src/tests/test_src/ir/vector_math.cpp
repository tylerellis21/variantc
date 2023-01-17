struct v2i {
    int x;
    int y;
};

v2i add(v2i lhs, v2i rhs) {
    return v2i {
        lhs.x + rhs.x,
        lhs.y + rhs.y
    };
}

v2i sub(v2i lhs, v2i rhs) {
    return v2i {
        lhs.x - rhs.x,
        lhs.y - rhs.y
    };
}

v2i mul(v2i lhs, v2i rhs) {
    return v2i {
        lhs.x * rhs.x,
        lhs.y * rhs.y
    };
}

v2i div(v2i lhs, v2i rhs) {
    return v2i {
        lhs.x / rhs.x,
        lhs.y / rhs.y
    };
}

v2i mod(v2i lhs, v2i rhs) {
    return v2i {
        lhs.x % rhs.x,
        lhs.y % rhs.y
    };
}
v2i bsl(v2i lhs, v2i rhs) {
    return v2i {
        lhs.x << rhs.x,
        lhs.y << rhs.y
    };
}

v2i bsr(v2i lhs, v2i rhs) {
    return v2i {
        lhs.x >> rhs.x,
        lhs.y >> rhs.y
    };
}

int main() {
    v2i a = v2i {1, 2};
    v2i b = v2i {3, 4};
    v2i c = add(a, b);
    v2i d = sub(a, b);
    v2i e = mul(a, b);
    v2i f = div(a, b);
    v2i g = mod(a, b);
    v2i h = bsr(a, b);
    v2i i = bsl(a, b);
    return 0;
}