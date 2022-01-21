cmake_minimum_required(VERSION 3.0.0)

set(MODULE_NAME "NetworkRequest")
set(${MODULE_NAME}_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR} PARENT_SCOPE)
set(${MODULE_NAME}_LIBRARIES ${MODULE_NAME} PARENT_SCOPE)


find_package(Qt5Core)
find_package(Qt5Widgets)
find_package(Qt5Network)


add_library(${MODULE_NAME}
    NetworkRequest.cpp NetworkRequest.h
)

target_link_libraries(${MODULE_NAME} Qt5::Core Qt5::Network)


# target_include_directories(${MODULE_NAME} PRIVATE
#     ${NetworkRequest_INCLUDE_DIRS}
# )
# target_link_libraries(${MODULE_NAME} Qt5::Core Qt5::Network
#     ${NetworkRequest_LIBRARIES}
# )
