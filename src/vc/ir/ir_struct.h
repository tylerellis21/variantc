#ifndef VC_IR_FUNCTION_H_INCLUDE
#define VC_IR_FUNCTION_H_INCLUDE
#include <vector>
#include <vc/ir/ir_opcode.h>
namespace vc {

struct ir_struct {
    std::string name;
    std::vector<ir_ssa_value> basic_fields;
    std::vector<ir_struct> struct_fields;
};

} // namespace vc

#endif // VC_IR_FUNCTION_H_INCLUDE