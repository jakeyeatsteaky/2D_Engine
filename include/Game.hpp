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
    std::unique_ptr<SDL_Window, decltype(&SDL_DestroyWindow)> m_window;
    std::unique_ptr<SDL_Renderer, decltype(&SDL_DestroyRenderer)> m_renderer;

public:
    Game();
    ~Game();

    int Setup();
    void Run();
    void Input();
    void Update();
    void Render() const;
    void Destroy();

    void ProcessKeyDown(const SDL_Keycode& keyCode); // SDL_KeyCode is just an int.  pass by value

    bool m_initialized;
    bool m_running;
};

#endif // end GAME_HPP