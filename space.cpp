#include <iostream>
#include "raylib.h"
#define  WIDTH 1000
#define HEIGHT 1000
#define FPS 60
#define SIZE 10
int x=400;
int y=500;

using namespace std;
enum direction{stop=0 , left_dir , right_dir , up_dir , down_dir};
direction dir;
void move_jet(){
    switch (dir)
    {
    case left_dir:
        x -=SIZE;
        break;
    case right_dir:
        x +=SIZE;
        break;
    case up_dir:
        y -=SIZE;
        break;
    case down_dir:
        y +=SIZE;
        break;

    
    default:
        break;
    }
}

int main(){
    InitWindow(WIDTH,HEIGHT, "space_shooter");
    SetTargetFPS(FPS);
    Texture2D bg=LoadTexture("jet.png");
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(BLACK);
         move_jet();
        DrawTexture(bg ,x , y, WHITE);
        EndDrawing();
        /* code */
    }
    // UnloadTexture(bg);
    CloseWindow();
    return 0;
    
}
