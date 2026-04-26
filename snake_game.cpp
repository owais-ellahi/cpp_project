#include <iostream>
#include "raylib.h"
#define WIDTH 900
#define HEIGTH 800
#define SIZE 10
#define FPS 20
#define max_tal 100
using namespace std;
int x=300;
int y=300;
int fruitx;
int fruity;
int score=0;
int tailx[max_tal],taily[max_tal];
int taillength=0;
enum direction{stop=0, left_dir , right_dir , up_dir , down_dir};
direction dir;
int counter=0;

    
void move(){
    for (int i = taillength-1; i >0; i--)
    {
        tailx[i]=tailx[i-1];
        taily[i]=taily[i-1];
    }
    if(taillength>0){
        tailx[0]=x;
        taily[0]=y;
    }
    
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
    // if (x + SIZE>WIDTH){
    //     x=WIDTH-SIZE;
    // }
    // if (x<0){
    //     x=0;
    // }
    // if (y + SIZE>HEIGTH){
    //     y=HEIGTH-SIZE;
    // }
    // if (y<0){
    //     y=0;
    // }
}
void fruit(){
    fruitx=GetRandomValue(0,WIDTH/SIZE-1)*SIZE;
    fruity=GetRandomValue(0,HEIGTH/SIZE-1)*SIZE;
}
bool selfcollision(){
    for(int i=0; i<taillength; i++){
        if (x==tailx[i] && y==taily[i])
        {
            return true;
        }
        
    }
    return false;
}
int main(){
    InitWindow(WIDTH,HEIGTH, "Random Snake");
    SetTargetFPS(FPS);
    dir=stop;
    fruit();
    Texture2D bg=LoadTexture("game.png");
    InitAudioDevice();
    Sound eatsound=LoadSound("bite.wav");
    Sound colide=LoadSound("colide.wav");
    Sound itself=LoadSound("itself.wav");
    

    while (!WindowShouldClose()) {

        DrawTexture(bg,0,0,WHITE);

       DrawRectangle(fruitx, fruity, SIZE ,SIZE, BLUE);
       for (int i = 0; i <taillength; i++)
        {
            DrawCircle(tailx[i],taily[i],SIZE,GREEN);
            
        }
        DrawCircle(x , y , SIZE , LIME);
        // for (int i = 0; i < WIDTH; i += SIZE) {
        // DrawLine(i, 0, i, HEIGTH, {40, 40, 60, 255});
        // }
        //     for (int j = 0; j < HEIGTH; j +=SIZE) {
        //         DrawLine(0, j, WIDTH, j, {40, 40, 60, 255});
        //     }
             
        if (IsKeyPressed(KEY_LEFT) && dir !=right_dir)
        {
            dir=left_dir;
        }
        if(IsKeyPressed(KEY_RIGHT) && dir!=left_dir){
            dir=right_dir;
        }
        if (IsKeyPressed(KEY_UP) && dir !=down_dir)
        {
            dir=up_dir;
        }
        if(IsKeyPressed(KEY_DOWN) && dir!=up_dir){
            dir=down_dir;
        }
        if(x<0 || x+SIZE>WIDTH || y<0 || y+SIZE>HEIGTH){
            taillength=0;
            score=0;
            x=(WIDTH/SIZE/2)*SIZE;
            y=(HEIGTH/SIZE/2)*SIZE;
            dir=stop;
            fruit();
            PlaySound(colide);
        }
        if(selfcollision()){
        taillength=0;
        score=0;
        x=(WIDTH/SIZE/2)*SIZE;
        y=(HEIGTH/SIZE/2)*SIZE;
        dir=stop;
        fruit();
        PlaySound(itself);
    }
        
        if(x==fruitx && y==fruity){
            score++;
            if(taillength<max_tal){
                taillength++;
            }
            fruit();
            PlaySound(eatsound);
        }
        
    
    
    move();
    
        BeginDrawing();
        ClearBackground(BLACK);
        
        DrawText(TextFormat("score%d",score),10,10,20,WHITE);
        
        
                
        
        EndDrawing();
        
    }
    UnloadSound(eatsound);
    UnloadSound(colide);
    UnloadSound(itself);
    CloseAudioDevice();

    CloseWindow();
    return 0;
}
