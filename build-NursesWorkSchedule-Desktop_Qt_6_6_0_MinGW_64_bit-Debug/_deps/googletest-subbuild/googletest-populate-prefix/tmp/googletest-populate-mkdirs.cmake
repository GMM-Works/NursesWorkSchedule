# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "G:/Nurses/NursesWorkSchedule/build-NursesWorkSchedule-Desktop_Qt_6_6_0_MinGW_64_bit-Debug/_deps/googletest-src"
  "G:/Nurses/NursesWorkSchedule/build-NursesWorkSchedule-Desktop_Qt_6_6_0_MinGW_64_bit-Debug/_deps/googletest-build"
  "G:/Nurses/NursesWorkSchedule/build-NursesWorkSchedule-Desktop_Qt_6_6_0_MinGW_64_bit-Debug/_deps/googletest-subbuild/googletest-populate-prefix"
  "G:/Nurses/NursesWorkSchedule/build-NursesWorkSchedule-Desktop_Qt_6_6_0_MinGW_64_bit-Debug/_deps/googletest-subbuild/googletest-populate-prefix/tmp"
  "G:/Nurses/NursesWorkSchedule/build-NursesWorkSchedule-Desktop_Qt_6_6_0_MinGW_64_bit-Debug/_deps/googletest-subbuild/googletest-populate-prefix/src/googletest-populate-stamp"
  "G:/Nurses/NursesWorkSchedule/build-NursesWorkSchedule-Desktop_Qt_6_6_0_MinGW_64_bit-Debug/_deps/googletest-subbuild/googletest-populate-prefix/src"
  "G:/Nurses/NursesWorkSchedule/build-NursesWorkSchedule-Desktop_Qt_6_6_0_MinGW_64_bit-Debug/_deps/googletest-subbuild/googletest-populate-prefix/src/googletest-populate-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "G:/Nurses/NursesWorkSchedule/build-NursesWorkSchedule-Desktop_Qt_6_6_0_MinGW_64_bit-Debug/_deps/googletest-subbuild/googletest-populate-prefix/src/googletest-populate-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "G:/Nurses/NursesWorkSchedule/build-NursesWorkSchedule-Desktop_Qt_6_6_0_MinGW_64_bit-Debug/_deps/googletest-subbuild/googletest-populate-prefix/src/googletest-populate-stamp${cfgdir}") # cfgdir has leading slash
endif()
