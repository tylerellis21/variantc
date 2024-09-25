#ifndef VC_IR_MODULE_H_INCLUDE
#define VC_IR_MODULE_H_INCLUDE

#include <vc/ir/ir_opcode.h>
#include <vc/ir/ir_function.h>

namespace vc {

struct ir_module {
    std::string name;
    std::vector<ir_ssa_value> globals;
    std::vector<ir_function> functions;
    ir_string_table string_table;
};

} // namespace vc

#endif // VC_IR_MODULE_H_INCLUDE