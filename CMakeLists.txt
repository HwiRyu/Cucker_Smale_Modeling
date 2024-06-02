cmake_minimum_required(VERSION 3.14)
project(Cucker_Smale_Modeling)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")
set(CMAKE_OSX_SYSROOT /Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX.sdk)

set(SOURCE_FILES main.cpp
        scale.h
        functions.h
        axes.h
        cucker_smale.h
)

add_executable(Cucker_Smale_Modeling ${SOURCE_FILES})
include_directories(/usr/local/include)

find_package(SFML 2.5 COMPONENTS system window graphics network audio REQUIRED)
include_directories(${SFML_INCLUDE_DIRS})
target_link_libraries(Cucker_Smale_Modeling sfml-system sfml-window sfml-graphics sfml-audio sfml-network)
