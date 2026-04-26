#include <iostream>
#include "raylib.h"
using namespace std;

#define WIDTH 700
#define HEIGHT 600
#define FPS 60

struct Circle {
    int x = 10;
    int y = 10;
    int radius = 10;
    int vx = 5;
    int vy = 5;
};

Circle circle;
Circle *ptr = &circle;


void updatePositions() {

    circle.x += circle.vx;
    circle.y += circle.vy;
    if(circle.x + circle.radius > WIDTH) {
        circle.x = WIDTH - circle.radius;
        circle.vx = -circle.vx;
    }

    if(circle.x - circle.radius < 0) {
        circle.x = circle.radius;
        circle.vx = -circle.vx;
    }

    // For top and bottom
    if(circle.y + circle.radius > HEIGHT) {
        circle.y = HEIGHT - circle.radius;
        circle.vy = -circle.vy;
    }

    if(circle.y - circle.radius < 0) {
        circle.y = circle.radius;
        circle.vy = -circle.vy;
    }
}

int main()
{
    InitWindow(WIDTH, HEIGHT, "Bouncing Ball");

    SetTargetFPS(FPS);
    while (!WindowShouldClose())
    {
        BeginDrawing();

            updatePositions();
            ClearBackground(BLACK);
            // BounceBall();   
            updatePositions();
            DrawCircle(circle.x,circle.y,circle.radius,WHITE);
        EndDrawing();
    }

    CloseWindow();

    return 0;
}
               