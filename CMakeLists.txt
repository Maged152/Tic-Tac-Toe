cmake_minimum_required(VERSION 3.22)
project(TicTacToe VERSION 1.0.0)

List (APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")
include(FetchDependencies)

# Configuration
set(version_config "${PROJECT_NAME}ConfigVersion.cmake")
set(project_config "${PROJECT_NAME}Config.cmake")
set(TARGETS_EXPORT_NAME "${PROJECT_NAME}Targets")
set(namespace "NameSpace::")
set(INSTALL_INC_DIR "include")
set(INSTALL_BIN_DIR "bin")
set(INSTALL_LIB_DIR "lib")
set(INSTALL_RUN_DIR "dll")
set(INSTALL_CFG_DIR "cmake")

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

# Create excutable for the game
add_executable(${exec_name} main.cpp)  
target_link_libraries(${exec_name} PRIVATE ${lib_name})

# Install the library
# install(TARGETS ${PROJECT_NAME}
#     EXPORT "${TARGETS_EXPORT_NAME}"
#     LIBRARY DESTINATION ${INSTALL_LIB_DIR}
#     ARCHIVE DESTINATION ${INSTALL_LIB_DIR}
#     RUNTIME DESTINATION ${INSTALL_RUN_DIR}
#     INCLUDES DESTINATION ${INSTALL_INC_DIR}
# )

# install(EXPORT "${TARGETS_EXPORT_NAME}"
#     NAMESPACE "${namespace}"
#     DESTINATION "${INSTALL_CFG_DIR}"
# )

# install(
#     DIRECTORY include/ dependencies/
#     DESTINATION ${INSTALL_INC_DIR}
#     FILES_MATCHING PATTERN "*.h"
# )

# # Create the package configuration file
# include(CMakePackageConfigHelpers)
# configure_package_config_file(
#   "${CMAKE_CURRENT_SOURCE_DIR}/cmake/${project_config}.in"
#   "${CMAKE_CURRENT_BINARY_DIR}/${project_config}"
#   INSTALL_DESTINATION "${INSTALL_CFG_DIR}"
# )

# # Write the library version file
# write_basic_package_version_file(
#   "${CMAKE_CURRENT_BINARY_DIR}/${version_config}"
#   COMPATIBILITY AnyNewerVersion
# )

# # Install configuration and version files
# install(FILES 
#     "${CMAKE_CURRENT_BINARY_DIR}/${version_config}"
#     "${CMAKE_CURRENT_BINARY_DIR}/${project_config}"
#     DESTINATION ${INSTALL_CFG_DIR}
# )