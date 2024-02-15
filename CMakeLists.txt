
cmake_minimum_required(VERSION 3.1.0)

# Set C compiler to gcc
set(CMAKE_C_COMPILER gcc)

# Set C++ compiler to g++
set(CMAKE_CXX_COMPILER g++)


# Check if C++ compiler information is available
message(STATUS "-- -- -- -- --")
if (CMAKE_CXX_COMPILER)
    message(STATUS "C++ compiler: ${CMAKE_CXX_COMPILER}")
    message(STATUS "C++ compiler version: ${CMAKE_CXX_COMPILER_VERSION}")
    message(STATUS "C++ compiler ID: ${CMAKE_CXX_COMPILER_ID}")
else()
    message(WARNING "C++ compiler information not available.")
endif()
message(STATUS "-- -- -- -- --")
# Check if C compiler information is available
if (CMAKE_C_COMPILER)
    message(STATUS "C compiler: ${CMAKE_C_COMPILER}")
    message(STATUS "C compiler version: ${CMAKE_C_COMPILER_VERSION}")
    message(STATUS "C compiler ID: ${CMAKE_C_COMPILER_ID}")
else()
    message(WARNING "C compiler information not available.")
endif()
message(STATUS "-- -- -- -- --")

set(CUI_PROJECT_NAME 
        main
)

set(CUI_SRC_DIR 
        main/srcs
)

set(CUI_INCLUDE_DIRS 
        main/includes
)
        
set(CUI_WX_WIDGETS_DIR 
        libs/wxWidgets
)
        
file(GLOB_RECURSE ALL_SRCS ${CUI_SRC_DIR}/*.cpp)
file(GLOB_RECURSE ALL_INCLUDES ${CUI_INCLUDE_DIRS}/*.h)

message(STATUS "-- -- -- -- --")
message(STATUS "Project name: ${CUI_PROJECT_NAME}")
message(STATUS "-- -- -- -- --")
message(STATUS "Including...")
foreach(include_files IN LISTS ALL_INCLUDES)
        message(STATUS "${include_files}")
endforeach()
message(STATUS "-- -- -- -- --")

project(${CUI_PROJECT_NAME})

add_subdirectory(
        ${CUI_WX_WIDGETS_DIR}
)

include_directories(
        ${CUI_INCLUDE_DIRS}
)

add_executable(${CUI_PROJECT_NAME} ${ALL_SRCS})
target_link_libraries(${CUI_PROJECT_NAME} wx::net wx::core wx::base)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fmem-report -save-temps -ggdb -Xlinker --Map=${CMAKE_BINARY_DIR}/${CUI_PROJECT_NAME}.map")


