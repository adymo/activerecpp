# - Find Boost
# Find the Boost includes and libraries
#
# If BOOST_LIBS variable is set then only libraries in BOOST_LIBS
# are searched for and included in BOOST_LIBRARIES.
# Otherwise, all boost libraries will be included.
#
# This module defines
#  BOOST_INCLUDE_DIR
#  BOOST_LIBRARIES
#  BOOST_FOUND

find_path(BOOST_INCLUDE_DIR version.hpp
    /usr/local/include
    /usr/include
    /usr/include/boost
    /usr/local/include/boost
)

set(BOOST_LIBRARY)
if (NOT BOOST_LIBS)
    set(BOOST_LIBS
        boost_date_time
        boost_filesystem
        boost_iostreams
        boost_prg_exec_monitor
        boost_program_options
        boost_regex
        boost_serialization
        boost_signals
        boost_test_exec_monitor
        boost_thread-mt
        boost_unit_test_framework
        boost_wave
        boost_wserialization
    )
endif (NOT BOOST_LIBS)

foreach (boost_lib ${BOOST_LIBS})
    set(LIB_NAME "${boost_lib}_lib")
    find_library(BOOST_${boost_lib}
        ${boost_lib}
        PATHS /usr/lib /usr/local/lib
    )
    set(BOOST_LIBRARY ${BOOST_LIBRARY} ${BOOST_${boost_lib}})
endforeach (boost_lib)

if (BOOST_LIBRARY AND BOOST_INCLUDE_DIR)
    set(BOOST_LIBRARIES ${BOOST_LIBRARY})
    set(BOOST_FOUND "YES")
else (BOOST_LIBRARY AND BOOST_INCLUDE_DIR)
    set(BOOST_FOUND "NO")
endif (BOOST_LIBRARY AND BOOST_INCLUDE_DIR)

if (BOOST_FOUND)
    message(STATUS "Found Boost: ${BOOST_LIBRARIES}")
else (BOOST_FOUND)
    message(FATAL_ERROR "Could not find Boost library")
endif (BOOST_FOUND)

mark_as_advanced(
    BOOST_LIBRARY
    BOOST_INCLUDE_DIR
)
