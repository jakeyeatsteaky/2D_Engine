#include <SDL.h>
#include "Game.hpp"

Game::Game() : 
    m_window(nullptr, SDL_DestroyWindow),
    m_renderer(nullptr, SDL_DestroyRenderer),
    m_initialized(false),
    m_running(false)
{
    
}

Game::~Game()
{
    std::cout << "Destroying the Game Object" << std::endl;
}

int Game::Setup()
{
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        std::cerr << "Error initializing SDL: " <<SDL_GetError() << std::endl;
        return -1;
    }    

    SDL_Window* pWindow = SDL_CreateWindow(GAME_TITLE.data(),
                                          SDL_WINDOWPOS_CENTERED,
                                          SDL_WINDOWPOS_CENTERED,
                                          WINDOW_WIDTH,
                                          WINDOW_HEIGHT,
                                          SDL_WINDOW_BORDERLESS);
    if(!pWindow)
    {
        std::cerr << "Error initializing SDL Window: " << SDL_GetError() << std::endl;
        return -1;
    }

    SDL_Renderer* pRenderer = SDL_CreateRenderer(pWindow, -1, 0);

    if (!pRenderer)
    {
        std::cerr << "Error initializing SDL Renderer: " << SDL_GetError() << std::endl;
        return -1;
    }

    m_window.reset(pWindow);        // transfer ownership to unique pointer with custom deletion
    m_renderer.reset(pRenderer);

    if (m_window && m_renderer)
        m_running = true, m_initialized = true;

    return 0;
}

void Game::Run()
{
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
