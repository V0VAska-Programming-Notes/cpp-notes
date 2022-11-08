cmake_minimum_required(VERSION 3.21)

project(RealJoke)

add_executable(real-joke)

target_sources(real-joke
    PRIVATE
        main.cxx
)

target_compile_features(real-joke
    PRIVATE
        cxx_std_17
)
