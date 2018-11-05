cmake_minimum_required(VERSION 3.1.0)

project(sandbox)
if( WIN32 )
  SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /openmp")
  SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /openmp")
endif()
set(CMAKE_INCLUDE_CURRENT_DIR ON)
find_package(OpenMP)
if (OPENMP_FOUND)
    set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
    set (CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
endif()


file(GLOB SRC "*.h" "*.hpp" "*.cpp" "*.ui")
add_executable(sandbox ${SRC})