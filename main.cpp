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
        clouds = {
            {50, 100, 30},
            {300, 150, 20},
            {600, 120, 25}
        };
    }

    void renderBackground() {
        // Dibujar el fondo y el castillo

        SDL_SetRenderDrawColor(renderer, 135, 206, 235, 255); 
        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer, 34, 139, 34, 255);
        SDL_Rect groundRect = {0, WINDOW_HEIGHT - 100, WINDOW_WIDTH, 100};
        SDL_RenderFillRect(renderer, &groundRect);

        drawCastle();
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
    std::vector<Cloud> clouds;

    void drawCastle() {
        // Torre izquierda
        SDL_SetRenderDrawColor(renderer, 169, 169, 169, 255);
        SDL_Rect leftTowerBase = {150, 300, 100, 200};
        SDL_RenderFillRect(renderer, &leftTowerBase);

        // Torre central
        SDL_Rect centerTowerBase = {325, 250, 150, 250};
        SDL_RenderFillRect(renderer, &centerTowerBase);

        // Torre derecha
        SDL_Rect rightTowerBase = {550, 300, 100, 200};
        SDL_RenderFillRect(renderer, &rightTowerBase);

        // Puerta
        SDL_SetRenderDrawColor(renderer, 139, 69, 19, 255);
        SDL_Rect door = {370, 400, 60, 100};
        SDL_RenderFillRect(renderer, &door);

        // Detalles en las torres (ventanas)
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_Rect leftWindow = {185, 350, 30, 50};
        SDL_RenderFillRect(renderer, &leftWindow);
        SDL_Rect rightWindow = {585, 350, 30, 50};
        SDL_RenderFillRect(renderer, &rightWindow);

        drawTowersAndFlags();
    }

    void drawTowersAndFlags() {
        // Techo de la torre izquierda
        SDL_SetRenderDrawColor(renderer, 255, 69, 0, 255); 
        SDL_Rect leftRoof = {140, 250, 120, 50};
        SDL_RenderFillRect(renderer, &leftRoof);

        // Techo de la torre central
        SDL_Rect centerRoof = {310, 200, 180, 50};
        SDL_RenderFillRect(renderer, &centerRoof);

        // Techo de la torre derecha
        SDL_Rect rightRoof = {540, 250, 120, 50};
        SDL_RenderFillRect(renderer, &rightRoof);

        // Banderas
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); /
        SDL_Rect leftFlagPole = {190, 220, 10, 30};
        SDL_RenderFillRect(renderer, &leftFlagPole);
        SDL_Rect centerFlagPole = {400, 170, 10, 30};
        SDL_RenderFillRect(renderer, &centerFlagPole);
        SDL_Rect rightFlagPole = {590, 220, 10, 30};
        SDL_RenderFillRect(renderer, &rightFlagPole);

        // Parte de la bandera
        SDL_Rect leftFlag = {200, 220, 20, 10};
        SDL_RenderFillRect(renderer, &leftFlag);
        SDL_Rect centerFlag = {410, 170, 20, 10};
        SDL_RenderFillRect(renderer, &centerFlag);
        SDL_Rect rightFlag = {600, 220, 20, 10};
        SDL_RenderFillRect(renderer, &rightFlag);
    }
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
