set(TEST_UTILITIES_NAME c_utils-examples)

file(GLOB TEST_SOURCES "*_test.c")

foreach(SOURCE_FILE ${TEST_SOURCES})
    get_filename_component(TEST_NAME ${SOURCE_FILE} NAME_WE)

    add_executable(${TEST_NAME} ${SOURCE_FILE})
    target_link_libraries(${TEST_NAME} PRIVATE c_utils)
    add_test(NAME ${TEST_NAME} COMMAND ${TEST_NAME})
endforeach()