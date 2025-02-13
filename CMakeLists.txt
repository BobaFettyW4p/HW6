cmake_minimum_required(VERSION 3.5)
project(HW6)
set(CMAKE_CXX_STANDARD 20)
find_package(Threads REQUIRED)

add_executable(DistributedCounterTest1 DistributedCounterTest1.cpp)
target_link_libraries(DistributedCounterTest1 Threads::Threads)

add_executable(DistributedCounterTest2 DistributedCounterTest2.cpp)
target_link_libraries(DistributedCounterTest2 Threads::Threads)

add_executable(DistributedCounterTest3 DistributedCounterTest3.cpp)
target_link_libraries(DistributedCounterTest3 Threads::Threads)

add_executable(HW6-3 HW6-3.cpp)



