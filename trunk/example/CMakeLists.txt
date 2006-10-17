include_directories(${CMAKE_SOURCE_DIR}/lib ${XERCES_INCLUDE_DIR} ${BOOST_INCLUDE_DIR} ${CURL_INCLUDE_DIR})

########### next target ###############
set(example_SRCS
    example.cpp
)

add_executable(example ${example_SRCS})
target_link_libraries(example recppful ${BOOST_LIBRARIES} ${CURL_LIBRARIES} ${XERCES_LIBRARIES})
