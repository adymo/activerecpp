include_directories(${BOOST_INCLUDE_DIR} ${XERCES_INCLUDE_DIR} ${CURL_INCLUDE_DIR})

########### next target ###############
set(recppful_LIB_SRCS
    resource.cpp
    http.cpp
    xmlparser.cpp
    DOMTreeErrorReporter.cpp
)

add_library(recppful SHARED ${recppful_LIB_SRCS})
target_link_libraries(recppful ${BOOST_LIBRARIES} ${CURL_LIBRARIES} ${XERCES_LIBRARIES})
set_target_properties(recppful PROPERTIES VERSION 0.0.1 SOVERSION 0)
