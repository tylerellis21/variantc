#ifndef FILE_BUFFER_H_INCLUDE
#define FILE_BUFFER_H_INCLUDE

#include <t/core/string.h>
#include <t/struct/list.h>
#include <t/io/filesystem.h>

namespace t {
namespace vc {

struct FileLineMarker {
    // line number, 1 based
    u64 line;
    // offset zero based
    u64 offset;
    // line length zero based
    u64 length;
};

struct FileBuffer {

    utf8 name;
    utf8 path;

    u8* buffer;
    u64 buffer_size;

    // todo: optimize this perhaps?
    List<FileLineMarker> line_marks;

    inline FileBuffer(const utf8& path) :
        path(path),
        buffer(0),
        buffer_size(0),
        line_marks(List<FileLineMarker>(1000)) {
        name = path::no_ext(path);
    }

    inline void free() {
        name.free();
        path.free();

        delete [] buffer;

        line_marks.free();
    }

    bool read();
};

} // namespace vc
} // namespace t

#endif // FILE_BUFFER_H_INCLUDE
