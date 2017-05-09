cmake_minimum_required(VERSION 3.7)
project(PriorityQueueVsHeapQ)

set(CMAKE_C_STANDARD 99)
INCLUDE_DIRECTORIES(C:/cunit/include)
LINK_DIRECTORIES(C:/cunit/lib)


set(SOURCE_FILES main.c src/PriorityQueue.c inc/PriorityQueue.h src/Heap.c inc/Heap.h)
set(SOURCE_final test.c src/PriorityQueue.c inc/PriorityQueue.h)
add_executable(PriorityQueueVsHeapQ ${SOURCE_FILES})
add_executable(funf ${SOURCE_final} )
target_link_libraries(funf cunit)