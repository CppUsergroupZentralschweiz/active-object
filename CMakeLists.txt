cmake_minimum_required(VERSION 3.25)

project(ActiveObject)

add_library(active-object )
target_sources(active-object PRIVATE src/ao/scheduler.cc)
target_compile_options(active-object PUBLIC
    "-std=c++20"
    "-Wall"
    "-Wextra"
    "-Werror"
)
target_include_directories(active-object INTERFACE src)
# target_compile_features(active-object INTERFACE cxx_std_20)

add_executable(example)
target_sources(example
    PRIVATE
        example/main.cc
        example/ascii.cc
        example/plain_counter.cc
        example/ao_counter.cc
)
target_link_libraries(example PRIVATE active-object)
