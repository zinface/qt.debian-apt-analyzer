
cmake_minimum_required(VERSION 3.5.1)

project(apt-source-view LANGUAGES CXX VERSION 0.0.1)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt5 COMPONENTS Core Widgets Network)

# 头文件目录
include_directories()

# 资源文件路径
set(QRC_SOURCES "")

add_executable(${PROJECT_NAME} "main.cpp"
    "mainwindow.cpp" "mainwindow.h" 
    ${QRC_SOURCES}
)
find_package(BaseBuild PATHS ${CMAKE_SOURCE_DIR})
# project(${BASE_NAME} LANGUAGES ${BASE_PROGRAMME} VERSION ${BASE_VERSION})
#
base_feature_init(FEATURES ./build-template)
target_include_directories(${PROJECT_NAME} PUBLIC
    ${FEATURES_INCLUDE_DIRS}
) 
target_link_libraries(${PROJECT_NAME} Qt5::Core Qt5::Widgets Qt5::Network
    ${FEATURES_LIBRARIES}
)
