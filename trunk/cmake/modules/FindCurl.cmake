# - Find Curl
# Find the Curl includes and libraries
#
# This module defines
#  CURL_INCLUDE_DIR
#  CURL_LIBRARIES
#  CURL_FOUND

find_program(CURL_CONFIG_EXECUTABLE NAMES curl-config PATHS
    /usr/bin
    /usr/local/bin
)

#reset vars
set(CURL_LIBRARIES)
set(CURL_INCLUDE_DIR)

if (CURL_CONFIG_EXECUTABLE)
    exec_program(${CURL_CONFIG_EXECUTABLE} ARGS --libs RETURN_VALUE _return_VALUE OUTPUT_VARIABLE CURL_LIBRARIES)
    exec_program(${CURL_CONFIG_EXECUTABLE} ARGS --cflags RETURN_VALUE _return_VALUE OUTPUT_VARIABLE CURL_INCLUDE_DIR)
    if (CURL_LIBRARIES AND CURL_INCLUDE_DIR)
        set(CURL_FOUND TRUE)
        message(STATUS "Found curl: ${CURL_LIBRARIES}")
    else (CURL_LIBRARIES AND CURL_INCLUDE_DIR)
        message(FATAL_ERROR "Could not find curl library")
    endif (CURL_LIBRARIES AND CURL_INCLUDE_DIR)

    mark_as_advanced(CURL_LIBRARIES CURL_INCLUDE_DIR)
endif (CURL_CONFIG_EXECUTABLE)
