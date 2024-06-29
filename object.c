#include <stdio.h>
#include <string.h>

#include "memory.h"
#include "object.h"
#include "table.h"
#include "value.h"
#include "vm.h"

#define ALLOCATE_OBJ(vm, type, objectType) (type*)allocateObject(vm, sizeof(type), objectType)

static Obj* allocateObject(VM* vm, size_t size, ObjType type) {
    Obj* object = (Obj*)reallocate(vm, NULL, 0, size);
    object->type = type;
    object->isMarked = false;
    object->next = vm->objects;
    vm->objects = object;

#ifdef DEBUG_LOG_GC
    printf("%p allocate %zu for %d\n", (void*)object, size, type);
#endif

    return object;
}

ObjList* newList(VM* vm){
    ObjList* list = ALLOCATE_OBJ(vm, ObjList, OBJ_LIST);
    list->items = NULL;
    list->count = 0;
    list->capacity = 0;
    return list;
}

void appendToList(VM* vm, ObjList* list, Value value) {
    // Grow the array if necessary
    if (list->capacity < list->count + 1) {
        int oldCapacity = list->capacity;
        list->capacity = GROW_CAPACITY(oldCapacity);
        list->items = GROW_ARRAY(vm, Value, list->items, oldCapacity, list->capacity);
    }
    list->items[list->count] = value;
    list->count++;
    return;
}

void storeToList(VM* vm, ObjList* list, int index, Value value){
    list->items[index] = value;
}

Value indexFromList(VM* vm, ObjList* list, int index){
    return list->items[index];
}

void deleteFromList(VM* vm, ObjList* list, int index){
    for (int i = index; i < list->count - 1; i++){
        list->items[i] = list->items[i + 1];
    }
    list->items[list->count - 1] = NIL_VAL;
    list->count--;
}

bool isValidListIndex(VM* vm, ObjList* list, int index){
    return index >= 0 && index < list->count;
}

ObjBoundMethod* newBoundMethod(VM* vm,Value receiver, ObjClosure* method) {
    ObjBoundMethod* bound = ALLOCATE_OBJ(vm, ObjBoundMethod, OBJ_BOUND_METHOD);
    bound->receiver = receiver;
    bound->method = method;
    return bound;
}

ObjClass* newClass(VM* vm, ObjString* name) {
    ObjClass* klass = ALLOCATE_OBJ(vm, ObjClass, OBJ_CLASS);
    klass->name = name;
    initTable(&klass->methods);
    return klass;
}

ObjClosure* newClosure(VM* vm, ObjFunction* function) {
    ObjUpvalue** upvalues = ALLOCATE(vm, ObjUpvalue*, function->upvalueCount);
    for (int i = 0; i < function->upvalueCount; i++) {
        upvalues[i] = NULL;
    }

    ObjClosure* closure = ALLOCATE_OBJ(vm, ObjClosure, OBJ_CLOSURE);
    closure->function = function;
    closure->upvalues = upvalues;
    closure->upvalueCount = function->upvalueCount;
    return closure;
}

ObjFunction* newFunction(VM* vm) {
    ObjFunction* function = ALLOCATE_OBJ(vm, ObjFunction, OBJ_FUNCTION);
    function->arity = 0;
    function->upvalueCount = 0;
    function->name = NULL;
    initChunk(&function->chunk);
    return function;
}

ObjInstance* newInstance(VM* vm, ObjClass* klass) {
    ObjInstance* instance = ALLOCATE_OBJ(vm, ObjInstance, OBJ_INSTANCE);
    instance->klass = klass;
    initTable(&instance->fields);
    return instance;
}

ObjNativeFunction* newNativeFunction(VM* vm, NativeFn function) {
    ObjNativeFunction * nativeFunction = ALLOCATE_OBJ(vm, ObjNativeFunction, OBJ_NATIVE_FUNCTION);
    nativeFunction->function = function;
    return nativeFunction;
}

ObjNativeMethod* newNativeMethod(VM* vm, NativeMethod method){
    ObjNativeMethod* nativeMethod = ALLOCATE_OBJ(vm, ObjNativeMethod, OBJ_NATIVE_METHOD);
    nativeMethod->method = method;
    return nativeMethod;
}

static ObjString* allocateString(VM* vm, char* chars, int length, uint32_t hash) {
    ObjString* string = ALLOCATE_STRING(vm, length);
    string->length = length;
    string->hash = hash;

    push(vm, OBJ_VAL(string));
    memcpy(string->chars, chars, length);
    string->chars[length] = '\0';
    tableSet(vm, &vm->strings, string, NIL_VAL);
    pop(vm);

    return string;
}

static uint32_t hashString(const char* key, int length) {
    uint32_t hash = 2166136261u;
    for (int i = 0; i < length; i++) {
        hash ^= (uint8_t)key[i];
        hash *= 16777619;
    }
    return hash;
}

ObjString* takeString(VM* vm, char* chars, int length) {
    uint32_t hash = hashString(chars, length);
    ObjString* interned = tableFindString(&vm->strings, chars, length, hash);
    if (interned != NULL) {
        FREE_ARRAY(vm, char, chars, length + 1);
        return interned;
    }

    return allocateString(vm, chars, length, hash);
}

ObjString* copyString(VM* vm, const char* chars, int length) {
    uint32_t hash = hashString(chars, length);
    ObjString* interned = tableFindString(&vm->strings, chars, length, hash);
    if (interned != NULL) return interned;

    char* heapChars = ALLOCATE(vm, char, length + 1);
    memcpy(heapChars, chars, length);
    heapChars[length] = '\0';

    return allocateString(vm, heapChars, length, hash);
}

ObjUpvalue* newUpvalue(VM* vm, Value* slot) {
    ObjUpvalue* upvalue = ALLOCATE_OBJ(vm, ObjUpvalue, OBJ_UPVALUE);
    upvalue->closed = NIL_VAL;
    upvalue->location = slot;
    upvalue->next = NULL;
    return upvalue;
}

static void printFunction(ObjFunction* function) {
    if (function->name == NULL) {
        printf("<script>");
        return;
    }
    printf("<fn %s>", function->name->chars);
}


void printObject(Value value) {
    switch (OBJ_TYPE(value)) {
        case OBJ_BOUND_METHOD:
            printFunction(AS_BOUND_METHOD(value)->method->function);
            break;
        case OBJ_CLASS:
            printf("%s", AS_CLASS(value)->name->chars);
            break;
        case OBJ_CLOSURE:
            printFunction(AS_CLOSURE(value)->function);
            break;
        case OBJ_FUNCTION:
            printFunction(AS_FUNCTION(value));
            break;
        case OBJ_INSTANCE:
            printf("%s instance", AS_INSTANCE(value)->klass->name->chars);
            break;
        case OBJ_NATIVE_FUNCTION:
            printf("<native fn>");
            break;
        case OBJ_NATIVE_METHOD:
            printf("<native method>");
            break;
        case OBJ_STRING:
            printf("%s", AS_CSTRING(value));
            break;
        case OBJ_UPVALUE:
            printf("upvalue");
            break;
        case OBJ_LIST:
            printf("[");
            for (int i = 0; i < AS_LIST(value)->count; i++){
                printValue(AS_LIST(value)->items[i]);
                if (i != AS_LIST(value)->count - 1){
                    printf(", ");
                }
            }
            printf("]");
            break;
    }
}
