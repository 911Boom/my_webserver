cmake_minimum_required(VERSION 3.22.1)
project(my_webserver)
SET(CMAKE_CXX_STANDARD 20)
find_package(Boost REQUIRED COMPONENTS system thread)
include_directories(${Boost_INCLUDE_DIRS})

include_directories(ShoDo)
link_directories(ShoDo)


add_executable(my_webserver main.cpp
        ShoDo/base/StringPiece.h
        ShoDo/base/types.h
        ShoDo/server/InetAddr.h
        ShoDo/server/InetAddr.cpp
        ShoDo/base/TimeStamp.h
        ShoDo/server/webserver.h
        ShoDo/pool/ThreadPool.h
        ShoDo/pool/ThreadPool.cpp
        ShoDo/server/Socket.cpp
        ShoDo/server/Socket.h
        ShoDo/pool/EventLoop.cpp
        ShoDo/pool/EventLoop.h
        ShoDo/channel/EPoller.cpp
        ShoDo/channel/EPoller.h
        ShoDo/channel/Channel.cpp
        ShoDo/channel/Channel.h
        ShoDo/Time/TimerQueue.cpp
        ShoDo/Time/TimerQueue.h
        ShoDo/Time/Timer.h
        ShoDo/Time/TimeId.h
        ShoDo/Time/callbacks.h
)

add_executable(TEST_STRING_PIECE ShoDo/tests/test_string_piece.cpp

        ShoDo/base/StringPiece.h
        ShoDo/base/types.h)

add_executable(TEST_TIME_STAMP ShoDo/tests/test_TimeStamp.cpp
        ShoDo/base/TimeStamp.h
        ShoDo/tests/test_TimeStamp.cpp)


add_executable(TRY_ATOMIC ShoDo/tests/try_atomic.cpp)

add_executable(TEST_INET_ADDR ShoDo/tests/test_InetAddr.cpp
        ShoDo/server/InetAddr.h)

