# Kat Language

Kat is a programming language designed with a primary focus on automation. Inspired by tools like BluePrism and UiPath, Kat allows developers to automate tasks through direct programming. It aims to provide a robust, easy-to-use platform for creating automation scripts and applications.

## Key Features

- **Simple and Intuitive Syntax**: Kat aims to combine the simplicity of Python with the structured approach of RPA tools.
- **Automation-Centric**: Built specifically for automating repetitive tasks, data handling, and system integration.
- **Statically and Strongly Typed**: Ensures reliability and performance with a robust type system.
- **Object-Oriented**: Supports classes, inheritance, and polymorphism to enable complex automation workflows.

## Current State

The Kat language currently includes the following features and functionalities:

### Core Language

- **Variables**: Declare and use variables to store and manipulate data.
- **Functions**: Define and call functions to encapsulate reusable code.
- **Control Flow**: If statements, while loops, and for loops to control the execution flow.
- **Error Handling**: Similar to Rust's `Result` and `Option` types for managing errors gracefully.

### Core/Prelude Library

- **Mathematical Functions**:
  - `abs`, `sqrt`, `sin`, `cos`, `tan`
  - `asin`, `acos`, `atan`
  - `sinh`, `cosh`, `tanh`
  - `log10`, `fabs`
- **String Functions**:
  - `strlen`, `strcat`, `strcmp`, `strcpy`
  - `strstr`, `strtok`

### Native Functions

- **Clock**: `clock()` - Returns the current time in seconds.
- **Input**: `input()` - Reads a line from standard input.

### Arrays

- **Array Creation**: `var arr = [1, 2, 3, 4, 5];`
- **Array Access**: `arr[0]`, `arr[1]`, etc.
- **Array Modification**: `arr[1] = 42`

- You can also concatenate string/number functionality.

- **Creation with number functions**: `var arr = [abs(10), sqrt(4), 3 + 2, 4 / 2, 5];`
- **Creation with string functions**: `var arr = [strcat("Test ", "Array"), strlen("Returns number with len")];`

### Example Usage

```kat
// Variable declaration
var x = 10;
var y = 20;

// Function definition
fun add(a, b) {
  return a + b;
}

// Control flow
if (x > y) {
  print("x is greater");
} else {
  print("y is greater");
}

// Using arrays
var arr = [1, 2, 3, 4, 5];
print(arr[0]);  // Should print: 1

// Using string functions
var str1 = "Hello";
var str2 = "World";
var result = strcat(str1, str2);
print(result);  // Should print: HelloWorld
