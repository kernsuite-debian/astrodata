cmake_minimum_required(VERSION 3.10)
project(AstroData VERSION 3.1.1)
include(GNUInstallDirs)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++14")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -march=native -mtune=native")
if($ENV{LOFAR})
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DHAVE_HDF5")
endif()
if($ENV{PSRDADA})
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DHAVE_PSRDADA")
endif()

# libastrodata
add_library(astrodata SHARED
  src/Observation.cpp
  src/Platform.cpp
  src/ReadData.cpp
  src/SynthesizedBeams.cpp
)
set_target_properties(astrodata PROPERTIES
  VERSION ${PROJECT_VERSION}
  SOVERSION 1
  PUBLIC_HEADER "include/Generator.hpp;include/Observation.hpp;include/Platform.hpp;include/ReadData.hpp;include/SynthesizedBeams.hpp"
)
target_include_directories(astrodata PRIVATE include)

install(TARGETS astrodata
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)
