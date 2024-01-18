cmake_minimum_required(VERSION 3.5)

project(NursesWorkSchedule LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#option(CodeCoverage "CodeCoverage" OFF)
#set(CMAKE_CXX_FLAGS "-std=c++11 -Wno-deprecated-register ${CMAKE_CXX_FLAGS}")
#set(CMAKE_CXX_FLAGS_DEBUG "-std=c++11 -Wno-deprecated-register -O0 -g -fprofile-arcs -ftest-coverage ${CMAKE_CXX_FLAGS_DEBUG}")
#set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR})

add_executable(
    NursesWorkSchedule
    include/prompt/parser.h
    include/prompt/procedure.h
    include/prompt/procedureconsole.h
    include/prompt/procedureconsole.cpp
    include/prompt/storage.h
    include/prompt/storage.cpp
    include/prompt/wordsparser.h
    include/prompt/wordsparser.cpp
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
    staff.h
    staff.cpp
    nursesinterface.h
    scheduleprocedure.h
    scheduleprocedure.cpp
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
    csvstaffparser.h
    csvstaffparser.cpp
    staff.h
    staff.cpp
    nursesinterface.h
    currentDateTest.cpp
    fileWriterFileReaderTest.cpp
    fileReaderTest.cpp
    holidayParserTest.cpp
    staffParserTest.cpp
)

include(GNUInstallDirs)
install(TARGETS NursesWorkSchedule
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG  "main"

)

#For Windows: Prevent overriding the parent project's compiler/linker settings
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
gtest_discover_tests(NursesWorkScheduleTest PRE_TEST)
#if (CMAKE_BUILD_TYPE MATCHES Debug)
#if (CodeCoverage MATCHES ON)
#include(CodeCoverage)
#setup_target_for_coverage(${PROJECT_NAME}_coverage poptests coverage)
#setup_target_for_coverage_cobertura(${PROJECT_NAME}_cobertura poptests coverage --gtest_output=xml:coverage.junit.xml)
#endif()
#endif()
