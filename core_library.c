#include <math.h>
#include "core_library.h"
#include "object.h"
#include "value.h"
#include "vm.h"


//Define the ABS function.
static Value absNative(int argCount, Value *args){
    if (argCount != 1 || !IS_NUMBER(args[0])){
        runtimeError("abs() expects a single number argument");
        return NIL_VAL;
    }

    double value = AS_NUMBER(args[0]);
    return NUMBER_VAL(fabs(value));
}

//Define the SQRT function.
static Value sqrtNative(int argCount, Value *args){
    if (argCount != 1){
        runtimeError("Expected 1 argument but got %d", argCount);
        return NIL_VAL;
    }
    if (!IS_NUMBER(args[0])){
        runtimeError("Expected a number as argument");
        return NIL_VAL;
    }

    return NUMBER_VAL(sqrt(AS_NUMBER(args[0])));
}

//Define the POW function.
static Value powNative(int argCount, Value *args){
    if (argCount != 2){
        runtimeError("Expected 2 arguments but got %d", argCount);
        return NIL_VAL;
    }
    if (!IS_NUMBER(args[0]) || !IS_NUMBER(args[1])){
        runtimeError("Expected a number as argument");
        return NIL_VAL;
    }

    return NUMBER_VAL(pow(AS_NUMBER(args[0]), AS_NUMBER(args[1])));
}

void initCoreLibrary(VM *vvm){
    //Create the abs function.
    defineNative("abs", absNative);
    defineNative("sqrt", sqrtNative);
    defineNative("pow", powNative);
}