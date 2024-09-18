#include <bits/stdc++.h>
#include <SDL2/SDL.h>
#include <random>

using namespace std;

#undef main

void drawState(vector<int> &v, SDL_Renderer *renderer, int l, int r, int pivot)
{
    for (int i = 0; i < v.size(); i++)
    {
        if (i == pivot)
            SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        else if (i > pivot && i <= r)
            SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
        else if (i < pivot && i >= l)
            SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
        else
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderDrawLine(renderer, i, 99, i, v[i]);
    }
}

int partition(vector<int> &v, int &l, int &r, SDL_Renderer *renderer, SDL_Event &e)
{
    int pivot = v[l], i = l + 1, j = r;
    while (i <= j)
        if (v[i] < pivot)
            i++;
        else if (v[j] >= pivot)
            j--;
        else
            swap(v[i], v[j]);

    swap(v[l], v[j]);

    while (SDL_PollEvent(&e))
    {
        if (e.type == SDL_QUIT)
        {
            SDL_Quit();
            return EXIT_SUCCESS;
        }
        if (e.type == SDL_KEYDOWN && (e.key.keysym.sym == SDLK_q || e.key.keysym.sym == SDLK_ESCAPE))
        {
            SDL_Quit();
            return EXIT_SUCCESS;
        }
    }

    // Clear the Screen
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    // Draw the state of the sort
    drawState(v, renderer, l, r, pivot);
    // Show to window
    SDL_RenderPresent(renderer);
    SDL_Delay(120);

    return j;
}

void quickSort(vector<int> &v, int l, int r, SDL_Renderer *renderer, SDL_Event &e)
{
    if (l < r)
    {
        int pivot = partition(v, l, r, renderer, e);
        quickSort(v, l, pivot, renderer, e);
        quickSort(v, pivot + 1, r, renderer, e);
    }
    return;
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
    int window_Width = 900;
    int window_Height = 800;

    window = SDL_CreateWindow("Quick Sort", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, window_Width, window_Height, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    bool running = true;
    SDL_Event e;

    SDL_RenderSetScale(renderer, 9, 8);

    // Sort Algorithm
    quickSort(v, 0, v.size() - 1, renderer, e);

    // Clean up SDL resources
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}