cmake_minimum_required(VERSION 3.10)
project(augment)
 
# specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)
 
# Google Test
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})
# OpenCV
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})
 
set(SOURCE augment.cpp image.cpp drawing.cpp) 
add_executable(${PROJECT_NAME} ${SOURCE})
target_compile_options(${PROJECT_NAME} PRIVATE -Werror -Wall -Wextra)
target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS} ${GTEST_LIBRARIES} pthread)
