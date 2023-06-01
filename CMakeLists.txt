cmake_minimum_required(VERSION 3.20)

project(pomodoro LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

include(cmake/CPM.cmake)

CPMAddPackage(
    NAME wxWidgets
    VERSION 3.2.2.1
    GITHUB_REPOSITORY "wxWidgets/wxWidgets"
    OPTIONS "wxBUILD_SHARED OFF"
)

add_executable(pomodoro WIN32
        src/main.cpp
        src/PomodoroFrame.cpp
        src/PomodoroState.cpp)
target_include_directories(pomodoro PRIVATE include)
target_link_libraries(pomodoro PRIVATE wxcore)
