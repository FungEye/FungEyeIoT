cmake_minimum_required(VERSION 3.14)
set(projectName SEP4_IOT_TEST)
project(${projectName})

# GoogleTest requires at least C++14
set(CMAKE_CXX_STANDARD 14)

set(DOWNLOAD_EXTRACT_TIMESTAMP true)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
  DOWNLOAD_EXTRACT_TIMESTAMP false
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(googletest )

#toDO light
set(SOURCES_TEST
    testForHumTemp.cpp
    testForCO2.cpp
    FreeRTOS_defs/FreeRTOS_FFF_MocksDefinitions.cpp
    ../SEP4_IOT/SEP4_IOT/Main/srcFiles/HumidityTemperature.c
    ../SEP4_IOT/SEP4_IOT/Main/srcFiles/CO2.c
    ${SRCS}
)


# This makes the test.cpp files able to #include target libraries without errors.  
include_directories(
  FreeRTOS_defs  # Mock and FreeRTOS definitions
  ../SEP4_IOT/SEP4_IOT/Main/headerFiles
  ../SEP4_IOT/SEP4_IOT/drivers
)

# Something to 
enable_testing()

add_executable(
  ${projectName}
  ${SOURCES_TEST}
)
target_link_libraries(
  ${projectName}
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(${projectName})