cmake_minimum_required(VERSION 3.13.4)

include(cmake/SparkWithGit.cmake)

project(debian-apt-analyzer LANGUAGES CXX VERSION 0.0.9)

spark_initialize_modules()

# 构建一个可执行目标，由一系列资源组成
spark_add_executable_path(debian-apt-analyzer
    src
    src/widgets
    res/res.qrc
)
target_link_qt(debian-apt-analyzer)

# 引用了一系列资源：
spark_framework_include_with_git(debian-apt-analyzer
    https://gitee.com/spark-framework-libs/spark-framework-features
    FEATURES qd defer eaters analyzer version screenutil qrcutil
)
spark_framework_include_with_git(debian-apt-analyzer
    https://gitee.com/spark-framework-libs/debian-analyzer-libs
    FEATURES repo
)
spark_framework_include_with_git(debian-apt-analyzer
    https://gitee.com/spark-framework-libs/simple-frameless-libs
    FEATURES frameless)

# 使用了 zlib 进行 gz 解析
spark_find_library(zlib zlib)
target_link_zlib(debian-apt-analyzer)

# include(cmake/SparkDesktopMacros.cmake)
# 内容默认应用名称: Name= 应与项目名称相同
spark_desktop_macros(
    # 应用名称: Name=
    "Debian Apt Repo Analyzer"
    # 应用名称: Name[zh_CN]=
    "Debian 软件仓库分析工具"
    # 应用说明: Comment=
    "适用于 Debian 软件仓库分析"
    # 应用类型: Type=
    "Application"
    # 执行程序: Exec=
    "/opt/apps/com.gitee.zinface.debian-apt-analyzer/bin/debian-apt-analyzer"
    # 图标路径: Icon=
    "/opt/apps/com.gitee.zinface.debian-apt-analyzer/icon/diversity-2019.png"
    # 应用分类: Categories=
    "Utility"
    # MIME类型: MimeType=
    ""
)

# 安装快捷方式
spark_install_file(/usr/share/applications 
    ${SPARK_DESKTOP_FILE})
# 安装图标
spark_install_file(/opt/apps/com.gitee.zinface.debian-apt-analyzer/icon 
    res/diversity-2019.png)
# 安装目标
spark_install_target(/opt/apps/com.gitee.zinface.debian-apt-analyzer/bin 
    debian-apt-analyzer)

add_package_descript(cmake/spark-deb-package.descript)
