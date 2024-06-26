#include <math.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "core_library.h"
#include "object.h"
#include "memory.h"
#include "value.h"
#include "vm.h"

//<<<<<<<<<<<<<<<<<<<<<MATHEMATICAL FUNCTIONS>>>>>>>>>>>>>>>>>>>>>>>>>>>>>


//Define the ABS function. Returns the absolut value of a number.
static Value absNative(int argCount, Value *args){
    if (argCount != 1 || !IS_NUMBER(args[0])){
        runtimeError("abs() expects a single number argument");
        return NIL_VAL;
    }

    double value = AS_NUMBER(args[0]);
    return NUMBER_VAL(fabs(value));
}

//Define the SQRT function. Returns the square root of a number.
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

//Define the POW function. Returns the first number raised to the power of the second number.
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

//Define the MAX function. Returns the maximum of two numbers.
static Value maxNative(int argCount, Value *args){
    if (argCount != 2){
        runtimeError("Expected 2 arguments but got %d", argCount);
        return NIL_VAL;
    }

    if (!IS_NUMBER(args[0]) || !IS_NUMBER(args[1])){
        runtimeError("Expected a number as argument");
        return NIL_VAL;
    }

    return NUMBER_VAL(fmax(AS_NUMBER(args[0]), AS_NUMBER(args[1])));
}

//Define the MIN function. Returns the minimum of two numbers.
static Value minNative(int argCount, Value *args) {
    if (argCount != 2) {
        runtimeError("Expected 2 arguments but got %d", argCount);
        return NIL_VAL;
    }

    if (!IS_NUMBER(args[0]) || !IS_NUMBER(args[1])) {
        runtimeError("Expected a number as argument");
        return NIL_VAL;
    }

    return NUMBER_VAL(fmin(AS_NUMBER(args[0]), AS_NUMBER(args[1])));
}

//Define the FLOOR function. Returns the largest integer less than or equal to a number. 2.3 -> 2
static Value floorNative(int argCount, Value *args){
    if (argCount != 1){
        runtimeError("Expected 1 argument but got %d", argCount);
        return NIL_VAL;
    }
    if (!IS_NUMBER(args[0])){
        runtimeError("Expected a number as argument");
        return NIL_VAL;
    }

    return NUMBER_VAL(floor(AS_NUMBER(args[0])));
}

//Define the CEIL function. Returns the smallest integer greater than or equal to a number. 2.3 -> 3
static Value ceilNative(int argCount, Value *args){
    if (argCount != 1){
        runtimeError("Expected 1 argument but got %d", argCount);
        return NIL_VAL;
    }
    if (!IS_NUMBER(args[0])){
        runtimeError("Expected a number as argument");
        return NIL_VAL;
    }

    return NUMBER_VAL(ceil(AS_NUMBER(args[0])));
}

//Define the ROUND function. Returns the nearest integer to a number. 2.3 -> 2, 2.7 -> 3
static Value roundNative(int argCount, Value *args){
    if (argCount != 1){
        runtimeError("Expected 1 argument but got %d", argCount);
        return NIL_VAL;
    }
    if (!IS_NUMBER(args[0])){
        runtimeError("Expected a number as argument");
        return NIL_VAL;
    }

    return NUMBER_VAL(round(AS_NUMBER(args[0])));
}

//Define the LOG function. Returns the natural logarithm of a number.
static Value logNative(int argCount, Value *args){
    if (argCount != 1){
        runtimeError("Expected 1 argument but got %d", argCount);
        return NIL_VAL;
    }
    if (!IS_NUMBER(args[0])){
        runtimeError("Expected a number as argument");
        return NIL_VAL;
    }

    return NUMBER_VAL(log(AS_NUMBER(args[0])));
}

//Define the EXP function. Returns the exponential of a number. e^x.
static Value expNative(int argCount, Value *args){
    if (argCount != 1){
        runtimeError("Expected 1 argument but got %d", argCount);
        return NIL_VAL;
    }
    if (!IS_NUMBER(args[0])){
        runtimeError("Expected a number as argument");
        return NIL_VAL;
    }

    return NUMBER_VAL(exp(AS_NUMBER(args[0])));
}

//Define the SIN function. Returns the sine of a number.
static Value sinNative(int argCount, Value *args){
    if (argCount != 1){
        runtimeError("Expected 1 argument but got %d", argCount);
        return NIL_VAL;
    }
    if (!IS_NUMBER(args[0])){
        runtimeError("Expected a number as argument");
        return NIL_VAL;
    }

    return NUMBER_VAL(sin(AS_NUMBER(args[0])));
}

//Define the COS function. Returns the cosine of a number.
static Value cosNative(int argCount, Value *args){
    if (argCount != 1){
        runtimeError("Expected 1 argument but got %d", argCount);
        return NIL_VAL;
    }
    if (!IS_NUMBER(args[0])){
        runtimeError("Expected a number as argument");
        return NIL_VAL;
    }

    return NUMBER_VAL(cos(AS_NUMBER(args[0])));
}

//Define the TAN function. Returns the tangent of a number.
static Value tanNative(int argCount, Value *args){
    if (argCount != 1){
        runtimeError("Expected 1 argument but got %d", argCount);
        return NIL_VAL;
    }
    if (!IS_NUMBER(args[0])){
        runtimeError("Expected a number as argument");
        return NIL_VAL;
    }

    return NUMBER_VAL(tan(AS_NUMBER(args[0])));
}

//Define the ASIN function. Returns the arcsine of a number.
static Value asinNative(int argCount, Value *args){
    if (argCount != 1) {
        runtimeError("Expected 1 argument but got %d", argCount);
        return NIL_VAL;
    }
    if (!IS_NUMBER(args[0])) {
        runtimeError("Expected a number as argument");
        return NIL_VAL;
    }

    return NUMBER_VAL(asin(AS_NUMBER(args[0])));
}

//Define the ACOS function. Returns the arccosine of a number.
static Value acosNative(int argCount, Value *args){
    if (argCount != 1) {
        runtimeError("Expected 1 argument but got %d", argCount);
        return NIL_VAL;
    }
    if (!IS_NUMBER(args[0])) {
        runtimeError("Expected a number as argument");
        return NIL_VAL;
    }

    return NUMBER_VAL(acos(AS_NUMBER(args[0])));
}

//Define the ATAN function. Returns the arctangent of a number.
static Value atanNative(int argCount, Value *args){
    if (argCount != 1) {
        runtimeError("Expected 1 argument but got %d", argCount);
        return NIL_VAL;
    }
    if (!IS_NUMBER(args[0])) {
        runtimeError("Expected a number as argument");
        return NIL_VAL;
    }

    return NUMBER_VAL(atan(AS_NUMBER(args[0])));
}

//Define the SINH function. Returns the hyperbolic sine of a number.
static Value sinhNative(int argCount, Value *args){
    if (argCount != 1) {
        runtimeError("Expected 1 argument but got %d", argCount);
        return NIL_VAL;
    }
    if (!IS_NUMBER(args[0])) {
        runtimeError("Expected a number as argument");
        return NIL_VAL;
    }

    return NUMBER_VAL(sinh(AS_NUMBER(args[0])));
}

//Define the COSH function. Returns the hyperbolic cosine of a number.
static Value coshNative(int argCount, Value *args){
    if (argCount != 1) {
        runtimeError("Expected 1 argument but got %d", argCount);
        return NIL_VAL;
    }
    if (!IS_NUMBER(args[0])) {
        runtimeError("Expected a number as argument");
        return NIL_VAL;
    }

    return NUMBER_VAL(cosh(AS_NUMBER(args[0])));
}

//Define the TANH function. Returns the hyperbolic tangent of a number.
static Value tanhNative(int argCount, Value *args){
    if (argCount != 1) {
        runtimeError("Expected 1 argument but got %d", argCount);
        return NIL_VAL;
    }
    if (!IS_NUMBER(args[0])) {
        runtimeError("Expected a number as argument");
        return NIL_VAL;
    }

    return NUMBER_VAL(tanh(AS_NUMBER(args[0])));
}

//Define the LOG10 function. Returns the base 10 logarithm of a number.
static Value log10Native(int argCount, Value *args){
    if (argCount != 1) {
        runtimeError("Expected 1 argument but got %d", argCount);
        return NIL_VAL;
    }
    if (!IS_NUMBER(args[0])) {
        runtimeError("Expected a number as argument");
        return NIL_VAL;
    }

    return NUMBER_VAL(log10(AS_NUMBER(args[0])));
}

//Define the FABS function. Returns the absolute value of a float number.
static Value fabsNative(int argCount, Value *args){
    if (argCount != 1) {
        runtimeError("Expected 1 argument but got %d", argCount);
        return NIL_VAL;
    }
    if (!IS_NUMBER(args[0])) {
        runtimeError("Expected a number as argument");
        return NIL_VAL;
    }

    return NUMBER_VAL(fabs(AS_NUMBER(args[0])));
}


//<<<<<<<<<<<<<<<<<<<<<STRING MANIPULATION>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

//Define the STRLEN function. Returns the length of a string.
static Value strlenNative(int argCount, Value *args){
    if (argCount != 1){
        runtimeError("Expected 1 argument but got %d", argCount);
        return NIL_VAL;
    }
    if (!IS_STRING(args[0])){
        runtimeError("Expected a string as argument");
        return NIL_VAL;
    }

    ObjString* string = AS_STRING(args[0]);
    return NUMBER_VAL((double)string->length);
}

//Define the STRCMP function. Compares two string and returns 0 if they are equal or a non-zero value if they are different.
static Value strcmpNative(int argCount, Value *args){
    if (argCount != 2){
        runtimeError("Expected 2 arguments but got %d", argCount);
        return NIL_VAL;
    }

    ObjString* string1 = AS_STRING(args[0]);
    ObjString* string2 = AS_STRING(args[1]);

    int result = strcmp(string1->chars, string2->chars);
    return NUMBER_VAL((double)result);
}

//Define the STRCAT function. Concatenates two strings.
static Value strcatNative(int argCount, Value *args){
    if (argCount != 2){
        runtimeError("Expected 2 arguments but got %d", argCount);
        return NIL_VAL;
    }

    ObjString* string1 = AS_STRING(args[0]);
    ObjString* string2 = AS_STRING(args[1]);

    int length = string1->length + string2->length;
    char* chars = ALLOCATE(char, length + 1);
    memcpy(chars, string1->chars, string1->length);
    memcpy(chars + string1->length, string2->chars, string2->length);
    chars[length] = '\0';

    ObjString* result = takeString(chars, length);
    return OBJ_VAL(result);
}

//Define the TOUPPER function. Converts a string to uppercase.
static Value toupperNative(int argCount, Value *args){
    if (argCount != 1){
        runtimeError("Expected 1 argument but got %d", argCount);
        return NIL_VAL;
    }

    ObjString* str = AS_STRING(args[0]);
    int length = str->length;
    char* chars = ALLOCATE(char, length + 1);

    for (int i = 0; i < length; i++){
        chars[i] = (char)toupper((unsigned char) str->chars[i]);
    }
    chars[length] = '\0';

    ObjString* result = takeString(chars, length);
    return OBJ_VAL(result);
}

//Define the STRCHR function. Returns the first occurrence of a character in a string.
static Value strchrNative(int argCount, Value *args){
    if (argCount != 2 || !IS_STRING((args[0])) || !IS_STRING(args[1]) || AS_STRING(args[1])->length != 1){
        runtimeError("Expected a string and a character as arguments");
        return NIL_VAL;
    }

    ObjString* str = AS_STRING(args[0]);
    char chr = AS_STRING(args[1])->chars[0];

    char* found = strchr(str->chars, chr);
    if (found == NULL){
        return NIL_VAL;
    }

    int index = (int)(found - str->chars);
    return NUMBER_VAL(index);
}

//Define the STRSTR function. Returns the first occurrence of a substring in a string.
static Value strstrNative(int argCount, Value *args){
    if (argCount != 2 || !IS_STRING((args[0])) || !IS_STRING(args[1])){
        runtimeError("Expected a string and a substring as arguments");
        return NIL_VAL;
    }

    ObjString* haystack = AS_STRING(args[0]);
    ObjString* needle = AS_STRING(args[1]);

    char* found = strstr(haystack->chars, needle->chars);
    if (found == NULL){
        return NIL_VAL;
    }

    int index = (int)(found - haystack->chars);
    return NUMBER_VAL(index);
}

//Define STRCPY function. Copies a string.
static Value strcpyNative(int argCount, Value *args){
    if (argCount != 1 || !IS_STRING(args[0])){
        runtimeError("Expected a string as argument");
        return NIL_VAL;
    }

    ObjString* source = AS_STRING(args[0]);
    ObjString* copy = copyString(source->chars, source->length);

    return OBJ_VAL(copy);
}

//Define the STRDUP function. Duplicates a string.
static Value strdupNative(int argCount, Value* args) {
    if (argCount != 1 || !IS_STRING(args[0])) {
        runtimeError("strdup() expects a single string argument.");
        return NIL_VAL;
    }

    ObjString* source = AS_STRING(args[0]);
    ObjString* duplicate = copyString(source->chars, source->length);

    return OBJ_VAL(duplicate);
}

//Define the STRTOK function. Tokenizes a string. strtok("Hello,world") -> "Hello", if called again with empty it returns the next one: strtok("", ",") -> "world"
static Value strtokNative(int argCount, Value* args) {
    if (argCount != 2 || !IS_STRING(args[0]) || !IS_STRING(args[1])) {
        runtimeError("strtok() expects two string arguments.");
        return NIL_VAL;
    }

    static char* lastToken = NULL;
    const char* str = AS_CSTRING(args[0]);
    const char* delimiters = AS_CSTRING(args[1]);

    char* token = strtok(str[0] != '\0' ? (char*)str : NULL, delimiters);
    if (token == NULL) {
        return NIL_VAL;
    }

    lastToken = token;
    return OBJ_VAL(copyString(token, strlen(token)));
}

//Define the SPRINTF function. Formats a string.
static Value sprintfNative(int argCount, Value* args) {
    if (argCount < 1 || !IS_STRING(args[0])) {
        runtimeError("sprintf() expects at least one string argument.");
        return NIL_VAL;
    }

    const char* format = AS_CSTRING(args[0]);
    char buffer[1024]; // Adjust buffer size as needed
    int index = 1;

    char* out = buffer;
    const char* fmt = format;

    while (*fmt) {
        if (*fmt == '%' && *(fmt + 1) != '%') {
            fmt++;
            if (index >= argCount) {
                runtimeError("sprintf() format specifiers exceed provided arguments.");
                return NIL_VAL;
            }
            switch (*fmt) {
                case 'd': {
                    if (!IS_NUMBER(args[index])) {
                        runtimeError("sprintf() expects a number for %%d.");
                        return NIL_VAL;
                    }
                    int num = (int)AS_NUMBER(args[index]);
                    out += sprintf(out, "%d", num);
                    index++;
                    break;
                }
                case 'f': {
                    if (!IS_NUMBER(args[index])) {
                        runtimeError("sprintf() expects a number for %%f.");
                        return NIL_VAL;
                    }
                    double num = AS_NUMBER(args[index]);
                    out += sprintf(out, "%f", num);
                    index++;
                    break;
                }
                case 's': {
                    if (!IS_STRING(args[index])) {
                        runtimeError("sprintf() expects a string for %%s.");
                        return NIL_VAL;
                    }
                    const char* str = AS_CSTRING(args[index]);
                    out += sprintf(out, "%s", str);
                    index++;
                    break;
                }
                default:
                    runtimeError("Unsupported format specifier in sprintf().");
                    return NIL_VAL;
            }
        } else {
            *out++ = *fmt;
        }
        fmt++;
    }
    *out = '\0';

    return OBJ_VAL(copyString(buffer, (int)strlen(buffer)));
}

//<<<<<<<<<<<<<<<<<<<<<TIME FUNCTIONS>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

//Define the TIME function. Returns the current time in seconds.
static Value timeNative(int argCount, Value *args){
    return NUMBER_VAL((double)time(NULL));
}

//Define the STRFTIME function. Formats a time value.
static Value strftimeNative(int argCount, Value* args) {
    if (argCount != 1 || !IS_STRING(args[0])) {
        runtimeError("Expects one string argument.");
        return NIL_VAL;
    }

    const char* format = AS_CSTRING(args[0]);
    char buffer[1024];
    time_t rawTime = time(NULL);
    struct tm* timeInfo = localtime(&rawTime);

    size_t length = strftime(buffer, sizeof(buffer), format, timeInfo);
    if (length == 0) {
        return NIL_VAL;
    }

    return OBJ_VAL(copyString(buffer, (int)length));
}

//<<<<<<<<<<<<<<<<<<<<<MISC>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

//Define the RAND function. Returns a random number between 0 and 1.
static Value randNative(int argCount, Value *args){
    return NUMBER_VAL(rand());
}

//Define the SRAND function. Seeds the random number generator.
static Value srandNative(int argCount, Value* args) {
    if (argCount != 1 || !IS_NUMBER(args[0])) {
        runtimeError("srand() expects one number argument.");
        return NIL_VAL;
    }
    srand((unsigned int)AS_NUMBER(args[0]));
    return NIL_VAL;
}

//Define the ASSERT function. Asserts a condition.
static Value assertNative(int argCount, Value* args) {
    if (argCount != 1 || !IS_BOOL(args[0])) {
        runtimeError("assert() expects one boolean argument.");
        return NIL_VAL;
    }
    if (!AS_BOOL(args[0])) {
        runtimeError("Assertion failed.");
    }
    return NIL_VAL;
}


void initCoreLibrary(VM *vvm){
    //Mathematical functions
    defineNative("abs", absNative);
    defineNative("sqrt", sqrtNative);
    defineNative("pow", powNative);
    defineNative("max", maxNative);
    defineNative("min", minNative);
    defineNative("floor", floorNative);
    defineNative("ceil", ceilNative);
    defineNative("round", roundNative);
    defineNative("log", logNative);
    defineNative("exp", expNative);
    defineNative("sin", sinNative);
    defineNative("cos", cosNative);
    defineNative("tan", tanNative);
    defineNative("asin", asinNative);
    defineNative("acos", acosNative);
    defineNative("atan", atanNative);
    defineNative("sinh", sinhNative);
    defineNative("cosh", coshNative);
    defineNative("tanh", tanhNative);
    defineNative("log10", log10Native);
    defineNative("fabs", fabsNative);

    //String manipulation
    defineNative("strlen", strlenNative);
    defineNative("strcmp", strcmpNative);
    defineNative("strcat", strcatNative);
    defineNative("toupper", toupperNative);
    defineNative("strchr", strchrNative);
    defineNative("strstr", strstrNative);
    defineNative("strcpy", strcpyNative);
    defineNative("strdup", strdupNative);
    defineNative("strtok", strtokNative);
    defineNative("sprintf", sprintfNative);

    //Time functions
    defineNative("time", timeNative);
    defineNative("strftime", strftimeNative);

    //Misc functions
    defineNative("rand", randNative);
    defineNative("srand", srandNative);
    defineNative("assert", assertNative);
}