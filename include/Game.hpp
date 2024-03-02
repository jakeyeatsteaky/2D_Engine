#ifndef GAME_HPP
#define GAME_HPP
#pragma once

#include <iostream>
#include <memory>
#include <thread>
#include <string>
#include <vector>
#include <stdint.h>
#include <mutex>

namespace Engine
{
    // startup constants
    constexpr std::string_view GAME_TITLE = "2DEngine\0";
    constexpr uint32_t DEFAULT_WINDOW_WIDTH = 800;
    constexpr uint32_t DEFAULT_WINDOW_HEIGHT = 600; 
    constexpr std::string_view PATH_TO_ASSETS = "../assets/images/\0";

    // Framerate data
    constexpr uint8_t FPS = 60;
    constexpr uint32_t MILLISECONDS_PER_FRAME = static_cast<uint32_t>(1000 / FPS);

    // utility methods
    const std::string getPngFromList(unsigned index) ;
}


#if 0
    TODO
        [ ] Implement fixed update
            Right now I have a mechanism in place which will limit the update cycle based on my target frame rate
            this still leads to 120fps gameplay being twice as fast as 60fps.  
             i want to decouple the update loop (fixed time step) and the render loop (target fps)

#endif
class Game
{
private:
    std::unique_ptr<SDL_Window, decltype(&SDL_DestroyWindow)> m_window;
    std::unique_ptr<SDL_Renderer, decltype(&SDL_DestroyRenderer)> m_renderer;

    // frame rate checker
    std::shared_ptr<std::thread> m_pFrameRateChecker;
    mutable std::mutex m_frameRateMutex;

    double m_frameRate;
    double m_millisecondsPreviousFrame;
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
    void CheckFrameRate() const;

    void ProcessKeyDown(const SDL_Keycode& keyCode); // SDL_KeyCode is just an int.  pass by value

    bool m_initialized;
    bool m_running;

    int m_windowWidth;
    int m_windowHeight;

};

#endif // end GAME_HPP