cmake_minimum_required(VERSION 3.10)
project(arkanoid)

set(FORGE_DIR vendor/game-forge)

add_subdirectory(vendor/game-forge)

set(CMAKE_C_STANDARD 99)
set(CMAKE_EXPORT_COMPILE_COMMANDS 1)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(TARGET_ARCHITECTURE "x64")

set(GAME_SOURCES
    ${PROJECT_SOURCE_DIR}/src/game.c
    ${PROJECT_SOURCE_DIR}/src/main.c
)

add_executable(${PROJECT_NAME}
    ${GAME_SOURCES}
)

target_include_directories(${PROJECT_NAME} PRIVATE
    ${PROJECT_SOURCE_DIR}/src
    ${FORGE_DIR}/src
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    forge
)

add_custom_target(run
    COMMAND cd ${CMAKE_RUNTIME_OUTPUT_DIRECTORY} && ./${PROJECT_NAME} ${ARGS}
)

# Asset files
set(ASSETS_SRC "${CMAKE_SOURCE_DIR}/resources")
set(ASSETS_DST "$<TARGET_FILE_DIR:${PROJECT_NAME}>/resources")

if(CMAKE_SYSTEM_NAME MATCHES "Windows")
    set(ASSETS_CMD copy_directory)
    set(ASSETS_MSG "Copy assets")
elseif(CMAKE_SYSTEM_NAME MATCHES "Linux")
    set(ASSETS_CMD create_symlink)
    set(ASSETS_MSG "Link assets")
endif()

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E echo "${ASSETS_MSG}: ${ASSETS_SRC} to ${ASSETS_DST}"
    COMMAND ${CMAKE_COMMAND} -E ${ASSETS_CMD} "${ASSETS_SRC}" "${ASSETS_DST}"
)
