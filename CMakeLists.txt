cmake_minimum_required(VERSION 3.16)
find_package(SystemCLanguage CONFIG REQUIRED)

include_directories(
  ./
)

set(srcfiles
  main.cpp
  fir.cpp
  tb.cpp
)

set(hdrfiles
  main.hpp
  fir.hpp
  tb.hpp
)

add_compile_options(-Wall -Wextra -pedantic)

add_library(design STATIC ${srcfiles} ${hdrfiles})
target_link_libraries(design PUBLIC SystemC::systemc booksim noc)