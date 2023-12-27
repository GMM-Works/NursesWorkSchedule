cmake_minimum_required(VERSION 3.5)

project(NursesWorkSchedule LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(
    NursesWorkSchedule
    parser.h
    csvparser.h
    csvparser.cpp
    filereader.h
    csvfilereader.h
    csvfilereader.cpp
    nurse.h
    nurse.cpp
    io.h
    mainio.h
    mainio.cpp
    shift.h
    shift.cpp
    main.cpp
    csvnursesparser.h csvnursesparser.cpp
    filewriter.h
    csvfilewriter.h csvfilewriter.cpp
)

include(GNUInstallDirs)
install(TARGETS NursesWorkSchedule
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
