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
    set(CPM_WX_VERSION "3.2.4")
    message(STATUS "Fetching wxWidgets ${CPM_WX_VERSION} with CPM since no install was found")
    CPMAddPackage(
            NAME wxWidgets
            VERSION ${CPM_WX_VERSION}
            URL https://github.com/wxWidgets/wxWidgets/releases/download/v${CPM_WX_VERSION}/wxWidgets-${CPM_WX_VERSION}.zip
            URL_HASH SHA256=051aa9d5a1b39fec940efd963b702a6082d5eb57935245edcbab21dfe19be209
            EXCLUDE_FROM_ALL "ON"
            OPTIONS "wxBUILD_SHARED OFF"
    )
    set(WX_LINK_ARG wxcore)
endif()

add_executable(pomodoro WIN32
        include/PomodoroConfig.hpp
        include/PomodoroFrame.hpp
        include/PomodoroState.hpp
        src/main.cpp
        src/PomodoroConfig.cpp
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