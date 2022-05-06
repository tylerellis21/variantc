#include <vc/basic/filebuffer.h>
#include <iostream>
#include <fstream>

namespace vc {

bool FileBuffer::load(std::string filePath) {
    std::ifstream input(filePath, std::ios::binary);
    if (input.is_open() == false) {
        std::cout << "failed to open file: " << filePath << std::endl;
        return false;
    }
    // seek to end, to get the length
    input.seekg(0, std::ios::end);

    std::streampos fsize = input.tellg() - fsize;

    // reset so we can read from the start of the file.
    input.seekg(0, std::ios::beg);

    std::string buffer;
    // allocate space for the entire file.
    buffer.resize((size_t)fsize);
    
    input.read(&buffer[0], (std::streamsize)fsize);
    input.close();

    this->string = buffer;

    return true;
}

}