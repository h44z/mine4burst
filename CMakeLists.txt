cmake_minimum_required(VERSION 3.7)
project(mine4burst)

set(CMAKE_C_STANDARD 11)

#Add dependencies
add_subdirectory(external/tinycthread)
add_subdirectory(external/cJSON)

#Set your directories.  The dot representes the root application folder.
set(APP_SRC ./src)
set(APP_INC ./include)

#Include the directories and now your cpp files will recognize your headers
include_directories(${APP_SRC})
include_directories(${APP_INC})

set(SOURCE_FILES ${APP_SRC}/main.c ${APP_SRC}/config.c ${APP_SRC}/helper.c ${APP_SRC}/plot.c)

add_executable(mine4burst ${SOURCE_FILES})
target_link_libraries(mine4burst cjson tinycthread)

add_custom_command(TARGET mine4burst POST_BUILD        # Adds a post-build event to mine4burst
        COMMAND ${CMAKE_COMMAND} -E copy_if_different  # which executes "cmake - E copy_if_different..."
        "${PROJECT_SOURCE_DIR}/cmake-build-$<CONFIGURATION>/external/cJSON/libcjson.dll"      # <--this is in-file
        $<TARGET_FILE_DIR:mine4burst>)                 # <--this is out-file path

add_custom_command(TARGET mine4burst POST_BUILD        # Adds a post-build event to mine4burst
        COMMAND ${CMAKE_COMMAND} -E copy_if_different  # which executes "cmake - E copy_if_different..."
        "${PROJECT_SOURCE_DIR}/cmake-build-$<CONFIGURATION>/external/tinycthread/libtinycthread.a"      # <--this is in-file
        $<TARGET_FILE_DIR:mine4burst>)                 # <--this is out-file path