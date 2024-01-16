cmake_minimum_required(VERSION 3.5)

project(NursesWorkSchedule LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

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
    ScheduleCreatorTest.cpp
)

# set(staff_csv ${CMAKE_CURRENT_SOURCE_DIR}/staff.csv)
# set(nurses_csv ${CMAKE_CURRENT_SOURCE_DIR}/nurses.csv)
# set(holidays_csv ${CMAKE_CURRENT_SOURCE_DIR}/holidays.csv)
# set(output_csv ${CMAKE_CURRENT_BINARY_DIR}/workScheduleTest.csv)

# add_custom_command(
#     OUTPUT  ${output_csv}
#     COMMAND NursesWorkScheduleTest
#     DEPENDS ${staff_csv} ${nurses_csv} ${holidays_csv}
# )

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
