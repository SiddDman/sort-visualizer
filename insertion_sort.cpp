#include <bits/stdc++.h>
#include <SDL2/SDL.h>
#include <random>

using namespace std;

#undef main

void drawState(vector<int> &v, SDL_Renderer *renderer, int &red, int &blue)
{

    for (int i = 0; i < v.size(); i++)
    {
        if (i == red)
            SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        else if (i == blue)
            SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
        else
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderDrawLine(renderer, i, 99, i, v[i]);
    }
}

int main()
{
    random_device rd;
    uniform_int_distribution<int> d(1, 99);

    vector<int> v;
    for (int i = 0; i < 100; i++)
        v.push_back(d(rd));

    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window *window = nullptr;
    SDL_Renderer *renderer = nullptr;
    int window_Width = 800;
    int window_Height = 600;

    window = SDL_CreateWindow("Insertion Sort", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, window_Width, window_Height, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    bool running = true;
    SDL_Event e;

    SDL_RenderSetScale(renderer, 8, 6);

    // Sort Algorithm
    for (int i = 1; i < v.size() && running; i++)
    {
        int j = i - 1, key = v[i];
        while (j >= 0 && v[j] > key)
        {
            v[j + 1] = v[j--];
            while (SDL_PollEvent(&e))
            {
                if (e.type == SDL_QUIT)
                {
                    running = false;
                    SDL_Quit();
                    return EXIT_SUCCESS;
                }
                if (e.type == SDL_KEYDOWN && (e.key.keysym.sym == SDLK_q || e.key.keysym.sym == SDLK_ESCAPE))
                {
                    running = false;
                    SDL_Quit();
                    return EXIT_SUCCESS;
                }
            }

            // Clear the Screen
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            SDL_RenderClear(renderer);

            // Draw the state of the sort
            drawState(v, renderer, i, j);

            // Show to window
            SDL_RenderPresent(renderer);
            SDL_Delay(25);
        }
        v[j + 1] = key;
    }

    // Clean up SDL resources
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}