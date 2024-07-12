# build.cmake
spark_add_executable_path(apt-repo-analyzer
    ${CMAKE_CURRENT_LIST_DIR}/src
    ${CMAKE_CURRENT_LIST_DIR}/src/widgets
    ${CMAKE_CURRENT_LIST_DIR}/res/res.qrc
)
target_link_qt(apt-repo-analyzer)
spark_framework_include_with_git(apt-repo-analyzer
    https://gitee.com/spark-framework-libs/spark-framework-features
    FEATURES qd defer version screenutil qrcutil
)
spark_framework_include_with_git(apt-repo-analyzer
    https://gitee.com/spark-framework-libs/debian-analyzer-libs
    FEATURES repo
)

spark_framework_include_with_git(apt-repo-analyzer
    https://gitee.com/spark-framework-libs/simple-frameless-libs
    FEATURES frameless)

spark_find_library(zlib zlib)
target_link_zlib(apt-repo-analyzer)
