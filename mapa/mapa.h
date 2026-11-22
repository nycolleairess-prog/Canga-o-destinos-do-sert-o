#ifndef MAPA_H
#define MAPA_H

#include "../personagens/personagem.h"

// Mostra os lugares do mapa
void mostrarMapa();

// Permite explorar os lugares (recebe o jogador e o inventario)
void explorarMapa(Personagem *jogador, Inventario *inv);

#endif