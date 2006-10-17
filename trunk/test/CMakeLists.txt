include_directories(${CMAKE_SOURCE_DIR}/lib ${XERCES_INCLUDE_DIR} ${BOOST_INCLUDE_DIR} ${CURL_INCLUDE_DIR})

########### next target ###############
set(test_resource_SRCS
    test_resource.cpp
)

add_executable(test_resource ${test_resource_SRCS})
target_link_libraries(test_resource recppful ${BOOST_LIBRARIES}
    ${CURL_LIBRARIES} ${XERCES_LIBRARIES} boost_unit_test_framework)

add_test(resource ${EXECUTABLE_OUTPUT_PATH}/test_resource)
