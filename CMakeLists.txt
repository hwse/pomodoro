cmake_minimum_required(VERSION 3.20)

project(pomodoro LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

find_package(wxWidgets CONFIG REQUIRED)

add_executable(pomodoro WIN32
        src/main.cpp
        src/PomodoroFrame.cpp
        src/PomodoroState.cpp)
target_include_directories(pomodoro PRIVATE include)
target_link_libraries(pomodoro PRIVATE wx::core)
install(TARGETS pomodoro RUNTIME DESTINATION bin)

set(CPACK_NSIS_DISPLAY_NAME Pomodoro)
set(CPACK_NSIS_PACKAGE_NAME Pomodoro)
set(CPACK_PACKAGE_INSTALL_DIRECTORY Pomodoro)
set(CPACK_PACKAGE_EXECUTABLES pomodoro Pomodoro)
include(CPack)