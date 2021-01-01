cmake_minimum_required(VERSION 3.17)
project(riscvVM C)

set(CMAKE_C_STANDARD 11)

add_executable(riscvVM main.c elfhandler.h elfhandler.c virtualmachine.c virtualmachine.h)