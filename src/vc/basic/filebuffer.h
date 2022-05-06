#ifndef VC_FILE_BUFFER_H_INCLUDE
#define VC_FILE_BUFFER_H_INCLUDE

#include <string>

namespace vc {

struct FileBuffer {
    std::string string;

    bool load(std::string filePath);
};

}

#endif // VC_FILE_BUFFER_H_INCLUDE