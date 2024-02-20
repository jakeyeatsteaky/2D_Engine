#include <SDL.h>
#include "Game.hpp"

Game::Game() : 
    m_initialized(false)
{
    
}

Game::~Game()
{

}

int Game::Setup()
{
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        std::cerr << "Error initializing SDL: " <<SDL_GetError() << std::endl;
        return -1;
    }    

    SDL_Window* window = SDL_CreateWindow(GAME_TITLE.data(),
                                          SDL_WINDOWPOS_CENTERED,
                                          SDL_WINDOWPOS_CENTERED,
                                          WINDOW_WIDTH,
                                          WINDOW_HEIGHT,
                                          SDL_WINDOW_BORDERLESS);
    
    if(!window)
    {
        std::cerr << "Error initializing SDL Window: " << SDL_GetError() << std::endl;
        return -1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window,
        -1,
        0);

    if (!renderer)
    {
        std::cerr << "Error initializing SDL Renderer: " << SDL_GetError() << std::endl;
        return -1;
    }


    return 0;
}

void Game::Run()
{

}

void Game::Input()
{

}

void Game::Update()
{

}

void Game::Render()
{

}

void Game::Destroy()
{

}

