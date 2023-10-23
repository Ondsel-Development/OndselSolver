cmake_minimum_required(VERSION 3.16)

project(OndselSolver VERSION 1.0.1 DESCRIPTION "Assembly Constraints and Multibody Dynamics code")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include(GNUInstallDirs)

add_library(OndselSolver STATIC)

add_subdirectory(OndselSolver)

target_include_directories(OndselSolver PRIVATE "${PROJECT_SOURCE_DIR}/OndselSolver")

set_target_properties(OndselSolver
        PROPERTIES VERSION ${PROJECT_VERSION}
        SOVERSION 1
)

configure_file(OndselSolver.pc.in ${CMAKE_BINARY_DIR}/OndselSolver.pc @ONLY)
install(TARGETS OndselSolver
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
        FILE_SET HEADERS)
install(FILES ${CMAKE_BINARY_DIR}/OndselSolver.pc
        DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/pkgconfig)
