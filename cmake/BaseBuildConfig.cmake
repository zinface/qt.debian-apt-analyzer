cmake_minimum_required(VERSION 3.0.0)

find_package(BuildFeature PATHS ${CMAKE_SOURCE_DIR})

set(BASE_NAME          "Base")
set(BASE_VERSION_MAJOR 0)
set(BASE_VERSION_MINOR 1)
set(BASE_VERSION_PATCH 0)
set(BASE_VERSION       "${BASE_VERSION_MAJOR}.${BASE_VERSION_MINOR}.${BASE_VERSION_PATCH}")
set(BASE_FULL_NAME     "${BASE_NAME} Project")
set(BASE_PROGRAMME     "CXX")
set(BASE_FEATURES      "")

# 用于打印 ascii 文字 logo 
function(base_load_hello)
    file(READ ${ARGV0} _OUT)
    message("${_OUT}")
endfunction(base_load_hello)

# 用于定制构建器 feature 消息
function(base_feature_init _NAME)
    add_custom_target(${_NAME} SOURCES "")
    set_target_properties(${_NAME} PROPERTIES INCLUDE_DIRECTORIES "")
    build_feature("${BASE_FULL_NAME}" "准备构建特性" ${_NAME} ${ARGN})
    get_source_file_property(_${_NAME}_INCLUDE_DIRS ${_NAME} INCLUDE_DIRECTORIES)
    get_target_property(_${_NAME}_LIBRARIES ${_NAME} SOURCES)
    set(${_NAME}_INCLUDE_DIRS ${_${_NAME}_INCLUDE_DIRS} PARENT_SCOPE)
    set(${_NAME}_LIBRARIES ${_${_NAME}_LIBRARIES} PARENT_SCOPE)
endfunction(base_feature_init _NAME)

# 用于定制构建器 test 消息
function(base_test_init _NAME)
    add_custom_target(${_NAME} SOURCES "")
    set_target_properties(${_NAME} PROPERTIES INCLUDE_DIRECTORIES "")
    build_feature("${BASE_FULL_NAME}" "准备构建特性" ${_NAME} ${ARGN})
    get_source_file_property(_${_NAME}_INCLUDE_DIRS ${_NAME} INCLUDE_DIRECTORIES)
    get_target_property(_${_NAME}_LIBRARIES ${_NAME} SOURCES)
    set(${_NAME}_INCLUDE_DIRS ${_${_NAME}_INCLUDE_DIRS} PARENT_SCOPE)
    set(${_NAME}_LIBRARIES ${_${_NAME}_LIBRARIES} PARENT_SCOPE)
endfunction(base_test_init _NAME)


# find_package 命令还可以用来加载 cmake 的功能模块
# 并不是所有的库都直接支持 cmake 查找的，但大部分都支持了 pkg-config 这个标准，
# 因此 cmake 提供了间接加载库的模块：FindPkgConfig， 下面这行命令表示加载 FindPkgConfig 模块，
# 这个 cmake 模块提供了额外的基于 “pkg-config” 加载库的能力
# 执行下面的命令后后会设置如下变量，不过一般用不到：
# PKG_CONFIG_FOUND            pkg-config 可执行文件是否找到了
# PKG_CONFIG_EXECUTABLE       pkg-config 可执行文件的路径
# PKG_CONFIG_VERSION_STRING   pkg-config 的版本信息
find_package(PkgConfig REQUIRED)