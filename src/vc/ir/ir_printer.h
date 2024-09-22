#ifndef VC_IR_PRINTER_H_INCLUDE
#define VC_IR_PRINTER_H_INCLUDE

#include <vc/ir/ir_module.h>

namespace vc {

class IRPrinter {
public:
    void print(const ir_module& module);
    void print(const ir_function& function);
    void print(const ir_opcode& opcode);
private:
    void indent(int i);
};

} // namespace vc

#endif // VC_IR_PRINTER_H_INCLUDE