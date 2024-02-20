#ifndef GAME_HPP
#define GAME_HPP

#include <iostream>
#include <memory>
#include <string>
#include <stdint.h>

constexpr std::string_view GAME_TITLE = "2DEngine\0";
constexpr uint32_t WINDOW_WIDTH = 800;
constexpr uint32_t WINDOW_HEIGHT = 600; 

class Game
{
private:

public:
    Game();
    ~Game();

    int Setup();
    void Run();
    void Input();
    void Update();
    void Render();
    void Destroy();

    bool m_initialized;
};

#endif // end GAME_HPP