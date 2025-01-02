cmake_minimum_required(VERSION 3.10)
project(PyLite)

set(CMAKE_CXX_STANDARD 17)

# Include directories
include_directories(include)

# Source files
set(SOURCE_FILES
    main.cpp
    src/token.cpp
    src/lexer.cpp
    src/ast.cpp
    src/parser.cpp
    src/interpreter.cpp
)


add_executable(pylite ${SOURCE_FILES})
