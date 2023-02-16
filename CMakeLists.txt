project(DatReader CXX)
cmake_minimum_required(VERSION 3.14.6 FATAL_ERROR)

set(VERSION_MAJOR 0)
set(VERSION_MINOR 1)
set(VERSION_REL 0)
set(PROJECT_VERSION "${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_REL}")

set(PACKAGE_INSTALL_BIN_DIR bin CACHE PATH "Installation directory for executables")
set(PACKAGE_INSTALL_LIB_DIR lib CACHE PATH "Installation directory for libraries")
set(PACKAGE_INSTALL_INC_DIR include CACHE PATH "Installation directory for headers")
set(PACKAGE_INSTALL_DATA_DIR share CACHE PATH "Installation directory for data files")

find_package(ROOT 6.15 CONFIG REQUIRED)
include(${ROOT_USE_FILE})

find_package(OpenMP)
option(OpenMP_ACTIVE "Activate OpenMP parallel compilation" ON)
if(OPENMP_FOUND AND OpenMP_ACTIVE)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}" )
endif()

include_directories(${ROOT_INCLUDE_DIRS}
		    /usr/include/boost/)

add_subdirectory(run)
