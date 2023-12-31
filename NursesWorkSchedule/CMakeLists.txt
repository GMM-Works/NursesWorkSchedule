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
    holiday.h
    holiday.cpp
    io.h
    mainio.h
    mainio.cpp
    shift.h
    shift.cpp
    csvnursesparser.h
    csvnursesparser.cpp
    csvholidaysparser.h
    csvholidaysparser.cpp
    filewriter.h
    csvfilewriter.h
    csvfilewriter.cpp
    schedulecreator.h
    schedulecreator.cpp
    currentdate.h
    currentdate.cpp
    csvstaffparser.h
    csvstaffparser.cpp
    staff.h staff.cpp
    main.cpp
)

add_executable(
    NursesWorkScheduleTest
    parser.h
    csvparser.h
    csvparser.cpp
    filereader.h
    csvfilereader.h
    csvfilereader.cpp
    nurse.h
    nurse.cpp
    holiday.h
    holiday.cpp
    io.h
    mainio.h
    mainio.cpp
    shift.h
    shift.cpp
    csvnursesparser.h
    csvnursesparser.cpp
    csvholidaysparser.h
    csvholidaysparser.cpp
    filewriter.h
    csvfilewriter.h
    csvfilewriter.cpp
    schedulecreator.h
    schedulecreator.cpp
    currentdate.h
    currentdate.cpp
    currentDateTest.cpp
)

include(GNUInstallDirs)
install(TARGETS NursesWorkSchedule
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)
enable_testing()


target_link_libraries(
    NursesWorkScheduleTest
    GTest::gtest_main
)

target_link_libraries(
    NursesWorkScheduleTest
    GTest::gmock_main
)

include(GoogleTest)
gtest_discover_tests(NursesWorkScheduleTest)
