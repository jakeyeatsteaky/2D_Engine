#ifndef GAME_HPP
#define GAME_HPP
#pragma once

#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include <stdint.h>

namespace Engine
{
    constexpr std::string_view GAME_TITLE = "2DEngine\0";
    constexpr uint32_t DEFAULT_WINDOW_WIDTH = 800;
    constexpr uint32_t DEFAULT_WINDOW_HEIGHT = 600; 
    constexpr std::string_view PATH_TO_ASSETS = "../assets/images/\0";
    const std::string getPngFromList(unsigned index) ;
}

class Game
{
private:
    std::unique_ptr<SDL_Window, decltype(&SDL_DestroyWindow)> m_window;
    std::unique_ptr<SDL_Renderer, decltype(&SDL_DestroyRenderer)> m_renderer;

public:
    Game();
    ~Game();

    int Init();
    void Setup();
    void Run();
    void Input();
    void Update();
    void Render() const;
    void Destroy();

    void ProcessKeyDown(const SDL_Keycode& keyCode); // SDL_KeyCode is just an int.  pass by value

    bool m_initialized;
    bool m_running;

    int m_windowWidth;
    int m_windowHeight;
};

#endif // end GAME_HPP