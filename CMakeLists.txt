cmake_minimum_required(VERSION 3.0.0)
project(WiServer VERSION 0.1.0)

#include(CTest)
#enable_testing()

file(GLOB SOURCES "src/*.c")

add_executable(WiServer src/server.c src/docroot/ ${SOURCES})
target_include_directories(WiServer PRIVATE include/)
find_library(LIBCIVETWEB civetweb include/)
target_link_libraries(WiServer ${LIBCIVETWEB})

find_library(LIBJSONC json-c)
target_link_libraries(WiServer ${LIBJSONC})

find_library(LIBTHREAD pthread include/)
target_link_libraries(WiServer ${LIBTHREAD} ${CMAKE_DL_LIBS})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
