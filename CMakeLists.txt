cmake_minimum_required(VERSION 3.22.1)
project(my_webserver)
SET(CMAKE_CXX_STANDARD 20)


add_executable(my_webserver main.cpp
        ShoDo/base/StringPiece.h
        ShoDo/base/types.h
        ShoDo/server/InetAddr.h
        ShoDo/server/InetAddr.cpp
        ShoDo/base/TimeStamp.h
)

add_executable(TEST ShoDo/tests/test_string_piece.cpp
        ShoDo/base/StringPiece.h
        ShoDo/base/types.h)