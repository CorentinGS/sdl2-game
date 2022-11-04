cmake_minimum_required(VERSION 3.23)
project(GameEngine C)

set(CMAKE_C_STANDARD 17)

add_executable(GameEngine src/main.c src/main.h src/camera.c src/camera.h src/common.h src/defs.h src/draw.c src/draw.h src/entities.c src/entities.h
        src/init.c src/init.h src/input.c src/input.h src/io.c src/io.h src/map.c src/map.h src/menu.c src/menu.h src/pizza.c src/pizza.h
        src/player.c src/player.h src/sound.c src/sound.h src/stage.c src/stage.h src/structs.h src/text.c src/text.h src/textures.c src/textures.h
        src/util.c src/util.h)

# Add SDL2 CMake modules
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/sdl2)

# Add -lm to the linker flags
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -lm")

# Find SDL2, SDL2_image and SDL2_gfx libraries
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_gfx REQUIRED)
find_package(SDL2_mixer REQUIRED)
find_package(SDL2_ttf REQUIRED)

# Link SDL2::Main, SDL2::Image and SDL2::GFX to our project
target_link_libraries(${PROJECT_NAME} SDL2::Main SDL2::Image SDL2::GFX SDL2::Mixer SDL2::TTF)
