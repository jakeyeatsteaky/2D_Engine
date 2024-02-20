#include "Game.hpp"

int main([[maybe_unused]] int argc, [[maybe_unused]] char* argv[]) 
{
    
    Game game;

    if(game.Setup()) return -1; // returns 0 on success
    game.Run();
    game.Destroy();
    std::cout << "success" << std::endl;
    return 0;
}
