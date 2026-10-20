#ifndef RESOURCES_H
#define RESOURCES_H

#include <raylib.h>

/**
 * @file resources.h
 * @brief Recursos globais compartilhados por todas as cenas do jogo.
 * @details Centraliza assets que precisam estar disponíveis durante toda
 *          a execução, como fontes. Deve ser inicializado uma única vez
 *          no main e descarregado ao encerrar o jogo.
 */

/** @brief Recursos globais do jogo. Acesse via ponteiro retornado por ResourcesGet(). */
typedef struct ResourcesBody {
    Font fonte_principal; /**< Fonte VT323, usada em todas as cenas. */
}ResourcesBody;

/**
 * @brief Inicializa e carrega todos os recursos globais.
 * @param self Ponteiro para o ResourcesBody a ser inicializado.
 */
void ResourcesInit(ResourcesBody *self);

/**
 * @brief Descarrega todos os recursos globais da memória.
 * @param self Ponteiro para o ResourcesBody a ser descarregado.
 */
void ResourcesUnload(ResourcesBody *self);

#endif