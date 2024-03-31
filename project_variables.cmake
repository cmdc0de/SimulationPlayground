set(PROJ_EXEC1 "sim-p")

#directories under src that will be added as subdirectories to the project
set(MY_PROJECT_SUBDIRECTORIES "sim-p;sample_library;cmdc0de-core;cmd_graphics")

set(DEFAULT_EXEC ${PROJ_EXEC1} CACHE STRING "Default executable to build")

#set(MY_PROJECT_TARGETS "${PROJ_EXEC1} ${SERVER_APP}")
set(MY_PROJECT_TARGETS "${PROJ_EXEC1}")

MESSAGE(STATUS "MY PROJECT TARGETS = ${MY_PROJECT_TARGETS}")
