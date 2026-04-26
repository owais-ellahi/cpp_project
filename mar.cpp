#include <iostream>
#include "raylib.h"
using namespace std;

#define WIDTH 1200
#define HEIGHT 1000
#define MAX_BULLETS 5

#define MAX_ENEMIES 8


struct Player {
    float x;
    float y;
    int vx;
    int width;
    int height;
    Texture2D img;
};

struct Bullet {
    float x,y;
    float speed;
    bool active;
};

Bullet bullets[MAX_BULLETS];

struct Enemy {
    float x,y;
    float speed;
    bool active;
    Texture2D img;
};

Enemy enemies[MAX_ENEMIES];

bool gameOver = 0;



void updatePlayerPosition(Player *shooter) {

    if(shooter->x + 150 > WIDTH) {
                                       shooter->x = WIDTH - 150;
    }

    if (shooter->x - 10 < 0) {
        shooter->x = 10;
    }

    if(IsKeyDown(KEY_RIGHT)) {
        shooter->x += shooter->vx;
    } else if(IsKeyDown(KEY_LEFT)) {
        shooter->x -= shooter->vx;
    }
}

void shootBullets(Player *shooter) {
    for(int i = 0; i < MAX_BULLETS; i++) {
        if(!bullets[i].active) {
            bullets[i].active = true;
            bullets[i].x = shooter->x + 75;
            bullets[i].y = shooter->y;
            bullets[i].speed = 8;
            break;
        }
    }
}



void updateBullets() {
    for(int i = 0; i < MAX_BULLETS; i++) {
        if(bullets[i].active) {
            bullets[i].y -= bullets[i].speed;
            if(bullets[i].y < 0) {
                bullets[i].active = false;
            }
        }
    }
}

void spawnEnemy() {
    for(int i = 0; i < MAX_ENEMIES; i++) {
        if(!enemies[i].active) {
            enemies[i].active = true;
            enemies[i].speed = 10;
enemies[i].x = GetRandomValue(0,WIDTH-50);
            enemies[i].y = GetRandomValue(0,HEIGHT/2-50);
            enemies[i].img = LoadTexture("enemy_updated.png");
        }
    }
}

void updateEnemies() {
    for(int i = 0; i < MAX_ENEMIES;i++) {
        if(enemies[i].active) {
            enemies[i].x += enemies[i].speed;
            if(enemies[i].x + 150 > WIDTH) {
                enemies[i].x =  WIDTH - 150;
                enemies[i].speed = -enemies[i].speed;
                enemies[i].y += 30;
            }

            if(enemies[i].x - 1 < 0) {
                enemies[i].x = 1;
                enemies[i].speed = -enemies[i].speed;
            }
            DrawTexture(enemies[i].img,enemies[i].x,enemies[i].y,WHITE);
        }

    }
}

void checkCollision(Player *shooter) {
    for(int i = 0; i < MAX_ENEMIES; i++) {
        if(shooter->x+150 > enemies[i].x and shooter->x < enemies[i].x and shooter->x < enemies[i].x + enemies[i].img.width and shooter->y + shooter->img.height > enemies[i].y and shooter->y < enemies[i].y + enemies[i].img.height) {
            // Logic for game over
            gameOver = 1;
        }
    }

    // cout << enemies[0].img.height << endl;
}

void reset() {
if(IsKeyPressed(KEY_ENTER)) {
        gameOver = 0;
        spawnEnemy();
    }
    DrawText("Game Over",WIDTH/2-50,HEIGHT/2,50,WHITE);
}

void drawEnemiesAndPlayer(Player *shooter) {
    for(int i = 0; i < MAX_ENEMIES;i++) {
        DrawTexture(enemies[i].img,enemies[i].x,enemies[i].y,WHITE);
    }

    DrawTexture(shooter->img,shooter->x,shooter->y,WHITE);
}

void drawBullets() {
    for (int i = 0; i < MAX_BULLETS; i++) {
        if (bullets[i].active)
            DrawCircle(bullets[i].x, bullets[i].y, 5, RED);
    }
}

void checkBulletCollision() {
    for(int i = 0; i < MAX_BULLETS; i++) {
        for(int j = 0; j < MAX_ENEMIES; j++) {
            if(bullets[i].x + 5 > enemies[j].x and bullets[i].x - 5 < enemies[j].x + enemies[j].img.width and bullets[i].y + 5 > enemies[j].y and bullets[i].y - 5 < enemies[j].y + enemies[j].img.height) {
                enemies[j].active = false;
                bullets[i].active = false;
            }
        }

    }
}


int main(void)
{
    InitWindow(WIDTH, HEIGHT, "Space Shooter");
    Texture2D background = LoadTexture("background.jpg");
    SetTargetFPS(60);
Player shooter = {
        WIDTH/2,
        HEIGHT-150,
        10,
        0,
        0,
        LoadTexture("output.png")
    };


    // for(int i = 0; i < MAX_ENEMIES; i++) {
    //     enemies[i].active = false;
    // }

    spawnEnemy();

    while (!WindowShouldClose())
    {

        BeginDrawing();
            ClearBackground(BLACK);
            DrawTexture(background,0,0,WHITE);
            if(gameOver) {
                drawBullets();
                drawEnemiesAndPlayer(&shooter);
                reset();
            } else {
                DrawTexture(shooter.img, shooter.x,shooter.y, WHITE);
                updatePlayerPosition(&shooter);
                updateEnemies();

                updateBullets();
                checkCollision(&shooter);
                checkBulletCollision();
                drawBullets();

                if(IsKeyPressed(KEY_SPACE)){
                    shootBullets(&shooter);
                }
            }

EndDrawing();
    }

    CloseWindow();

    return 0;
}
        