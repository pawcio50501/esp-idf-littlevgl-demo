# The following lines of boilerplate have to be in your project's
# CMakeLists in this exact order for cmake to work correctly
cmake_minimum_required(VERSION 3.5)

include($ENV{IDF_PATH}/tools/cmake/project.cmake)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -DTOUCH_SUPPORT=1 -DENABLE_TOUCH_INPUT") 
set(CMAKE_CXX_FLAGS "${CMAKE_C_FLAGS} -DTOUCH_SUPPORT=1 -DENABLE_TOUCH_INPUT")

project(esp-idf-littlevgl-demo)
