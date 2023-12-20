#include <vc/basic/report.h>
#include <vc/compiler.h>

#include <iostream>
#include <cassert>

namespace t {
namespace vc {

void name_print(Name* name) {
    if (!name) return;
    u64 count = name->identifiers.count;
    bool colon = false;
    for (u64 i = 0; i < count; i++) {
        if (colon) printf("::");
        printf("%s", name->identifiers.data[i].buffer);
        colon = true;
    }
}
void report_location(FileBuffer* file_buffer, SourceLocation loc) {
    printf("%s:%i:%i error: ",
           file_buffer->name.buffer,
           loc.line,
           loc.column);
}

void report_buffer_line(FileBuffer* file_buffer, SourceLocation loc) {
    i32 line = loc.line - 1;
    if (line < 0) line = 0;

    for (; line < (i32)loc.line; line++) {

        if (line < 0) continue;
        if (line >= file_buffer->line_marks.count) continue;

        FileLineMarker mark = file_buffer->line_marks[line];

        u64 length = mark.length;
        u64 start = mark.offset;

        char* str = new char[length + 1];
        memcpy(str, file_buffer->buffer + start, length);
        str[length] = 0;

        printf("%s\n", str);

        delete [] str;
    }

    for (i32 space = 1; space < (i32)loc.column; space++) printf(" ");
    printf("^\n");
}

void report_error(FileBuffer* fb, SourceLocation loc, const char* format, ...) {
    report_location(fb, loc);

    va_list vl;
    va_start(vl, format);
    vprintf(format, vl);
    va_end(vl);

    report_buffer_line(fb, loc);
}

void report_ice() {
    // TODO: make this more informative lol
    printf("Internal Compiler Error\n");
}

} // namespace vc
} // namespace t
