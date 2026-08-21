cmake_minimum_required(VERSION 3.20)
project(BattleCreator LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(NOT SCRIPTHOOKRDR2_SDK AND DEFINED ENV{SCRIPTHOOKRDR2_SDK})
    set(SCRIPTHOOKRDR2_SDK "$ENV{SCRIPTHOOKRDR2_SDK}")
endif()

if(NOT SCRIPTHOOKRDR2_LIB_DIR AND DEFINED ENV{SCRIPTHOOKRDR2_LIB_DIR})
    set(SCRIPTHOOKRDR2_LIB_DIR "$ENV{SCRIPTHOOKRDR2_LIB_DIR}")
endif()

if(NOT SCRIPTHOOKRDR2_SDK AND EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/third_party/ScriptHookRDR2_SDK/inc/natives.h")
    set(SCRIPTHOOKRDR2_SDK "${CMAKE_CURRENT_SOURCE_DIR}/third_party/ScriptHookRDR2_SDK")
endif()

set(SCRIPTHOOKRDR2_SDK "${SCRIPTHOOKRDR2_SDK}" CACHE PATH "Path to the ScriptHookRDR2 SDK folder containing inc/natives.h")
set(SCRIPTHOOKRDR2_LIB_DIR "${SCRIPTHOOKRDR2_LIB_DIR}" CACHE PATH "Path to the folder containing ScriptHookRDR2.lib")

if(NOT SCRIPTHOOKRDR2_SDK OR NOT EXISTS "${SCRIPTHOOKRDR2_SDK}/inc/natives.h")
    message(FATAL_ERROR "Set SCRIPTHOOKRDR2_SDK to your ScriptHookRDR2 SDK folder. Expected: <sdk>/inc/natives.h")
endif()

if(NOT SCRIPTHOOKRDR2_LIB_DIR)
    set(SCRIPTHOOKRDR2_LIB_DIR "${SCRIPTHOOKRDR2_SDK}/lib")
endif()

if(NOT EXISTS "${SCRIPTHOOKRDR2_LIB_DIR}/ScriptHookRDR2.lib")
    message(FATAL_ERROR "Set SCRIPTHOOKRDR2_LIB_DIR to the folder containing ScriptHookRDR2.lib.")
endif()

add_library(BattleCreator SHARED
    src/BattleCreator.cpp
)

target_include_directories(BattleCreator PRIVATE
    "${SCRIPTHOOKRDR2_SDK}/inc"
)

target_link_directories(BattleCreator PRIVATE
    "${SCRIPTHOOKRDR2_LIB_DIR}"
)

target_link_libraries(BattleCreator PRIVATE
    ScriptHookRDR2
)

target_compile_definitions(BattleCreator PRIVATE
    WIN32_LEAN_AND_MEAN
    NOMINMAX
)

set_target_properties(BattleCreator PROPERTIES
    SUFFIX ".asi"
    PREFIX ""
)

