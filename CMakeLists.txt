cmake_minimum_required(VERSION 3.22)
project(cpplox)

set(CMAKE_CXX_STANDARD 14)

include_directories(src)

add_executable(cpplox
        src/loxi.cc
        src/loxi.hh
        src/main.cc
        src/scanner.cc
        src/scanner.hh
        src/token.cc
        src/token.hh)
