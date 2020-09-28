cmake_minimum_required(VERSION 3.5)
project(gamepad_interface)

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)


SET(CMAKE_INCLUDE_CURRENT_DIR ON) # to include the binary directory of the project to include all the moc generated header


SET(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH_1})

set(CMAKE_CXX_STANDARD 14)

if(POLICY CMP0071)
  cmake_policy(SET CMP0071 OLD)
endif()

# Instruct CMake to run moc automatically when needed
set(CMAKE_AUTOMOC ON)

set(CMAKE_AUTOUIC ON)


include_directories("include/")
include_directories(${CMAKE_BINARY_DIR})


add_executable(${PROJECT_NAME} main.cpp ${tst_hdr_moc})
#add_executable(${PROJECT_NAME} main.cpp )
