#ifndef VC_IR_FUNCTION_H_INCLUDE
#define VC_IR_FUNCTION_H_INCLUDE
#include <vector>
#include <vc/ir/ir_opcode.h>
namespace vc {

struct ir_function {
    std::string name;
    std::vector<ir_ssa_value> args;
    std::vector<ir_opcode> opcodes;
};

} // namespace vc

#endif // VC_IR_FUNCTION_H_INCLUDE