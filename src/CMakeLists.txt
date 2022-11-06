add_subdirectory(lib)
add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE asio)
target_link_libraries(${PROJECT_NAME} PRIVATE lazy)
