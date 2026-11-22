#ifndef PERSONAGEM_H
#define PERSONAGEM_H

#include "inventario.h"

// Dados do personagem controlado pelo jogador
typedef struct {
    char nome[MAX_NOME];
    int vida;
    int vidaMaxima;
    int ataque;
    int defesa;
} Personagem;

// Dados de um inimigo encontrado durante a aventura
typedef struct {
    char nome[MAX_NOME];
    int vida;
    int ataque;
    int defesa;
} Inimigo;

// Mostra as classes disponiveis e prepara o personagem
void escolherPersonagem(Personagem *jogador);

// Mostra os atributos do personagem
void mostrarPersonagem(const Personagem *jogador);

// Prepara os dados de um inimigo
void iniciarInimigo(Inimigo *inimigo, const char *nome, int vida, int ataque, int defesa);

// Realiza uma batalha por turnos
void batalhar(Personagem *jogador, Inventario *inv, Inimigo *inimigo);

#endif
