#ifndef HISTORIA_H
#define HISTORIA_H

#include "../personagens/personagem.h"

#define MAX_MISSOES 3

typedef struct {
    char titulo[50];
    int concluida;  /* 0 = pendente, 1 = concluida */
} Missao;

void iniciarHistoria();                            /* prepara as missoes  */
void mostrarIntroducao(const Personagem *jogador); /* abertura do jogo    */
void mostrarMissoes();                             /* lista as missoes    */

/* Chamada pelo mapa. Retorna 1 se o jogo acabou e 0 se continua. */
int eventoDoLugar(int lugar, Personagem *jogador, Inventario *inv);

#endif