#include <SDL.h>
#include <SDL_image.h>
#include "Game.hpp"

Game::Game() : 
    m_window(nullptr, SDL_DestroyWindow),
    m_renderer(nullptr, SDL_DestroyRenderer),
    m_initialized(false),
    m_running(false),
    m_windowWidth(Engine::DEFAULT_WINDOW_WIDTH),
    m_windowHeight(Engine::DEFAULT_WINDOW_HEIGHT)
{

}

Game::~Game()
{
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

    SDL_Renderer* pRenderer = SDL_CreateRenderer(pWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

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

void Game::Setup()
{

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

}

void Game::Render() const
{
    SDL_SetRenderDrawColor(m_renderer.get(), 0x45, 0x5F, 0xAA, 0xFF);
    SDL_RenderClear(m_renderer.get());

    std::string tiger = Engine::PATH_TO_ASSETS.data() + Engine::ASSETS_LIST_PNG.at(2);
    SDL_Surface* surface = IMG_Load(tiger.c_str());
    SDL_Texture* texture = SDL_CreateTextureFromSurface(m_renderer.get(), surface);
    SDL_FreeSurface(surface);                                                       // dont need the surface once you have the texture.
    SDL_RenderCopy(m_renderer.get(), texture, NULL, NULL);

    SDL_RenderPresent(m_renderer.get()); // swap buffers
}

void Game::Destroy()
{

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
