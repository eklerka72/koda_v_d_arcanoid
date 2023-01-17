cmake_minimum_required(VERSION 3.23)

project(koda LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CONFIGURATION_TYPES "Release" CACHE STRING "" FORCE)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR})

include(cmake/CPM.cmake)
CPMAddPackage("gh:SFML/SFML#2.5.1")

add_executable(${PROJECT_NAME} main.cpp)


target_include_directories(${PROJECT_NAME} PRIVATE include)
target_link_libraries(${PROJECT_NAME} PRIVATE sfml-graphics)

if (WIN32 AND BUILD_SHARED_LIBS)
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_RUNTIME_DLLS:${PROJECT_NAME}> $<TARGET_FILE_DIR:${PROJECT_NAME}> COMMAND_EXPAND_LISTS)
endif()