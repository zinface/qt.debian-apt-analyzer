cmake_minimum_required(VERSION 3.0.0)

set(BUILD_NAME      "BUILD")
set(BUILD_VERSION   "")
set(BUILD_FULL_NAME "${BUILD_NAME} Feature")
set(BUILD_PROGRAMME "C")
set(BUILD_FEATURES  "")
set(BUILD_MESSAGE   "准备构建目标")

# 自定义打印内容前缀
function(build_message)
    message("[${BUILD_FULL_NAME}] ${BUILD_MESSAGE}: " ${ARGN}) 
endfunction(build_message)

# 定义方法，加载特性约定配置(实际为子构建约定配置)
function(build_feature_init _NAME)

    # 过滤标志：给入的参数数量为 2 时
    if(${ARGC} EQUAL 2)
        # 分割前提条件：按参数的 “/” 分割前后部分，为找出 "/" 字符的坐标
        string(FIND ${ARGN} "/" Separate)
        # 检查标志："/" 字符坐标值超过 0 ，将进行拆分左右，并进行设置到变量
        if(${Separate} GREATER 0)
            string(SUBSTRING ${ARGN} 0 ${Separate} sleft)
            math(EXPR rindex "${Separate}+1")   # 将原始值偏移 +1
            string(SUBSTRING ${ARGN} ${rindex} -1 sright)
            # 递归调用，参数数量为 3 个
            build_feature_init(${_NAME} ${sleft} ${sright})
        endif(${Separate} GREATER 0)
        return()
    endif()

    # 过滤标志：给入的参数数量为大于 2 时
    if(${ARGC} GREATER 2)
        # set(slen 0)
        # set(fsize 0)

        # 读取文件到变量
        file(READ ${ARGV1}/${ARGV2} build_feats_string)

        # 获取变量值长度到变量, 语法：
        # string(LENGTH <string> <out-var>)
        string(LENGTH "${build_feats_string}" slen)

        # 跳过条件：变量内容长度为 0 将跳过
        # if(${slen} EQUAL 0)
        #     return()
        # endif(${slen} EQUAL 0)

        # 内容替换：将 "\n" 符 替换成 ";" 以符合 CMake LIST 判定标志，并到变量
        string(REPLACE "\n" ";" build_feats_list ${build_feats_string})
        
        # list 条件计算：LENGTH 为 计算list内容的长度，并到变量
        list(LENGTH build_feats_list eflen)

        # 遍历标志 IN LISTS：将遍历list内容，到变量
        foreach(feat IN LISTS build_feats_list)
            # 替换标志：名称中开头为空格的替换成非空
            string(REGEX REPLACE "^[ ]" "" feat  "${feat}")

            # 过滤标志：名称为空将过滤
            string(LENGTH "${feat}" slen)
            if(${slen} EQUAL 0)
                continue()
            endif(${slen} EQUAL 0)

            # 过滤标志：以 '#'开头将过滤 ，构建中有 if(IS_DIRECTORY 可不需要该过滤
            string(FIND ${feat} "#" Separate)
            if(${Separate} EQUAL 0)
                continue()
            endif(${Separate} EQUAL 0)

            # 检查标志：当前绝对目录路径下的后续路径指定的是目录将进行加载构建
            if(IS_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/${ARGV1}/${feat}")
                build_message(${feat})
                add_subdirectory(${ARGV1}/${feat})

                # include
                get_source_file_property(F_INC ${_NAME} INCLUDE_DIRECTORIES)
                if(F_INC STREQUAL "NOTFOUND")
                    set_source_files_properties(${_NAME} PROPERTIES INCLUDE_DIRECTORIES ${ARGV1}/${feat})
                else()
                    set_source_files_properties(${_NAME} PROPERTIES INCLUDE_DIRECTORIES "${F_INC};${ARGV1}/${feat}")
                endif(F_INC STREQUAL "NOTFOUND")

                # libraries
                get_target_property(F_TMP ${_NAME} SOURCES)
                if(F_TMP STREQUAL "F_TMP-NOTFOUND")
                    set_target_properties(${_NAME} PROPERTIES SOURCES "${feat}")
                else()
                    set_target_properties(${_NAME} PROPERTIES SOURCES "${F_TMP};${feat}")
                endif(F_TMP STREQUAL "F_TMP-NOTFOUND")
            endif()
        endforeach(feat IN LISTS BUILD_FEATURES)
    endif(${ARGC} GREATER 2)
endfunction(build_feature_init _NAME)

# 使用初始化特性约定加载，(实际为普通文件)
# build_feature_init(./tutorials)


function(build_feature)
    set(BUILD_FULL_NAME ${ARGV0})
    set(BUILD_MESSAGE ${ARGV1})
    if(${ARGC} EQUAL 4)
        build_feature_init(${ARGV2} ${ARGV3})
    elseif(${ARGC} EQUAL 5)
        build_feature_init(${ARGV3} ${ARGV4})
    endif()
endfunction(build_feature)