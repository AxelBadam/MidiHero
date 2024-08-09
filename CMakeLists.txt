cmake_minimum_required(VERSION 3.16)
project(MidiHero LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

# Fetch SFML
include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x)
FetchContent_MakeAvailable(SFML)

# Manually specify midifile path
set(MIDIFILE_INCLUDE_DIR /Users/axel/Desktop/cmake-sfml-project/src/midifile/include)
set(MIDIFILE_LIB_DIR /Users/axel/Desktop/cmake-sfml-project/src/midifile/lib)

add_executable(main src/main.cpp src/Note.cpp src/Game.cpp)

target_include_directories(main PRIVATE ${MIDIFILE_INCLUDE_DIR})
target_link_libraries(main PRIVATE
    sfml-graphics
    sfml-window
    sfml-system
    sfml-audio
    ${MIDIFILE_LIB_DIR}/libmidifile.a)  # Adjust the filename and path as necessary

target_compile_features(main PRIVATE cxx_std_17)

if(WIN32)
    add_custom_command(
        TARGET main
        COMMENT "Copy OpenAL DLL"
        PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll $<TARGET_FILE_DIR:main>
        VERBATIM)
endif()
