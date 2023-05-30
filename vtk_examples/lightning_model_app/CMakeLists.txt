
cmake_minimum_required(VERSION 3.12 FATAL_ERROR)

if(POLICY CMP0020)
  cmake_policy(SET CMP0020 NEW)
  cmake_policy(SET CMP0071 NEW)
endif()

PROJECT(lightning_model_app)

# Tu nastavit verziu cestu k VTK
set(VTK_DIR "C:/Program Files/VTK/lib/cmake/vtk-9.2")

# manually setting qt6 - version and compiler path
set(QT_VERSION_MAJOR 6)
set(QT_VERSION 6.4.0)
set(QT_COMPILER "msvc2019_64")

if(APPLE)
    set(Qt${QT_VERSION_MAJOR}_DIR "/Users/$ENV{USER}/Qt/6.4.2/macos/lib/cmake/Qt${QT_VERSION_MAJOR}")
elseif(WIN32)
    set(Qt${QT_VERSION_MAJOR}_DIR "C:/Qt/${QT_VERSION}/${QT_COMPILER}/lib/cmake/Qt${QT_VERSION_MAJOR}")
    set(Qt${QT_VERSION_MAJOR}WidgetsTools_DIR "C:/Qt/${QT_VERSION}/${QT_COMPILER}/lib/cmake/Qt${QT_VERSION_MAJOR}WidgetsTools")
    set(Qt${QT_VERSION_MAJOR}CoreTools_DIR "C:/Qt/${QT_VERSION}/${QT_COMPILER}/lib/cmake/Qt${QT_VERSION_MAJOR}CoreTools")
    set(Qt${QT_VERSION_MAJOR}GuiTools_DIR "C:/Qt/${QT_VERSION}/${QT_COMPILER}/lib/cmake/Qt${QT_VERSION_MAJOR}GuiTools")
endif()

find_package(VTK COMPONENTS 
  CommonColor
  CommonCore
  FiltersSources
  InteractionStyle
  RenderingContextOpenGL2
  RenderingCore
  RenderingFreeType
  RenderingGL2PSOpenGL2
  RenderingOpenGL2
  GUISupportQt
  RenderingQt
)

if(NOT VTK_FOUND)
  message(FATAL_ERROR "${PROJECT_NAME}: Unable to find the VTK build folder.")
endif()

if(NOT(TARGET VTK::GUISupportQt))
  message(FATAL_ERROR "${PROJECT_NAME}: VTK not built with Qt support.")
endif()

if(NOT DEFINED VTK_QT_VERSION)
  set(VTK_QT_VERSION 5)
endif()

set(qt_components Core Gui Widgets)
if(${VTK_QT_VERSION} VERSION_GREATER_EQUAL 6)
  list(APPEND qt_components OpenGLWidgets)
endif()
list(SORT qt_components)
# We have ui files, so this will also bring in the macro:
#   qt5_wrap_ui or qt_wrap_ui from Widgets.
find_package(Qt${VTK_QT_VERSION} QUIET
  REQUIRED COMPONENTS ${qt_components}
)

foreach(_qt_comp IN LISTS qt_components)
  list(APPEND qt_modules "Qt${VTK_QT_VERSION}::${_qt_comp}")
endforeach()

message (STATUS "VTK_VERSION: ${VTK_VERSION}, Qt Version: ${Qt${VTK_QT_VERSION}Widgets_VERSION}")

# Instruct CMake to run moc and uic automatically when needed.
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)

include_directories(${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR})

file(GLOB UI_FILES src/*.ui)
file(GLOB QT_WRAP src/*.h)
file(GLOB CXX_FILES src/*.cxx)

# For VTK versions greater than or equal to 8.90.0:
#  CMAKE_AUTOUIC is ON so we handle uic automatically for Qt targets.
#  CMAKE_AUTOMOC is ON so we handle moc automatically for Qt targets.

# Prevent a "command line is too long" failure in Windows.
set(CMAKE_NINJA_FORCE_RESPONSE_FILE "ON" CACHE BOOL "Force Ninja to use response files.")
# CMAKE_AUTOMOC in ON so the MOC headers will be automatically wrapped.
add_executable(${PROJECT_NAME} MACOSX_BUNDLE
  ${CXX_FILES} ${UISrcs} ${QT_WRAP}
)
if (Qt${VTK_QT_VERSION}Widgets_VERSION VERSION_LESS "5.11.0")
  qt5_use_modules(${PROJECT_NAME} ${qt_components})
else()
  target_link_libraries(${PROJECT_NAME} ${qt_modules})
endif()
target_link_libraries(${PROJECT_NAME} ${VTK_LIBRARIES})
# vtk_module_autoinit is needed
vtk_module_autoinit(
  TARGETS ${PROJECT_NAME}
  MODULES ${VTK_LIBRARIES}
)

if(APPLE)
    install(TARGETS ${PROJECT_NAME}
        RUNTIME DESTINATION "${PROJECT_BINARY_DIR}"
        BUNDLE DESTINATION "${PROJECT_BINARY_DIR}"
        LIBRARY DESTINATION "${PROJECT_BINARY_DIR}"
    )
elseif(WIN32)
    add_custom_command(TARGET ${PROJECT_NAME}
                POST_BUILD COMMAND "C:/Qt/${QT_VERSION}/${QT_COMPILER}/bin/windeployqt.exe" "${PROJECT_BINARY_DIR}"
                COMMENT "windeployqt executed...")
endif()
