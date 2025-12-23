cmake_minimum_required(VERSION 3.22)
project(TicTacToe VERSION 1.0.0)

List (APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")
include(FetchDependencies)

# Configuration
set(namespace "NameSpace::")
set(INSTALL_INC_DIR "include")
set(INSTALL_BIN_DIR "bin")
set(lib_name "${PROJECT_NAME}Lib")
set(exec_name "${PROJECT_NAME}")

# Source files
file(GLOB_RECURSE SOURCES source/*.cpp)

# Create the static library
add_library(${lib_name} STATIC ${SOURCES})

set_target_properties(${lib_name} PROPERTIES 
                        CXX_STANDARD 20
                        CXX_EXTENSIONS OFF)

target_include_directories(${lib_name} PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:${INSTALL_INC_DIR}>
)

target_link_libraries(${lib_name} PUBLIC raylib_static)

add_library(NameSpace::${lib_name} ALIAS ${lib_name})

# Create executable for the game
add_executable(${exec_name} main.cpp)  
target_link_libraries(${exec_name} PRIVATE ${lib_name})
set_target_properties(${exec_name} PROPERTIES 
                        CXX_STANDARD 20
                        CXX_EXTENSIONS OFF)

# install the game
install(TARGETS ${exec_name}
    RUNTIME DESTINATION ${INSTALL_BIN_DIR}
)

# Install resource files
install(
    DIRECTORY resources/
    DESTINATION ${INSTALL_BIN_DIR}/resources
    FILES_MATCHING PATTERN "*.*"
)
