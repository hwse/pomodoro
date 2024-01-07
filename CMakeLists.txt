cmake_minimum_required(VERSION 3.20)

project(pomodoro LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

include(cmake/CPM.cmake)

find_package(wxWidgets)
if(wxWidgets_FOUND)
    include(${wxWidgets_USE_FILE})
    message(STATUS "Using wxWidgets libaries: ${wxWidgets_LIBRARIES}")
    set(WX_LINK_ARG ${wxWidgets_LIBRARIES})
else()
    CPMAddPackage(
            NAME wxWidgets
            VERSION 3.2.2.1
            GITHUB_REPOSITORY "wxWidgets/wxWidgets"
            EXCLUDE_FROM_ALL "ON"
            OPTIONS "wxBUILD_SHARED OFF"
    )
    set(WX_LINK_ARG wxcore)
endif()

add_executable(pomodoro WIN32
        src/main.cpp
        src/PomodoroFrame.cpp
        src/PomodoroState.cpp)
target_include_directories(pomodoro PRIVATE include)
target_link_libraries(pomodoro PRIVATE ${WX_LINK_ARG})
if(MSVC)
    target_compile_options(pomodoro PRIVATE /W4)
else()
    target_compile_options(pomodoro PRIVATE -Wall -Wextra -Wpedantic)
endif()
install(TARGETS pomodoro RUNTIME DESTINATION bin)


set(CPACK_NSIS_DISPLAY_NAME Pomodoro)
set(CPACK_NSIS_PACKAGE_NAME Pomodoro)
set(CPACK_PACKAGE_INSTALL_DIRECTORY Pomodoro)
set(CPACK_PACKAGE_EXECUTABLES pomodoro Pomodoro)
include(CPack)