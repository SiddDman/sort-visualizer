#include <bits/stdc++.h>
#include <SDL2/SDL.h>
#include <random>

using namespace std;

#undef main

void drawState(vector<int> &v, SDL_Renderer *renderer, int l, int r, int mid)
{
    for (int i = 0; i < v.size(); i++)
    {
        if (i >= l && i < mid)
            SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        else if (i > mid && i <= r)
            SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
        else
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderDrawLine(renderer, i, 99, i, v[i]);
    }
}

void merge(vector<int> &v, int &l, int &mid, int &r, SDL_Renderer *renderer, SDL_Event &e)
{
    vector<int> temp;
    int i = l, j = mid + 1;
    while (i <= mid && j <= r)
        if (v[i] <= v[j])
            temp.push_back(v[i++]);
        else
            temp.push_back(v[j++]);
    while (i <= mid)
        temp.push_back(v[i++]);
    while (j <= r)
        temp.push_back(v[j++]);

    cout << i << " " << j << endl;

    for (int k = l; k <= r; k++)
        v[k] = temp[k - l];

    while (SDL_PollEvent(&e))
    {
        if (e.type == SDL_QUIT)
        {
            SDL_Quit();
            return;
        }
        if (e.type == SDL_KEYDOWN && (e.key.keysym.sym == SDLK_q || e.key.keysym.sym == SDLK_ESCAPE))
        {
            SDL_Quit();
            return;
        }
    }

    // Clear the Screen
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    // Draw the state of the sort
    drawState(v, renderer, l, r, mid);
    // Show to window
    SDL_RenderPresent(renderer);
    SDL_Delay(200);
}

void mergeSort(vector<int> &v, int l, int r, SDL_Renderer *renderer, SDL_Event &e)
{
    if (l < r)
    {
        int mid = l + (r - l) / 2;
        mergeSort(v, l, mid, renderer, e);
        mergeSort(v, mid + 1, r, renderer, e);
        merge(v, l, mid, r, renderer, e);
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
    int window_Width = 800;
    int window_Height = 600;

    window = SDL_CreateWindow("Merge Sort", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, window_Width, window_Height, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    bool running = true;
    SDL_Event e;

    SDL_RenderSetScale(renderer, 8, 6);

    // Sort Algorithm
    mergeSort(v, 0, v.size() - 1, renderer, e);

    // Clean up SDL resources
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}