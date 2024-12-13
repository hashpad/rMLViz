#include <iostream>

#include "Context.h"
#include "State.h"
#include <memory>
#include <raylib.h>

#define APP_NAME "Machine Learning Visualization"
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 800
#define SCREEN_TITLE "The ML Game"

int main(int argc, char* argv[])
{
    std::cout << "starting the game" << std::endl;

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_TITLE);
    SetWindowTitle(APP_NAME);
    SetTargetFPS(60);

    Context ctx { std::make_unique<MainMenuState>() };

    while (!WindowShouldClose()) {
        ctx.update();

        BeginDrawing();
        ClearBackground(RAYWHITE);

        ctx.draw();

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
