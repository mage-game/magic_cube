STRING( REGEX REPLACE ".*/(.*)" "\\1" CURRENT_FOLDER ${CMAKE_CURRENT_SOURCE_DIR} )
set(TARGET ${CURRENT_FOLDER})

file(GLOB_RECURSE MASTER_SERVER_SRC "*.cpp" "*.h")

add_executable(${TARGET} ${MASTER_SERVER_SRC})
target_include_directories(${TARGET}
        PUBLIC
        ${PROJECT_SOURCE_DIR}/code/apis
        PRIVATE
        ${PROJECT_SOURCE_DIR}/code/framework
        )
target_link_libraries(${TARGET}
        libgo
        ${FOLLY_LIBRARIES}
        framework
        )
