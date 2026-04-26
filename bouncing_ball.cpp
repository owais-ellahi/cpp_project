#include <iostream>
#include "raylib.h"
#define WIDTH 800
#define HEIGHT 700
#define FPS 60

using namespace std;
struct  circle{
    int x=10;
    int y=10;
    int radius=20;
    int vx=5;
    int vy=5;
};
circle Circle;
void updateposition(){
    
    
    Circle.x +=Circle.vx;
    Circle.y +=Circle.vy;

    if(Circle.x + Circle.radius >WIDTH){
        Circle.x=WIDTH-Circle.radius;
        Circle.vx=-Circle.vx;
    }
    if(Circle.x - Circle.radius < 0){
        Circle.x=Circle.radius;
        Circle.vx=-Circle.vx;
    }
    if(Circle.y + Circle.radius >HEIGHT){
        Circle.y=HEIGHT-Circle.radius;
        Circle.vy=-Circle.vy;
    }
    if(Circle.y - Circle.radius < 0){
        Circle.y=Circle.radius;
        Circle.vy=-Circle.vy;
    }
}



int main(){
    InitWindow(WIDTH, HEIGHT, "Bouncing Ball");

    SetTargetFPS(FPS);
    while (!WindowShouldClose())
    {
        BeginDrawing();
            ClearBackground(BLACK);
            updateposition();
            DrawCircle(Circle.x , Circle.y , Circle.radius , RED);
            
        EndDrawing();
    }

    CloseWindow();

    return 0;
}
