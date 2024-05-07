cmake_minimum_required(VERSION 3.16)
project(SystemCPractice)  # Name your project

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(SystemCLanguage CONFIG REQUIRED)  # Find SystemC

# Include directories
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}  # Include current source dir for header files
)

# Source and header files
set(SRC_FILES
    main.cpp
    fir.cpp
    tb.cpp
)

set(HEADER_FILES
    fir.hpp
    tb.hpp
)

# Add compile options
add_compile_options(-Wall -Wextra -pedantic)

# Create a static library
add_library(design STATIC ${SRC_FILES} ${HEADER_FILES})

# Link the library with SystemC and other libraries
target_link_libraries(design PUBLIC SystemC::systemc)

# If executable is needed:
# add_executable(main_exec ${SRC_FILES})
# target_link_libraries(main_exec PUBLIC design)
# Create executable that runs sc_main in main.cpp
add_executable(main_exec main.cpp)  # This line tells CMake to compile main.cpp as an executable
target_link_libraries(main_exec PUBLIC design)  # Link the 'design' library with the executable