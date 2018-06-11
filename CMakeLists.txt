cmake_minimum_required(VERSION 3.6)
project(SIC_xe_Assembler)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp Expression.cpp Format.cpp LineOfCode.cpp ListingFile.cpp ObjectFile.cpp Opcode_SIC.cpp
        PassOne.cpp Literal.cpp )

INCLUDE_DIRECTORIES( Include  Map )


add_executable(SIC_xe_Assembler ${SOURCE_FILES})