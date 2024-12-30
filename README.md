# PyLite C++: A Simplified Python-like Language Interpreter (C++)

**GitHub Repository:** [https://github.com/DarsheeeGamer/Pylite-C/](https://github.com/DarsheeeGamer/Pylite-C/)

## Introduction

PyLite C++ is a simplified programming language interpreter, inspired by Python, implemented in C++. It's designed to demonstrate core compiler concepts like lexing, parsing, and interpretation using a compiled language and provides a performant implementation of the PyLite language.

This project provides a command-line interface (CLI) that can execute .pylite files or interpret code interactively.

## Features

*   **Basic Data Types:** Integers, Floats, Strings, Booleans
*   **Dynamic Typing:** Like Python, variables don't need explicit type declarations.
*   **Arithmetic Operators:** `+`, `-`, `*`, `/`, `//`, `%`, `**`
*   **Comparison Operators:** `==`, `!=`, `>`, `<`, `>=`, `<=`
*   **Logical Operators:** `and`, `or`, `not`
*   **Conditional Statements:** `if`, `elif`, `else`
*   **Looping:** `while`
*   **Basic Input/Output:** `print()` for output, `input()` for user input
*   **Built-in Functions:** `len()`, `int()`, `float()`, `str()`
*   **User-Defined Functions:** Allows user defined function with arguments and return statements
*   **Comments:** `#` for single-line comments
*   **File Execution:** Can run `.pylite` files from the command line
*   **Interactive Mode:** REPL (Read-Eval-Print Loop) for interactive code execution

## Project Structure

```
pylite/
├── include/             # Header files
│   ├── token.h
│   ├── lexer.h
│   ├── ast.h
│   ├── parser.h
│   └── interpreter.h
├── src/                 # Source files
│   ├── token.cpp
│   ├── lexer.cpp
│   ├── ast.cpp
│   ├── parser.cpp
│   └── interpreter.cpp
├── main.cpp             # Main program file
└── CMakeLists.txt       # CMake configuration file
```

## Compilation

### Prerequisites

*   **C++ Compiler:** You need a C++17 compatible compiler (GCC, Clang, MSVC).
*   **CMake:** You need CMake (version 3.10 or newer) installed. You can download it from the official CMake website ([https://cmake.org/download/](https://cmake.org/download/)).

### Compilation Steps

Here are the steps for macOS, Linux, and Windows:

**1. macOS**

   *   **Open Terminal:** Open a terminal window.
   *   **Navigate to Project Root:** Use the `cd` command to navigate to the `pylite` root directory.
   *   **Create `build` Directory:** Create a `build` directory inside the `pylite` root using the command `mkdir build`
   * **Navigate into `build` Directory:** Navigate to the created `build` directory using the command `cd build`.
   *   **Generate Build Files:** Execute `cmake ..`
   *   **Build:** Execute `make` or `cmake --build .`
   *   **Executable Location:** The executable `pylite` will be in the `build` directory.

**2. Linux**

   *   **Open Terminal:** Open a terminal window.
     *   **Navigate to Project Root:** Use the `cd` command to navigate to the `pylite` root directory.
   *   **Create `build` Directory:** Create a `build` directory inside the `pylite` root using the command `mkdir build`
   * **Navigate into `build` Directory:** Navigate to the created `build` directory using the command `cd build`.
   *   **Generate Build Files:** Execute `cmake ..`
   *   **Build:** Execute `make` or `cmake --build .`
   *   **Executable Location:** The executable `pylite` will be in the `build` directory.

**3. Windows**

   *   **Install CMake and a C++ compiler:** Ensure that you have CMake installed and a C++ compiler like Visual Studio or MinGW installed
   * **Open CMake GUI:** Open the CMake GUI application.
    * **Set Source and Build Directories:**
        *   Set the "Where is the source code:" field to the directory containing `CMakeLists.txt` (i.e the `pylite` folder).
        *   Set the "Where to build the binaries:" field to the `build` directory inside the `pylite` folder.
    * **Configure:** Click the "Configure" button.
        *   Select your generator (Visual Studio version or MinGW Makefiles) and click "Finish."
    * **Generate:** Click the "Generate" button.
    * **Open Build Folder:** Open the `build` folder
    * **Build using the generated files:**
        * If you have visual studio as the generator, then open the generated visual studio project file and build through the Visual studio GUI
        * If you have used Makefiles using MinGW, then open the terminal, navigate to the `build` folder, and use the `make` or `cmake --build .` command to compile the project
    *   **Executable Location:** The executable `pylite.exe` will be in the `build` directory.

## Usage

### Running from CLI

1.  **Navigate:** Open your terminal or command prompt and navigate to the `build` directory
2.  **Execute a .pylite file:**

    ```bash
     ./pylite your_script.pylite # macOS or Linux
     pylite.exe your_script.pylite # Windows
    ```

    (Replace `your_script.pylite` with the path to your PyLite script file.)
    - Note: Only .pylite files will be executed

3.  **Interactive Mode**

    ```bash
     ./pylite  # macOS or Linux
     pylite.exe # Windows
    ```

    This will launch a command-line interpreter where you can enter and run PyLite code line by line. To exit the interpreter type `exit()`.

### Example Pylite Code `example.pylite`

```pylite
def add(x, y):
   return x + y
def greet(name):
   return "Hello, " + name + "!"


result = add(5, 3)
print("Sum:", result)

message = greet("Pylite User")
print(message)

my_string = "Hello"
print("Length of my_string:",len(my_string))

input_value = input("Enter something: ")
print("You entered:", input_value)

num_str = "123"
num_int = int(num_str)
num_float = float(num_str)
print("Integer:", num_int)
print("Float:", num_float)

number = 234.34
print("String:",str(number))
```

## Development Notes

This project is intended to be a learning tool for understanding the following concepts:

*   **Lexing:** Converting raw code into a stream of tokens.
*   **Parsing:** Organizing tokens into an AST that represents the structure of the code.
*   **Interpretation:** Traversing the AST and executing the program.

### Possible Future Enhancements

*   Add support for more complex data structures like lists and dictionaries.
*   Improve error messages.
*   Implement more standard library functions.
*   Implement a type system
