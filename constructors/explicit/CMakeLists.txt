cmake_minimum_required(VERSION 3.21)

project(ExplicitContructors)

add_executable(${PROJECT_NAME})

target_sources(${PROJECT_NAME}
    PRIVATE
        main.cxx
)

target_compile_features(${PROJECT_NAME}
    PRIVATE
        cxx_std_17
)

target_compile_definitions(${PROJECT_NAME}
    PUBLIC
        PRESET_NAME="${PRESET_NAME}"
        BUILD_TYPE="${CMAKE_BUILD_TYPE}"
)

