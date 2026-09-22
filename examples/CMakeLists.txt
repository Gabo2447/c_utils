set(TEST_UTILITIES_NAME c_utils-examples)

set(SOURCES
        linked_list_test.c
)

add_executable(${TEST_UTILITIES_NAME} ${SOURCES})

target_link_libraries(${TEST_UTILITIES_NAME} PRIVATE ${PROJECT_NAME})
target_include_directories(${TEST_UTILITIES_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

add_test(NAME Linked_List_Tests COMMAND ${TEST_UTILITIES_NAME})