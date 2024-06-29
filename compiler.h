#ifndef kat_compiler_h
#define kat_compiler_h

#include "object.h"
#include "vm.h"


ObjFunction* compile(VM* vm, const char* source);
void markCompilerRoots(VM* vm);

#endif