cmake_minimum_required(VERSION 3.5)

project(NursesWorkSchedule LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(NursesWorkSchedule main.cpp)

include(GNUInstallDirs)
install(TARGETS NursesWorkSchedule
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
