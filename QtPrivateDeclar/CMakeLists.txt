cmake_minimum_required(VERSION 3.0.0)

set(MODULE_NAME "QtPrivateDeclar")
set(${MODULE_NAME}_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR} PARENT_SCOPE)
set(${MODULE_NAME}_LIBRARIES ${MODULE_NAME} PARENT_SCOPE)


find_package(Qt5Core)
find_package(Qt5Widgets)
find_package(Qt5Network)


add_library(${MODULE_NAME}
    QtPrivateDeclar.cpp QtPrivateDeclar.h
)

target_link_libraries(${MODULE_NAME} Qt5::Core Qt5::Network)


# target_include_directories(${MODULE_NAME} PRIVATE
#     ${QtPrivateDeclar_INCLUDE_DIRS}
# )
# target_link_libraries(${MODULE_NAME} Qt5::Core Qt5::Network
#     ${QtPrivateDeclar_LIBRARIES}
# )
