cmake_minimum_required(VERSION 2.8)

project(test_task)
# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed
set(CMAKE_AUTOMOC ON)
# Create code from a list of Qt designer ui files
set(CMAKE_AUTOUIC ON)

# Find the QtWidgets library
find_package(Qt6Widgets CONFIG REQUIRED)

# Find the QtNetwork library
find_package(Qt6Network CONFIG REQUIRED)

include_directories("include")

qt6_add_resources(QRC_SOURCES resource.qrc)

# Populate a CMake variable with the sources
set(TEST_TASK_SRCS
    testtask.ui
    testtask.cpp
    dataobject.cpp
    ellipseobject.cpp
    infomodel.cpp
    lineobject.cpp
    rectobject.cpp
    triangleobject.cpp
    workerthread.cpp
    resource.qrc
    main.cpp
    )
# Tell CMake to create the executable
add_executable(${PROJECT_NAME} WIN32 ${TEST_TASK_SRCS} ${QRC_SOURCES})
# Use the Widgets module from Qt 5
target_link_libraries(${PROJECT_NAME} Qt6::Widgets Qt6::Network)
