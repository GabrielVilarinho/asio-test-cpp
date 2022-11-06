#adding asio lib

add_library(
    asio
    INTERFACE
    asio-1.24.0/include/asio.hpp
)

#target_compile_options(asio INTERFACE ASIO_STANDALONE)

target_include_directories(asio INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/asio-1.24.0/include)

# Rock the Box

#add_library(
#    asio
#    INTERFACE
#)
#
#target_compile_options(asio INTERFACE)
#target_include_directories(asio INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/asio-1.24.0/include)
#target_link_libraries(asio INTERFACE pthread)