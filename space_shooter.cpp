#include <iostream>
#include "raylib.h"
#define  WIDTH 1000
#define HEIGHT 1000
#define FPS 120
#define SIZE 10
#define max_bulit 50
#define max_enimy 5
#define MAX_exp 50
#define max_en_bul 50
int x=400;
int y=500;
using namespace std;
enum direction{stop=0 , left_dir , right_dir , up_dir , down_dir};
direction dir;
struct bulits{int b , c; 
    bool active;
    float speed;
};


bulits bulit[max_bulit];
struct enimys{
    int x1,y1;
    bool active1;
    float speed1;
};
enimys en[max_enimy];
struct explossion{
    int x2,y2;
    bool active2;
    float timer;
};
struct enimy_bulits{
    int x, y;
    float speed3;
    bool active3;
};
enimy_bulits enm[max_en_bul];
explossion explosion[MAX_exp];
void move_jet(Texture2D jetTex){
    if(x < 0){
        x=0;
    }
    if(x+jetTex.width>WIDTH){
        x=WIDTH-jetTex.width;
    }
     if(y < 0){
        y=0;
    }
    if(y+jetTex.height>HEIGHT){
        y=HEIGHT-jetTex.height;
    }
}
void sh_bulits(Texture2D jetTex, Sound &bulitsound){
    if(IsKeyPressed(KEY_SPACE)){
        for (int i = 0; i < max_bulit; i++)
        {
            if(!bulit[i].active){
                bulit[i].b=x+jetTex.width/2;
                bulit[i].c=y;
                bulit[i].active=true;
                bulit[i].speed=10;
                PlaySound(bulitsound);
                
               break; 
            }   
        }
    }
}
void move_bulits(){
    for (int i = 0; i < max_bulit; i++)
    {
        if(bulit[i].active){
            bulit[i].c -=bulit[i].speed;
            if (bulit[i].c<0){
                bulit[i].active=false;
                }       
        }
    }
}
int score=0;
void collision_en(Texture2D end_Tex , Sound &hit ){
    for (int i = 0; i < max_bulit; i++)
    {
        if(!bulit[i].active){
            continue;
        }
        for (int j = 0; j < max_enimy; j++)
        {
            if (!en[j].active1)
            {
                continue;
            }
            if (bulit[i].b<en[j].x1+end_Tex.width && bulit[i].b+10 >en[j].x1 && bulit[i].c < en[j].y1+end_Tex.height && bulit[i].c+20>en[j].y1)
            {
                bulit[i].active=false;
                en[j].active1=false;
                en[j].x1=rand()%(0,WIDTH-end_Tex.width);

                en[j].y1=-end_Tex.height;
                en[j].active1=true;
                PlaySound(hit);
                score +=5;
            }   
        }   
    }
}
void random_position(){
    for (int  i = 0; i < max_enimy; i++)
    {
        en[i].x1=rand()%(WIDTH-50);
        en[i].y1=rand()%200;
        en[i].active1=true;
        en[i].speed1=2 + rand()%3;
    }    
}
void move_en(Texture2D end_Tex){
    for (int i = 0; i < max_enimy; i++)
    {
        if (en[i].active1)
        {
            en[i].y1+=en[i].speed1;
            if (en[i].y1>HEIGHT)
            {
                en[i].y1=0;
                en[i].x1 = rand() % (WIDTH - end_Tex.width);   
            }   
        }   
    }
}
int Player_hit=0;
bool gameover=false;
void player_hit(Texture2D jetTex){
    for(int i=0;i<max_en_bul;i++){
        if(!enm[i].active3) continue;

        if(enm[i].x < x + jetTex.width &&
           enm[i].x + 6 > x &&
           enm[i].y < y + jetTex.height &&
           enm[i].y + 15 > y){

            enm[i].active3 = false;
            DrawText("PLAYER HIT!",400,400,30,RED);
            Player_hit++;
            if(Player_hit>=5){
                gameover=true;
            }
        }
    }
}

void enimy_bul(Texture2D end_Tex){
    for (int i=0; i<max_enimy; i++){
        if (!en[i].active1)
        {
            continue;
        }
        if(en[i].y1>0 && en[i].y1<HEIGHT){
        
         
            if(GetRandomValue(0,100)<3){
                for (int j = 0; j < max_en_bul; j++)
                {
                    if(!enm[j].active3){
                        enm[j].x=en[i].x1+end_Tex.width/2;
                        enm[j].y=en[i].y1+end_Tex.height;
                        enm[j].active3=true;
                        enm[j].speed3=7;
                        break;
                    }
                }
            }
        }
    }
}
void move_en_bul(){
    for (int i = 0; i < max_en_bul; i++)
    {
        if (enm[i].active3)
        {
            enm[i].y +=enm[i].speed3;
            if (enm[i].y>HEIGHT)
            {
                enm[i].active3=false;
            }
            
        }
    }
}
int main(){
   
    InitAudioDevice();
    Music back = LoadMusicStream("back.mp3"); // Music stream load karein
    PlayMusicStream(back); // Loop se pehle play shuru karein
    for (int i = 0; i < max_bulit; i++){
        bulit[i].active=false;
    }
    for (int j=0; j<max_en_bul; j++){
        enm[j].active3=false;
    }
    InitWindow(WIDTH,HEIGHT, "space_shooter");
    SetTargetFPS(FPS);
    Sound bulitsound=LoadSound("bul.mp3");
    Sound hit=LoadSound("hit.mp3");
    Texture2D jetTex=LoadTexture("jet1.png");
    Texture2D bg=LoadTexture("space1.png");
    Texture2D end_Tex=LoadTexture("enimy.png");
    random_position();
    while (!WindowShouldClose())
    {
        
        UpdateMusicStream(back);
        
        if(!gameover){
        if(IsKeyDown(KEY_LEFT)){
            x -=SIZE;;
        }
        if(IsKeyDown(KEY_RIGHT)){
            x +=SIZE;
        }
        if(IsKeyDown(KEY_UP)){
            y -=SIZE;
        }
        if(IsKeyDown(KEY_DOWN)){
            y +=SIZE;
        }
        move_jet(jetTex);
        sh_bulits(jetTex, bulitsound);
        move_en(end_Tex);
        enimy_bul(end_Tex);
         move_en_bul();
         player_hit(jetTex);
        move_bulits();
        collision_en(end_Tex, hit );
        
    }
    else { // game over screen
        if(IsKeyPressed(KEY_R)){
            score=0;
            Player_hit=0;
            gameover=false;
            x = 400;
            y = 500;
            random_position();
            for(int i=0;i<max_en_bul;i++)
                enm[i].active3=false;
            for(int i=0;i<max_bulit;i++)
                bulit[i].active=false;

        }
    }
    ClearBackground(BLACK);
    BeginDrawing();
        DrawTexture(bg , 0 , 0 , WHITE);
         DrawTexture(jetTex, x , y ,WHITE);
         if(!gameover){
            DrawText(TextFormat("Score: %d", score), 20, 20, 30, YELLOW);

         for (int i = 0; i < max_enimy; i++)
         {
            if (en[i].active1)
            {
            DrawTexture(end_Tex,en[i].x1 , en[i].y1 ,WHITE);
            }
         }

          
         for (int i = 0; i < max_bulit; i++)
         {
            if(bulit[i].active){
                DrawRectangle(bulit[i].b , bulit[i].c , 10 ,20 , RED);
            }
         }
         for (int i = 0; i < max_en_bul; i++)
         {
            if(enm[i].active3){
                DrawRectangle(enm[i].x , enm[i].y , 10 ,20 , RED);
            }
         }
        }else{
            DrawText("GAME OVER!", 400, 500, 50, RED);
        DrawText("Press R to Restart", 380, 560, 20, WHITE);

        }
         EndDrawing();
         
    }

    UnloadSound(bulitsound);
    UnloadSound(hit);
    UnloadMusicStream(back);
    CloseAudioDevice();
    
    CloseWindow();
    return 0;
    
}
