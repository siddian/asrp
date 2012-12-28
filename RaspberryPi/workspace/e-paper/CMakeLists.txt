cmake_minimum_required (VERSION 2.6) 

project (ePaper)

message(STATUS "processor: ${CMAKE_SYSTEM_PROCESSOR}")

add_subdirectory (EPlibrary)
add_subdirectory (Examples/pgmloader)
