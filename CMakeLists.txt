cmake_minimum_required(VERSION 3.23)

project(koda LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17 REQUIRED)
set(ROOT "${CMAKE_SOURCE_DIR}")

set(CMAKE_CONFIGURATION_TYPES "Release" CACHE STRING "Release" FORCE)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY $<1:${CMAKE_SOURCE_DIR}/Release>)

include(cmake/CPM.cmake)
CPMAddPackage("gh:SFML/SFML#2.5.1")

find_package(doxygen REQUIRED)
if(${DOXYGEN_FOUND})
      add_custom_target(docs ALL
        COMMAND ${DOXYGEN_EXECUTABLE} docs.doxyfile
	COMMENT "Generating API documentation with Doxygen"
	VERBATIM
	WORKING_DIRECTORY ${PROJECT_SOURCE_DIR})
endif()


add_executable(${PROJECT_NAME} main.cpp)

target_include_directories(${PROJECT_NAME} PRIVATE include)
target_link_libraries(${PROJECT_NAME} PRIVATE sfml-graphics)


if (WIN32)
        set(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS} /SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup")
        if(BUILD_SHARED_LIBS)
                add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_RUNTIME_DLLS:${PROJECT_NAME}> $<TARGET_FILE_DIR:${PROJECT_NAME}> COMMAND_EXPAND_LISTS)
        endif()

endif()

target_link_options(${PROJECT_NAME} PRIVATE ${SUBSYSTEM_LINKER_OPTIONS})
target_compile_definitions(${PROJECT_NAME} PRIVATE ROOT="${CMAKE_SOURCE_DIR}")

install(TARGETS ${PROJECT_NAME} DESTINATION arcanoid/bin)
install(FILES 
${PROJECT_SOURCE_DIR}/include/ball.h 
${PROJECT_SOURCE_DIR}/include/brick.h 
${PROJECT_SOURCE_DIR}/include/player.h 
${PROJECT_SOURCE_DIR}/include/powerup.h 
${PROJECT_SOURCE_DIR}/include/wall.h 
DESTINATION arcanoid/include)
install(DIRECTORY ${PROJECT_SOURCE_DIR}/font DESTINATION arcanoid)
install(DIRECTORY ${PROJECT_SOURCE_DIR}/powers DESTINATION arcanoid)
install(FILES ${PROJECT_SOURCE_DIR}/HSCORE.txt DESTINATION arcanoid)
install(FILES 
${PROJECT_SOURCE_DIR}/Release/sfml-graphics-2.dll
${PROJECT_SOURCE_DIR}/Release/sfml-system-2.dll
${PROJECT_SOURCE_DIR}/Release/sfml-window-2.dll
 DESTINATION arcanoid/bin)