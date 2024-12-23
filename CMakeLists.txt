cmake_minimum_required(VERSION 3.31.0)
cmake_policy(SET CMP0148 OLD)

project(sample-app)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)

include(C:/vcpkg-master/scripts/buildsystems/vcpkg.cmake)
find_package(Qt5Widgets)

add_executable(sample-app
    src/main.cpp
    src/mainwindow.cpp
    src/figure.cpp
    src/rectangle.cpp
    src/triangle.cpp
    src/ellipse.cpp
)

target_link_libraries(sample-app
    Qt5::Widgets
)
