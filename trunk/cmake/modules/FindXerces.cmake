# - Find Xerces-C++
# Find the Xerces-C++ includes and libraries
#
# This module defines
#  XERCES_INCLUDE_DIR
#  XERCES_LIBRARIES
#  XERCES_FOUND

find_path(XERCES_INCLUDE_DIR version.hpp
    /usr/local/include
    /usr/include
    /usr/include/boost
    /usr/local/include/boost
)

find_library(XERCES_LIBRARIES
    xerces-c
    PATHS /usr/lib /usr/local/lib
)

if (XERCES_LIBRARIES AND XERCES_INCLUDE_DIR)
    set(XERCES_FOUND "YES")
else (XERCES_LIBRARIES AND XERCES_INCLUDE_DIR)
    set(XERCES_FOUND "NO")
endif (XERCES_LIBRARIES AND XERCES_INCLUDE_DIR)

if (XERCES_FOUND)
    message(STATUS "Found Xerces-C++: ${XERCES_LIBRARIES}")
else (XERCES_FOUND)
    message(FATAL_ERROR "Could not find Xerces-C++ library")
endif (XERCES_FOUND)

mark_as_advanced(
    XERCES_LIBRARY
    XERCES_INCLUDE_DIR
)
