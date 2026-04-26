#include <iostream>
#include "raylib.h"
#define WIDTH 900
#define HEIGHT 800
#define num_circle 80
#define FPS 60
#define gravit 1
using namespace std;
typedef struct{
    float r;
    int x, y  , vx ,vy;
}Gravity;
Gravity gravity[num_circle];
void gravityinit(){
    float r=10;
    for (int i = 0; i < num_circle; i++)
    {
        gravity[i].r=r;
        gravity[i].x=GetRandomValue(r,WIDTH-r);
        gravity[i].y=GetRandomValue(r, HEIGHT-r);
        gravity[i].vx=0;
        gravity[i].vy=3;
        
    }
    
}
void display(){
    for (int i = 0; i < num_circle; i++)
    {
    DrawCircle(gravity[i].x , gravity[i].y , gravity[i].r , RED);
    }
}
void manage(){
    for (int i = 0; i < num_circle; i++)
    {
        gravity[i].vy +=gravit;
        gravity[i].x +=gravity[i].vx;
        gravity[i].y +=gravity[i].vy;

        if (gravity[i].x + gravity[i].r >WIDTH){
            gravity[i].x = WIDTH-gravity[i].r;
            gravity[i].vx =-gravity[i].vx; 
        }
        if (gravity[i].x - gravity[i].r <0){
            gravity[i].x = gravity[i].r;
            gravity[i].vx =-gravity[i].vx; 
        }
        if (gravity[i].y + gravity[i].r >HEIGHT){
            gravity[i].y =HEIGHT - gravity[i].r;
            gravity[i].vy =-gravity[i].vy*0.8f; 
        }
        if (gravity[i].y - gravity[i].r <0){
            gravity[i].y = gravity[i].r;
            gravity[i].vy =-gravity[i].vy*0.8f; 
        }
        
    }
    
}





int main(){
    
    InitWindow(WIDTH, HEIGHT, "gravity");

    SetTargetFPS(FPS);
    gravityinit();
    while (!WindowShouldClose())
    {
        BeginDrawing();
        manage();
        ClearBackground(BLACK);
        display();
        
        
        EndDrawing();
    }

    CloseWindow();

    return 0;
}

