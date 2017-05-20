#cmake ver req
cmake_minimum_required(VERSION 2.8.3)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_LIST_DIR}/cmake/modules/")
set(TRACK_TIME TRUE CACHE BOOL "Selects if time taken should be output when compiling")
set(PROFILE TRUE CACHE BOOL "Selects if profiling should be enabled")

#project name
set(project_name spring_template)
project(${project_name})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1z -Wall -Wextra -Wshadow -Werror -Wconversion -Wno-long-long -Wno-unused-parameter -Wno-unused-variable -Wno-format-pedantic -Wno-conversion")
if(NOT EMSCRIPTEN)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1z -Wall -Wextra -Wshadow -Werror -Wconversion -Wno-long-long -Wno-unused-parameter -Wno-unused-variable -Wno-format-pedantic")
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1z -Wall -Wextra -Werror -Wconversion -Wno-long-long -Wno-unused-parameter -Wno-unused-variable -Wno-format-pedantic -Wno-conversion -Wno-shadow")
endif()


add_custom_target(
    dophax_gen
    COMMAND ${CMAKE_CURRENT_LIST_DIR}/dophax/build/dophax_gen ${CMAKE_CURRENT_LIST_DIR}/spring_template.dpx
    COMMAND ${CMAKE_CURRENT_LIST_DIR}/dophax/build/dophax_gen ${CMAKE_CURRENT_LIST_DIR}/spring/spring.dpx
)

include(cotire)

file(GLOB_RECURSE spr_source_files "spring/spr/*.cpp")
file(GLOB_RECURSE spr_header_files "spring/spr/*.hpp")
file(GLOB_RECURSE spr_generated_source_files "spring/generated/spr/*.cpp")
file(GLOB_RECURSE spr_generated_header_files "spring/generated/spr/*.hpp")
file(GLOB_RECURSE lode_png_source_files "spring/lodepng/*.cpp")
file(GLOB_RECURSE lode_png_header_files "spring/lodepng/*.hpp")
file(GLOB_RECURSE source_files "src/*.cpp")
file(GLOB_RECURSE header_files "src/*.hpp")
file(GLOB_RECURSE generated_source_files "generated/*.cpp")
file(GLOB_RECURSE generated_header_files "generated/*.hpp")
file(GLOB_RECURSE gl_source_files "spring/glad/gl/*.c")

if(EMSCRIPTEN)
    set(CMAKE_EXECUTABLE_SUFFIX ".html")
    set(executable_name "index")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -s USE_SDL=2 -s USE_OGG=1 -s USE_VORBIS=1 -s FULL_ES2=1 -Wno-gnu-anonymous-struct -Wno-nested-anon-types --preload-file data/ -s TOTAL_MEMORY=67108864")
else()
    set(executable_name ${project_name})
endif()

if(NOT EMSCRIPTEN)
    find_package(SDL2 REQUIRED)
    if(SDL2_FOUND)
        include_directories(${SDL2_INCLUDE_DIR})
    endif()
    
    find_package(SDL2_mixer REQUIRED)
    if(SDL2_MIXER_FOUND)
        include_directories(${SDL2_MIXER_INCLUDE_DIRS})
    endif()

endif()

find_package(OpenGL REQUIRED)
if(OPENGL_FOUND)
    include_directories(${OPENGL_INCLUDE_DIRS})
endif(OPENGL_FOUND)

find_package(OpenAL REQUIRED)
if(OPENAL_FOUND)
    include_directories(${OPENAL_INCLUDE_DIR})
endif(OPENAL_FOUND)

find_package(GLM REQUIRED)
if(GLM_FOUND)
    include_directories(${GLM_INCLUDE_DIRS})
endif()

if(CMAKE_BUILD_TYPE STREQUAL "Debug" OR CMAKE_BUILD_TYPE STREQUAL "RelWithDebInfo")
    add_definitions(-DDEBUG_ON)
endif()

if(NOT PROFILE)
    add_definitions(-DNPROFILE)
endif()

include_directories("thero/include")
include_directories("dophax/json/src")

include_directories("dophax/datatables")
include_directories("generated")
include_directories("src")
include_directories("spring")
include_directories("spring/generated")
include_directories("spring/glad")
file(GLOB_RECURSE dophax_source_files "dophax/datatables/*.cpp")
file(GLOB_RECURSE dophax_header_files "dophax/datatables/*.h")

include_directories("imgui")
file(GLOB_RECURSE imgui_source_files "imgui/*.cpp")
file(GLOB_RECURSE imgui_header_files "imgui/*.h")

add_executable(${executable_name} ${spr_header_files} ${spr_source_files} ${spr_generated_header_files} ${spr_generated_source_files} ${header_files} ${source_files} ${generated_header_files} ${generated_source_files} ${lode_png_header_files} ${lode_png_source_files} ${dophax_source_files} ${dophax_header_files} ${imgui_header_files} ${imgui_source_files} ${gl_source_files})

if(TRACK_TIME)
    set_property(TARGET ${executable_name} PROPERTY RULE_LAUNCH_COMPILE "${CMAKE_COMMAND} -E time")
endif()

add_dependencies(${executable_name} dophax_gen)
target_link_libraries(${executable_name} ${OPENGL_LIBRARIES} ${SDL2_LIBRARY} ${SDL2_MIXER_LIBRARIES})
cotire(${executable_name})
