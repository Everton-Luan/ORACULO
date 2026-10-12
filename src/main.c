#include <raylib.h>
#include "graphics/Animation.h"
#include "entities/player.h"
#include "map/map.h"

int main(void)
{
    const int SCREEN_WIDTH  = 900;
    const int SCREEN_HEIGHT = 450;

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Oráculo");
        ToggleFullscreen();
        SetTargetFPS(60);

        PlayerBody player;
        PlayerInit(&player);

        // PROVISÓRIO — manual em PNG
        Texture2D manual = LoadTexture("assets/texture/foto_cap3.png"); // ajuste o caminho
        bool manual_aberto = false;
        int sw = GetScreenWidth();
        int sh = GetScreenHeight();
        // fim provisório

        // ── Teste MAP_CROP (recorte do Pokemon Center 1F) ──
        MapBody map;
        MapInit(&map, MAP_CROP, "assets/texture/sprites_teste/mapas_temporarios/Game Boy Advance - Pokemon FireRed.png");
        MapSetCrop(&map,
            (Rectangle){ 8.0f, 25.0f, 239.0f, 158.0f },        // origem na textura
            (Rectangle){ 220.0f,  100.0f, 239*6.0f, 158*6.0f }     // destino na tela (escala 4x)
        );

        while (!WindowShouldClose())
        {   
            if (IsKeyDown(KEY_R)) PLayerReset(&player);
            // PROVISÓRIO — abre/fecha manual
            if (IsKeyPressed(KEY_M)) manual_aberto = !manual_aberto;

            if (!manual_aberto) {
                PlayerUpdateAction(&player);
            }
            // fim provisório

            BeginDrawing();

                ClearBackground(BLACK);
                MapDraw(&map);   // mapa primeiro, player por cima
                PlayerDraw(&player);

                // PROVISÓRIO — exibe o PNG do manual por cima de tudo
                if (manual_aberto) {
                // Calcula escala para caber na tela mantendo proporção
                float escala_x = (float)sw / manual.width;
                float escala_y = (float)sh / manual.height;
                float escala   = (escala_x < escala_y) ? escala_x : escala_y; // menor dos dois

                float dest_w = manual.width  * escala;
                float dest_h = manual.height * escala;

                // Centraliza na tela
                float dest_x = (sw - dest_w) / 2.0f;
                float dest_y = (sh - dest_h) / 2.0f;

                DrawRectangle(0, 0, sw, sh, (Color){ 0, 0, 0, 200 }); // fundo escuro
                DrawTexturePro(
                    manual,
                    (Rectangle){ 0, 0, (float)manual.width, (float)manual.height },
                    (Rectangle){ dest_x, dest_y, dest_w, dest_h },
                    (Vector2){ 0, 0 },
                    0.0f,
                    WHITE
                );
                DrawText("M - Fechar", 10, 10, 18, YELLOW);
            } else {
                    DrawText("M - Manual", 10, 10, 18, WHITE); // dica na tela
                }
                // fim provisório

            EndDrawing();
        }   

        // PROVISÓRIO
        UnloadTexture(manual);
        // fim provisório

        PlayerUnload(&player);
        MapUnload(&map);
    CloseWindow();
    return 0;
}