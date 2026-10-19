cmake_minimum_required(VERSION 3.20)
project(SpectreRootARM64 VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(spectreroot
    src/main.cpp
    src/process_inspector.cpp
    src/macho_parser.cpp
    src/persistence_audit.cpp
    src/system_security.cpp
)

target_include_directories(spectreroot PRIVATE include)
target_compile_options(spectreroot PRIVATE -Wall -Wextra -Wpedantic)

if(APPLE)
    target_link_libraries(spectreroot PRIVATE "-framework Foundation")
endif()

include(CTest)
if(BUILD_TESTING)
    add_executable(test_macho_parser
        tests/test_macho_parser.cpp
        src/macho_parser.cpp
    )
    target_include_directories(test_macho_parser PRIVATE include)
    target_compile_options(test_macho_parser PRIVATE -Wall -Wextra -Wpedantic)
    add_test(NAME macho_parser COMMAND test_macho_parser)
endif()
