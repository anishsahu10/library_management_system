cmake_minimum_required(VERSION 3.10)
project(LibraryManagementSystem)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set compiler
if(WIN32)
    set(CMAKE_CXX_COMPILER g++)
endif()

# Add source files
set(SOURCES
    src/main.cpp
    src/User.cpp
    src/Book.cpp
    src/Account.cpp
    src/Student.cpp
    src/Faculty.cpp
    src/Librarian.cpp
    src/Library.cpp
)

# Add header files
set(HEADERS
    include/User.h
    include/Book.h
    include/Account.h
    include/Student.h
    include/Faculty.h
    include/Librarian.h
    include/Library.h
)

# Create executable
add_executable(lms ${SOURCES} ${HEADERS})

# Add include directories
target_include_directories(lms PRIVATE include)

# Set output directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)