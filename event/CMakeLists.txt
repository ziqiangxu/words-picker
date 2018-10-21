set(TARGET_NAME event)

aux_source_directory(. DIR_LIB_SRCS)

add_library (${TARGET_NAME} ${DIR_LIB_SRCS})

# 导入Qt包，需要放在add_executable之后
set(QT Core)
find_package(Qt5 REQUIRED ${QT})
find_package(X11)
qt5_use_modules(${TARGET_NAME} ${QT})

