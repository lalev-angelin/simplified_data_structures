cmake_minimum_required(VERSION 3.23)
project(simplified_data_structures)

set(CMAKE_CXX_STANDARD 17)

add_executable(simplified_data_structures main.cpp Stack.h IntStack.h IntQueue.h Queue.h Tree.h Deque.h IntDeque.h)
