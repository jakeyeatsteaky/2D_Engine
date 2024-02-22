#include <SDL.h>
#include "Game.hpp"

int main([[maybe_unused]] int argc, [[maybe_unused]] char* argv[]) 
{
    {
        Game game;
        if(game.Setup()) return -1; // returns 0 on success
        game.Run();
        game.Destroy(); // all resources managed with smart pointers so right now this function isn't implemented;
    }

    SDL_Quit();

    std::cout << "success" << std::endl;
    return 0;
}
