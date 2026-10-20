#include <raylib.h>
#include "scenes/menu.h"

// ─── Funções internas ─────────────────────────────────────────────────────────

/** @brief Carrega as texturas de fundo de cada subtela.
 * @param self Ponteiro para o MenuBody.
 */
static void menu_init_backgrounds(MenuBody *self) {
    self->backgrounds[TELA_PRINCIPAL] = LoadTexture("assets/texture/menu/tela_principal.png");
    self->backgrounds[TELA_NOME]      = LoadTexture("assets/texture/menu/tela_nome.png");
    self->backgrounds[TELA_RANKING]   = LoadTexture("assets/texture/menu/frame 3.png");
}

// ─── Funções públicas ─────────────────────────────────────────────────────────

void MenuInit(MenuBody *self) {
    menu_init_backgrounds(self);
    self->tela_atual  = TELA_PRINCIPAL;
    self->opcao_atual = MENU_OPC_INICIAR;
    self->confirmado  = false;
}

void MenuUpdate(MenuBody *self) {
    if (self->tela_atual == TELA_PRINCIPAL) {

        if (IsKeyPressed(KEY_DOWN))
            self->opcao_atual = (self->opcao_atual + 1) % MENU_TOTAL_OPC;

        if (IsKeyPressed(KEY_UP))
            self->opcao_atual = (self->opcao_atual - 1 + MENU_TOTAL_OPC) % MENU_TOTAL_OPC;

        if (IsKeyPressed(KEY_ENTER)) {
            if (self->opcao_atual == MENU_OPC_RANKING)
                self->tela_atual = TELA_RANKING;
            else
                self->confirmado = true; // inicia partida
        }

    } else if (self->tela_atual == TELA_RANKING) {

        if (IsKeyPressed(KEY_ESCAPE) || IsKeyPressed(KEY_ENTER))
            self->tela_atual = TELA_PRINCIPAL;

    } else if (self->tela_atual == TELA_NOME) {

        if (IsKeyPressed(KEY_ESCAPE))
            self->tela_atual = TELA_PRINCIPAL;
    }
}

void MenuDraw(MenuBody *self, ResourcesBody *resources, int scream_width, int scream_height) {
    // Fundo da subtela ativa
    Texture2D bg = self->backgrounds[self->tela_atual];
    DrawTexturePro(
        bg,
        (Rectangle){ 0, 0, (float)bg.width, (float)bg.height },
        (Rectangle){ 0, 0, (float)scream_width, (float)scream_height },
        (Vector2){ 0, 0 },
        0.0f,
        WHITE
    );

    if (self->tela_atual == TELA_PRINCIPAL) {

        const char *labels[MENU_TOTAL_OPC] = { "INICIAR PARTIDA", "RANKING" };

        for (int i = 0; i < MENU_TOTAL_OPC; i++) {
            bool  sel  = (i == self->opcao_atual);
            Color cor  = sel ? YELLOW : WHITE;
            float size = sel ? 72.0f : 60.0f;

            Vector2 dim = MeasureTextEx(resources->fonte_principal, labels[i], size, 1);
            Vector2 pos = {
                scream_width  / 2.0f - dim.x / 2.0f,
                scream_height * 0.55f + i * 90.0f
            };

            DrawTextEx(resources->fonte_principal, labels[i], pos, size, 1, cor);
        }

    } else if (self->tela_atual == TELA_RANKING) {

        // Stub — implementar quando o sistema de ranking existir
        Vector2 pos = { scream_width / 2.0f - 150.0f, scream_height / 2.0f };
        DrawTextEx(resources->fonte_principal, "RANKING EM BREVE", pos, 60.0f, 1, WHITE);

        Vector2 pos_voltar = { scream_width / 2.0f - 180.0f, scream_height * 0.75f };
        DrawTextEx(resources->fonte_principal, "ENTER/ESC - VOLTAR", pos_voltar, 40.0f, 1, GRAY);

    } else if (self->tela_atual == TELA_NOME) {

        // Stub — implementar quando o sistema de nome existir
        Vector2 pos = { scream_width / 2.0f - 120.0f, scream_height / 2.0f };
        DrawTextEx(resources->fonte_principal, "NOME EM BREVE", pos, 60.0f, 1, WHITE);
    }
}

void MenuUnload(MenuBody *self) {
    for (int i = 0; i < TELA_TOTAL; i++) {
        UnloadTexture(self->backgrounds[i]);
    }
    // fonte não é descarregada aqui — pertence ao ResourcesBody
}