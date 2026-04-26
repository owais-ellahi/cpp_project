#include <iostream>
#include "raylib.h"
#include "time.h"
#include "math.h"
#include "stdlib.h"
#define WIDTH 900
#define HEIGHT 600

using namespace std;
int main(){
    InitWindow(WIDTH,HEIGHT, "coulomb force simulation");
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(BLACK);
        EndDrawing();
        /* code */
    }
    CloseWindow();
    return 0;
    
}