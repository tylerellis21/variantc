#include <vc/basic/file_buffer.h>
#include <stdio.h>

namespace t {
namespace vc {

bool FileBuffer::read() {

    FILE* fp = fopen((const char*)path.buffer, "rb");

    if (!fp) {
        printf("failed to open file: %s\n", path.buffer);
        return false;
    }

    u64 size = 0;

    fseek(fp, 0, SEEK_END);
    size = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    buffer_size = size;
    buffer = new u8[size];

    fread(buffer, sizeof(char), size, fp);

    fclose(fp);

    u64 offset = 0;

    u64 start = 0;
    u64 length = 0;
    u64 line = 1;

    while (offset < size) {
        char c = buffer[offset++];
        switch (c) {

        // end of a line, mark it
        case '\r': offset++;
        case '\n': {
            FileLineMarker mark;
            mark.length = length;
            mark.line = line;
            mark.offset = start;

            line_marks.push(mark);

            // reset the line
            start = offset;
            length = 0;
            line++;
        } break;

        default: {
            length++;
        } break;

        } // switch (c)

        //printf("%c", c);
    }

    return true;
}

} // namespace vc
} // namespace t
