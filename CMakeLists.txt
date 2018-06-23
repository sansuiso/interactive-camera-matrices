cmake_minimum_required(VERSION 3.11)
project(CameraMatrices VERSION 0.1.0 LANGUAGES CXX)

# C++ standard version handling
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Qt handling
set(CMAKE_AUTOMOC ON)
find_package(Qt5 COMPONENTS Core Gui Widgets QUIET REQUIRED)
qt5_add_resources(QRCS core-profile.qrc)

# Other dependancies
find_package(OpenGL REQUIRED)
find_package(Eigen3 3.3 QUIET REQUIRED) 

add_executable(CameraMatrices
    main.cpp
    mainwindow.cpp
    cameramatriceswidget.cpp
    cameramatrixmodel.cpp
    extrinsiccontrolwidget.cpp
    extrinsicmatrixmodel.cpp
    intrinsiccontrolwidget.cpp
    intrinsicmatrixmodel.cpp
    modelasset.cpp
    modelassetsmanager.cpp
    modelinstance.cpp
    slidingcontrolwidget.cpp
    camera.cpp
    ${QRCS}
)

target_link_libraries(CameraMatrices
    Qt5::Core
    Qt5::Gui
    Qt5::Widgets
    OpenGL::GL
    Eigen3::Eigen
)
