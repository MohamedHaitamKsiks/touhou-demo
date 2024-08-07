cmake_minimum_required(VERSION 3.22.1)
set(CMAKE_CXX_STANDARD 20)

include_directories({ASENGINE_INCLUDE_PATH})


project(asengine-project)

file(GLOB_RECURSE SOURCES *.cpp)

add_library(
    asengine-project
    STATIC
    ${SOURCES}
)

target_link_libraries(
    asengine-project
)

set(PROJECT_LIBRARIES
    asengine-project
    PARENT_SCOPE
)
