cmake_minimum_required(VERSION 3.16)
project(CharterGAPI LANGUAGES C)

add_library(CharterGAPICore STATIC src/charter_gapi_core.c)
target_include_directories(CharterGAPICore PUBLIC include)
set_target_properties(CharterGAPICore PROPERTIES C_STANDARD 11 C_STANDARD_REQUIRED YES)

if(WIN32)
    add_library(CharterGAPI STATIC src/charter_gapi.c)
    target_include_directories(CharterGAPI PUBLIC include)
    target_link_libraries(CharterGAPI PUBLIC CharterGAPICore gdi32 user32)
endif()

include(CTest)
if(BUILD_TESTING)
    add_executable(CharterGapiCoreSmoke tests/core_smoke.c)
    target_link_libraries(CharterGapiCoreSmoke PRIVATE CharterGAPICore)
    add_test(NAME CharterGapiCoreSmoke COMMAND CharterGapiCoreSmoke)
endif()
