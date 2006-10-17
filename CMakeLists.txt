project(recppful)

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake/modules)
find_package(Curl)
find_package(Xerces)

#we link only to a part of boost libraries
set(BOOST_LIBS boost_iostreams)
find_package(Boost)

add_subdirectory(lib)
add_subdirectory(test)
add_subdirectory(example)
