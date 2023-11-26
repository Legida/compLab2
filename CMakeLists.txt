cmake_minimum_required(VERSION 3.16)

project(compLab2 VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.2 COMPONENTS Quick REQUIRED)
FIND_PACKAGE(OpenMP)

IF(OPENMP_FOUND)
    SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
ENDIF()

qt_add_executable(appcompLab2
    main.cpp
    FuncGraphsProvider.cpp
    FuncGraphsProvider.h
    ProvidersHandler.cpp
    ProvidersHandler.h
    OperatorHelper.h
    ButtonAdapter.h
)

qt_add_qml_module(appcompLab2
    URI compLab2
    VERSION 1.0
    QML_FILES
    qml/main.qml
    qml/MImage.qml
)

set_target_properties(appcompLab2 PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_compile_definitions(appcompLab2
    PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)
target_link_libraries(appcompLab2
    PRIVATE Qt6::Quick)
