# aux_source_directory(. DIR_SRCS)
set(CMAKE_INCLUDE_CURRENT_DIR ON)  #
set(CMAKE_CXX_STANDARD 11)         # 指定C++标准

# Q_OBJECT宏展开、资源文件、界面文件
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# 搜集源代码
file(GLOB_RECURSE SOURCES "*.cpp")
file(GLOB_RECURSE HEADERS "*.h")
file(GLOB_RECURSE FORMS "*.ui")
file(GLOB_RECURSE RESOURCES "*.qrc")

# 使用第三方库需要
# find_package(PkgConfig REQUIRED)

# 和install有关系
# set(CMAKE_INSTALL_PREFIX /usr)

# 添加子目录
add_subdirectory (api)
add_subdirectory (SQL)
add_subdirectory(windows)
add_subdirectory(event)

# 对于QT项目来说，ui文件和qrc文件也是需要编译的
add_executable (${TARGET_NAME} ${RESOURCES} main.cpp mainwindow.cpp systemtrayicon.cpp picker.cpp)# ${FORMS})

# 导入Qt包，需要放在add_executable之后
set(QT Core Gui Widgets Network DBus Sql X11Extras)
find_package(Qt5 REQUIRED ${QT})
qt5_use_modules(${TARGET_NAME} ${QT})

#link_directories(${LINK_DIR})

link_directories(/usr/lib/x86_64-linux-gnu)

target_link_libraries(
    ${TARGET_NAME}
    event api SQL windows)

# 复制桌面入口文件
# set(CMAKE_INSTALL_PREFIX /usr)
install(FILES ../deb/words-picker/usr/share/applications/words-picker.desktop DESTINATION /usr/share/applications/)

# 复制words-picker目录
set(DES_DIR ../deb/words-picker/opt/words-picker/)
MESSAGE( STATUS ${DES_DIR})
install(DIRECTORY ${DES_DIR} DESTINATION /opt/words-picker)
install(TARGETS words-picker DESTINATION /opt/words-picker/)
