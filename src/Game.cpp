#include <SDL.h>
#include <SDL_image.h>
#include "Game.hpp"
#include <glm/glm.hpp>
#include <chrono>

#ifdef WIN32
#include <windows.h>
#endif

namespace Engine
{
    const std::string getPngFromList(unsigned index) 
    {
        std::vector<std::string> ret = {
        "bullet.png",
        "chopper-spritesheet.png",
        "tank-tiger-right.png"
        };

        if(index < static_cast<unsigned>(ret.size()))
            return ret.at(index);
        else
            return "Error -> invalid index";
    }


}

Game::Game() : 
    m_window(nullptr, SDL_DestroyWindow),
    m_renderer(nullptr, SDL_DestroyRenderer),
    m_pFrameRateChecker(nullptr),
    m_frameRateMutex(),
    m_frameRate(0.0),
    m_millisecondsPreviousFrame(0),
    m_initialized(false),
    m_running(false),
    m_windowWidth(Engine::DEFAULT_WINDOW_WIDTH),
    m_windowHeight(Engine::DEFAULT_WINDOW_HEIGHT)
{

}

Game::~Game()
{
    m_pFrameRateChecker->join();
    std::cout << "Destroying the Game Object" << std::endl;
}

int Game::Init()
{
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        std::cerr << "Error initializing SDL: " <<SDL_GetError() << std::endl;
        return -1;
    }    

    // Screen dimensions for window
    SDL_DisplayMode displayMode;
    SDL_GetCurrentDisplayMode(0, &displayMode);
    m_windowWidth = displayMode.w / 4;
    m_windowHeight = displayMode.h / 2;

    SDL_Window* pWindow = SDL_CreateWindow(Engine::GAME_TITLE.data(),
                                          SDL_WINDOWPOS_CENTERED,
                                          SDL_WINDOWPOS_CENTERED,
                                          m_windowWidth,
                                          m_windowHeight,
                                          SDL_WINDOW_RESIZABLE); // SDL_WINDOW_BORDERLESS
    if(!pWindow)
    {
        std::cerr << "Error initializing SDL Window: " << SDL_GetError() << std::endl;
        return -1;
    }

    SDL_Renderer* pRenderer = SDL_CreateRenderer(pWindow, -1, SDL_RENDERER_ACCELERATED); // | SDL_RENDERER_PRESENTVSYNC will keep frame rate for this at 60fps roughly

    if (!pRenderer)
    {
        std::cerr << "Error initializing SDL Renderer: " << SDL_GetError() << std::endl;
        return -1;
    }

    m_window.reset(pWindow);        // transfer ownership to unique pointer with custom deletion
    m_renderer.reset(pRenderer);

    if (m_window && m_renderer)
        m_running = true, m_initialized = true;

    //SDL_SetWindowFullscreen(m_window.get(), SDL_WINDOW_FULLSCREEN); // changes video mode of screen

    return 0;
}

glm::vec2 playerPosition;
glm::vec2 playerVelocity;


void Game::Setup()
{
    playerPosition = glm::vec2(10.0, 20.0);
    playerVelocity = glm::vec2(1.0, 0.5);

    // kick off framerate thread
    m_pFrameRateChecker = std::shared_ptr<std::thread>(new std::thread(&Game::CheckFrameRate, this));

#ifdef WIN32
    SetThreadDescription(m_pFrameRateChecker->native_handle(), L"CheckFrameRate");
#endif

}

void Game::Run()
{
    Setup();

    while (m_running)
    {
        Input();
        Update();
        Render();
    }
}

void Game::Input()
{
    SDL_Event event;

    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
            case SDL_QUIT:
            {
                m_running = false;
                break;
            }

            case SDL_KEYDOWN:
            {
                ProcessKeyDown(event.key.keysym.sym);
                break;
            }
        }
    }


}

void Game::Update()
{
    uint32_t frameStart = SDL_GetTicks();

    // Perform game state updates
    playerPosition += playerVelocity;


    uint32_t elapsedTime = SDL_GetTicks() - frameStart;
    uint32_t delayTime = static_cast<uint32_t>(Engine::MILLISECONDS_PER_FRAME) > elapsedTime ? static_cast<uint32_t>(Engine::MILLISECONDS_PER_FRAME) - elapsedTime : 0;
    if (delayTime > 0) {
        SDL_Delay(delayTime);
    }

    m_millisecondsPreviousFrame = SDL_GetTicks();

    uint32_t totalFrameTime = static_cast<uint32_t>(m_millisecondsPreviousFrame) - frameStart;

    {
        std::lock_guard<std::mutex> lock(m_frameRateMutex);
        m_frameRate = 1000.0 / totalFrameTime; 
    }
}

void Game::Render() const
{
    SDL_SetRenderDrawColor(m_renderer.get(), 0x45, 0x5F, 0xAA, 0xFF);
    SDL_RenderClear(m_renderer.get());

    std::string tiger = Engine::PATH_TO_ASSETS.data() + Engine::getPngFromList(2);

    SDL_Rect tigerRect = {
        (int)playerPosition.x, 
        (int)playerPosition.y, 
        (int)playerPosition.y, 
        (int)playerPosition.y};

    SDL_Surface* surface = IMG_Load(tiger.c_str());
   
    SDL_Texture* texture = SDL_CreateTextureFromSurface(m_renderer.get(), surface);
    SDL_FreeSurface(surface);                                                       // dont need the surface once you have the texture.
    SDL_RenderCopy(m_renderer.get(), texture, NULL, &tigerRect);
    SDL_DestroyTexture(texture);

    SDL_RenderPresent(m_renderer.get()); // swap buffers
}

void Game::Destroy()
{

}

void Game::CheckFrameRate() const
{
    std::this_thread::sleep_for(std::chrono::milliseconds(500)); // allow game to start up
    while(m_running)
    {

        {
            std::lock_guard<std::mutex> lock(m_frameRateMutex);
            std::cout << "FPS: " << m_frameRate << std::endl;
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
    std::cout << "Exiting Check Frame Rate Thread" << std::endl;
}

void Game::ProcessKeyDown(const SDL_Keycode& keyCode) 
{
    switch (keyCode)
    {
        case SDLK_ESCAPE:
        {
            m_running = false;
            std::cout << "Exiting the Application" << std::endl;
            break;
        }

        case SDLK_SPACE:
        {
            std::cout << "Pushed the SPACE BAR" << std::endl;
            break;
        }

        default:
        {
            std::cout << "SDL Key Code " << keyCode << " processing has not been handled" << std::endl;
            break;
        }

    }
}
