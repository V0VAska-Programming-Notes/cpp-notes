cmake_minimum_required(VERSION 3.21)

project(VitualDestructors)

add_executable(virtual-destructors)

target_sources(virtual-destructors
    PRIVATE
        main.cxx
)

target_compile_features(virtual-destructors
    PRIVATE
        cxx_std_17
)

target_compile_definitions(virtual-destructors
    PUBLIC
        PRESET_NAME="${PRESET_NAME}"
        BUILD_TYPE="${CMAKE_BUILD_TYPE}"
)
