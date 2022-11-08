cmake_minimum_required(VERSION 3.21)

project(machine_exceptions)

add_executable(${PROJECT_NAME})

#set(msvc_cxx "$<COMPILE_LANG_AND_ID:CXX,MSVC>")
#target_compile_options(${PROJECT_NAME}
#    PRIVATE
#        "$<${msvc_cxx}:$<BUILD_INTERFACE:-EHa>>"
#)

target_compile_features(${PROJECT_NAME}
    PRIVATE
        cxx_std_17
)

target_sources(${PROJECT_NAME}
    PRIVATE
        main.cxx
)
