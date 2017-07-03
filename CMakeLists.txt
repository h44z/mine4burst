cmake_minimum_required(VERSION 3.7)
project(mine4burst)

set(CMAKE_C_STANDARD 99)

#Set your directories.  The dot representes the root application folder.
set(APP_SRC ./src)
set(APP_INC ./include)
set(CJSON_SRC ./external/cJSON)

#Include the directories and now your cpp files will recognize your headers
include_directories(${APP_SRC})
include_directories(${APP_INC})
include_directories(${CJSON_SRC})

set(SOURCE_FILES ${APP_SRC}/main.c ${APP_SRC}/config.c ${APP_SRC}/helper.c ${APP_SRC}/plot.c ${CJSON_SRC}/cJSON_Utils.c ${CJSON_SRC}/cJSON.c)

add_executable(mine4burst ${SOURCE_FILES})