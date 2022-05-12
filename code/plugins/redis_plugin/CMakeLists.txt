STRING( REGEX REPLACE ".*/(.*)" "\\1" CURRENT_FOLDER ${CMAKE_CURRENT_SOURCE_DIR} )
set(TARGET ${CURRENT_FOLDER})

file(GLOB_RECURSE FRAMEWORK_SRC "*.cpp" "*.h")

add_library(${TARGET} ${FRAMEWORK_SRC})
target_include_directories(${TARGET}
        PUBLIC
        ${PROJECT_SOURCE_DIR}/code/include
        PRIVATE
        ${PROJECT_SOURCE_DIR}/code/framework
        )
target_link_libraries(${TARGET}
        ${FOLLY_LIBRARIES}
        )