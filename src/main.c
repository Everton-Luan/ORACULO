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

            PlayerUpdateAction(&player);

            BeginDrawing();

                ClearBackground(BLACK);
                MapDraw(&map);   // mapa primeiro, player por cima
                PlayerDraw(&player);

            EndDrawing();
        }   

        PlayerUnload(&player);
        MapUnload(&map);
    CloseWindow();
    return 0;
}