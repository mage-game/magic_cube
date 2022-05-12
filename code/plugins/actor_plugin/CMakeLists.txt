set(APP_NAME framework)

file(GLOB_RECURSE FRAMEWORK_SRC "*.cpp" "*.h")

add_library(${APP_NAME} ${FRAMEWORK_SRC})
target_include_directories(${APP_NAME}
        PUBLIC
        ${PROJECT_SOURCE_DIR}/code/include
        PRIVATE
        ${PROJECT_SOURCE_DIR}/code/framework
        )
target_link_libraries(${APP_NAME}
        ${FOLLY_LIBRARIES}
        )