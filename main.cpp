#include <SDL2/SDL.h>
#include <vector>
#include <iostream>

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

struct Cloud {
    float x, y;
    float speed;
};

class Background {
public:
    Background(SDL_Renderer* renderer) : renderer(renderer) {
        castleRect = {100, 200, 600, 300};  

        clouds = {
            {50, 100, 30},
            {300, 150, 20},
            {600, 120, 25}
        };
    }

    void renderBackground() {
        SDL_SetRenderDrawColor(renderer, 135, 206, 235, 255);
        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer, 34, 139, 34, 255); 
        SDL_Rect groundRect = {0, WINDOW_HEIGHT - 100, WINDOW_WIDTH, 100};
        SDL_RenderFillRect(renderer, &groundRect);

        
        SDL_SetRenderDrawColor(renderer, 169, 169, 169, 255); 
        SDL_RenderFillRect(renderer, &castleRect);
    }

    void renderClouds(float deltaTime) {
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); 
        for (auto& cloud : clouds) {
            cloud.x += cloud.speed * deltaTime;
            if (cloud.x > WINDOW_WIDTH) {
                cloud.x = -100; 
            }
            SDL_Rect cloudRect = {static_cast<int>(cloud.x), static_cast<int>(cloud.y), 100, 50};
            SDL_RenderFillRect(renderer, &cloudRect);
        }
    }

private:
    SDL_Renderer* renderer;
    SDL_Rect castleRect;
    std::vector<Cloud> clouds;
};

int main(int argc, char* argv[]) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "Error inicializando SDL: " << SDL_GetError() << std::endl;
        return -1;
    }

    SDL_Window* window = SDL_CreateWindow("Castle Background with Clouds", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, 0);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    Background background(renderer);

    bool running = true;
    Uint32 lastTime = SDL_GetTicks();
    SDL_Event event;

    while (running) {
        Uint32 currentTime = SDL_GetTicks();
        float deltaTime = (currentTime - lastTime) / 1000.0f;
        lastTime = currentTime;

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
        }

        background.renderBackground();
        background.renderClouds(deltaTime);

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
