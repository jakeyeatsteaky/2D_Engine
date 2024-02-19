#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

#include <iostream>

#include <glm/glm.hpp>
#include <imgui/imgui.h>
#include <sol/sol.hpp>

int main([[maybe_unused]] int argc, [[maybe_unused]] char* argv[]) {
    // Initialize SDL
    sol::state lua;
    lua.open_libraries(sol::lib::base);
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return -1;
    }

    // Create a window
    SDL_Window* window = SDL_CreateWindow(
        "SDL2 Demo",                  // window title
        SDL_WINDOWPOS_UNDEFINED,      // initial x position
        SDL_WINDOWPOS_UNDEFINED,      // initial y position
        640,                          // width, in pixels
        480,                          // height, in pixels
        SDL_WINDOW_SHOWN              // flags - window is visible
    );

    if (window == NULL) {
        std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return -1;
    }

    // Get window surface
    SDL_Surface* screenSurface = SDL_GetWindowSurface(window);

    // Fill the surface white
    SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0xFF, 0xFF, 0xFF));

    // Update the surface
    SDL_UpdateWindowSurface(window);

    // Wait two seconds
    SDL_Delay(2000);

    // Destroy window
    SDL_DestroyWindow(window);

    // Quit SDL subsystems
    SDL_Quit();

    glm::vec2 vel = glm::vec2(5.0, -2.0);
    std::cout << vel.length << std::endl;

    return 0;
}
