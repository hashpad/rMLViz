cmake_minimum_required(VERSION 3.30.5)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(NOT CMAKE_CXX_COMPILER)
	set(CMAKE_CXX_COMPILER "clang++")
endif()

if(NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE Debug)
endif()



project(ML VERSION 0.1 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
link_directories(${CMAKE_SOURCE_DIR}/lib)

FILE(GLOB ALL_SRCS src/*)

add_executable(
	ml
	${ALL_SRCS}
)


target_link_libraries(ml PRIVATE raylib)
