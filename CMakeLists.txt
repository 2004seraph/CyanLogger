# CMakeList.txt : CMake project for CyanLogger, include source and define
# project specific logic here.
#
cmake_minimum_required(VERSION 3.8)

include(CMakePackageConfigHelpers)
include(GNUInstallDirs)

set(CMAKE_CXX_STANDARD 17)

project(
	"CyanLogger"
	VERSION 1.0.0
	DESCRIPTION "A C++ logging library"
)

include_directories(
  ${PROJECT_NAME}
  "include/"
)

add_library(${PROJECT_NAME} STATIC
    src/CyanLogger.cpp
)

set_target_properties(
    ${PROJECT_NAME} PROPERTIES 

    VERSION ${PROJECT_VERSION}
    SOVERSION 1
    PUBLIC_HEADER ${CMAKE_CURRENT_SOURCE_DIR}/include/CyanLogger.hpp
)

target_include_directories(
    ${PROJECT_NAME} PUBLIC 
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/${PROJECT_NAME}>  
    $<INSTALL_INTERFACE:include/${PROJECT_NAME}>  # <prefix>/include/mylib
)

install(
    TARGETS ${PROJECT_NAME} 
    EXPORT ${PROJECT_NAME}-targets
)
install(
    DIRECTORY ${CMAKE_SOURCE_DIR}/include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)
install(
    EXPORT ${PROJECT_NAME}-targets
	NAMESPACE ${PROJECT_NAME}::
	DESTINATION ${CMAKE_INSTALL_DATADIR}/${PROJECT_NAME})


add_subdirectory("tests")