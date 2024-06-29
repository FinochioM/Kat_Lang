cmake_minimum_required(VERSION 3.28)
project(Kat C)

set(CMAKE_C_STANDARD 11)

add_executable(Kat main.c
        chunk.c
        memory.h
        memory.c
        debug.h
        debug.c
        value.h
        value.c
        vm.h
        vm.c
        compiler.h
        compiler.c
        scanner.h
        scanner.c
        object.h
        object.c
        table.h
        table.c
        core_library.c
        core_library.h
        resource.h
        native.h
        native.c
)
