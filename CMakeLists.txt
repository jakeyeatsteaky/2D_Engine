cmake_minimum_required(VERSION 3.10)

project(2D_Engine)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
add_compile_options(/W4 /WX /wd4201)

# Manually set the SDL2 paths
set(SDL2_INCLUDE_DIRS "C:/SDL2/include")
set(SDL2_LIBRARIES "C:/SDL2/lib/x64")

# Set the SDL2_image paths
set(SDL2_IMAGE_INCLUDE_DIRS "C:/SDL2_image/include")
set(SDL2_IMAGE_LIBRARIES "C:/SDL2_image/lib/x64")

# Set the SDL2_ttf paths
set(SDL2_TTF_INCLUDE_DIRS "C:/SDL2_ttf/include")
set(SDL2_TTF_LIBRARIES "C:/SDL2_ttf/lib/x64")

# Set the SDL2_mixer paths
set(SDL2_MIXER_INCLUDE_DIRS "C:/SDL2_mixer/include")
set(SDL2_MIXER_LIBRARIES "C:/SDL2_mixer/lib/x64")

# Set the Lua paths
set(LUA_INCLUDE_DIRS "C:/Lua_win/include")
set(LUA_LIBRARIES "C:/Lua_win")

# Include the SDL2, SDL2_image, SDL2_ttf, SDL2_mixer, and Lua directories
# Ensure the ./thirdParty directory is included for compiler include path
include_directories(${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS} ${SDL2_TTF_INCLUDE_DIRS} ${SDL2_MIXER_INCLUDE_DIRS} ${LUA_INCLUDE_DIRS} ./src ./thirdParty ./include)

# Globbing source and header files
file(GLOB_RECURSE PROJECT_SOURCES "src/*.cpp")
file(GLOB_RECURSE PROJECT_HEADERS "include/*.hpp")
set(NOTES_FILE "notes.md") 

add_executable(2D_Engine main.cpp ${PROJECT_SOURCES} ${PROJECT_HEADERS})

# Organizing files into "Source Files" and "Header Files" groups for Visual Studio
source_group("Source Files" FILES ${PROJECT_SOURCES})
source_group("Header Files" FILES ${PROJECT_HEADERS})
source_group("Notes" FILES ${NOTES_FILE}) 

# Link against SDL2, SDL2_image, SDL2_ttf, SDL2_mixer, and Lua
target_link_libraries(2D_Engine "${SDL2_LIBRARIES}/SDL2.lib" "${SDL2_LIBRARIES}/SDL2main.lib" "${SDL2_IMAGE_LIBRARIES}/SDL2_image.lib" "${SDL2_TTF_LIBRARIES}/SDL2_ttf.lib" "${SDL2_MIXER_LIBRARIES}/SDL2_mixer.lib" "${LUA_LIBRARIES}/liblua54.a")

# Copy DLLs to the output directory
file(COPY  
    "${SDL2_LIBRARIES}/SDL2.dll" 
    "${SDL2_IMAGE_LIBRARIES}/SDL2_image.dll" 
    "${SDL2_TTF_LIBRARIES}/SDL2_ttf.dll" 
    "${SDL2_MIXER_LIBRARIES}/SDL2_mixer.dll" 
    "${LUA_LIBRARIES}/lua54.dll"  
    DESTINATION ${CMAKE_BINARY_DIR})
