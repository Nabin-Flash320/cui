
cmake_minimum_required(VERSION 3.1.0)

set(CUI_PROJECT_NAME 
        main
)

set(CUI_SRC_DIR 
        srcs
)

set(CUI_INCLUDE_DIRS 
        includes
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





