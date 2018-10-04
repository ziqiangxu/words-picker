cmake_minimum_required (VERSION 2.8)

# aux_source_directory(. DIR_SRCS)
# 定义变量
set(TARGET_NAME freedict)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_STANDARD 17)

# Q_OBJECT宏展开、资源文件、界面文件
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# 搜集源代码
file(GLOB_RECURSE SOURCES "*.cpp")
file(GLOB_RECURSE HEADERS "*.h")
file(GLOB_RECURSE FORMS "*.ui")
file(GLOB_RECURSE RESOURCES "*.qrc")

# 项目名字
project (${TARGET_NAME})

# 使用第三方库需要
# find_package(PkgConfig REQUIRED)

# 和install有关系
# set(CMAKE_INSTALL_PREFIX /usr)

# 添加子目录
add_subdirectory (api)
add_subdirectory (SQL)
add_subdirectory(windows)
#add_subdirectory(event)

add_executable (${TARGET_NAME} main.cpp mainwindow.cpp systemtrayicon.cpp)
# 导入Qt包，需要放在add_executable之后
set(QT Core Gui Widgets Network DBus Sql X11Extras)
find_package(Qt5 REQUIRED ${QT})
qt5_use_modules(${TARGET_NAME} ${QT})

# 链接子目录生成的静态链接库
target_link_libraries(${TARGET_NAME} api SQL windows)# event)

# set(CMAKE_INSTALL_PREFIX /usr)