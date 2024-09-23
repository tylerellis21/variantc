#ifndef REPORT_H_INCLUDE
#define REPORT_H_INCLUDE

#include <vc/ast/decl.h>
#include <vc/ast/expr.h>
#include <vc/ast/name.h>
#include <vc/ast/stmt.h>
#include <vc/ast/type.h>

#include <vc/basic/file_buffer.h>

#include <stdarg.h>

namespace t {
namespace vc {

void name_print(Name* name);

struct InputFile;

void report_location(FileBuffer* file_buffer, SourceLocation loc);
void report_buffer_line(FileBuffer* file_buffer, SourceLocation loc);

void report_error(FileBuffer* fb, SourceLocation loc, const char* format, ...);

// Internal compiler error
void report_ice();

} // namespace vc
} // namespace t

#endif // REPORT_H_INCLUDE
