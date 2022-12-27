#ifndef VC_MACROS_H_INCLUDE
#define VC_MACROS_H_INCLUDE

#define STRINGIFY(x) #x
#define TOSTRING(x) STRINGIFY(x)
#define AT __FILE__ ":" TOSTRING(__LINE__)

#endif // VC_MACROS_H_INCLUDE