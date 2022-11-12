cmake_minimum_required(VERSION 3.21)

project(Singleton LANGUAGES CXX)

add_library(compiler_flags_lib INTERFACE)
target_compile_features(compiler_flags_lib INTERFACE cxx_std_17)

set(gcc_like_cxx "$<COMPILE_LANG_AND_ID:CXX,ARMClang,AppleClang,Clang,GNU,LCC>")
set(msvc_cxx "$<COMPILE_LANG_AND_ID:CXX,MSVC>")
target_compile_options(compiler_flags_lib
    INTERFACE
        "$<${gcc_like_cxx}:$<BUILD_INTERFACE:-Wall;-Wextra;-Wshadow;-Wformat=2;-Wunused>>"
        "$<${msvc_cxx}:$<BUILD_INTERFACE:-W3>>"
)

add_executable(${PROJECT_NAME})

target_sources(${PROJECT_NAME}
    PRIVATE
        main.cxx
        simple/simple.cxx
        pointerless/pointerless.cxx
        classic/classic.cxx
)

target_include_directories(${PROJECT_NAME}
    PRIVATE
        simple
        pointerless
        classic
)

target_compile_definitions(${PROJECT_NAME}
    PUBLIC
        PRESET_NAME="${PRESET_NAME}"
        BUILD_TYPE="${CMAKE_BUILD_TYPE}"
)

target_link_libraries(${PROJECT_NAME}
	PRIVATE
		compiler_flags_lib
)
