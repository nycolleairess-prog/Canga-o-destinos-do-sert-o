#include <stdio.h>
#include "mapa/mapa.h"
#include "historia/historia.h"

// Funcao que mostra o menu principal
void mostrarMenu() {
    printf("\n========================================\n");
    printf("       CANGACO: DESTINOS DO SERTAO\n");
    printf("========================================\n");

    printf("\n1 - Iniciar jogo");
    printf("\n2 - Instrucoes");
    printf("\n3 - Creditos");
    printf("\n4 - Sair");

    printf("\n\nEscolha uma opcao: ");
}

// Funcao que apresenta as instrucoes do jogo
void mostrarInstrucoes() {
    printf("\n========== INSTRUCOES ==========\n");

    printf("\nExplore o sertao nordestino.");
    printf("\nConheca personagens e cumpra missoes.");
    printf("\nEnfrente desafios durante sua jornada.");
    printf("\nAdministre seus itens e recursos.");
    printf("\nTome decisoes que influenciam sua aventura.");

    printf("\n\nPressione ENTER para voltar ao menu...");
    getchar();
}

// Funcao que apresenta os integrantes do projeto
void mostrarCreditos() {
    printf("\n========== CREDITOS ==========\n");

    printf("\nProjeto: Cangaco: Destinos do Sertao");
    printf("\n\nDesenvolvedores:");
    printf("\nNycolle - Menu principal e integracao");
    printf("\nEmilly - Historia, dialogos e missoes");
    printf("\nJoao - Personagens e batalhas");
    printf("\nArthur - Mapa e exploracao");
    printf("\nPedro - Inventario, itens e recursos");

    printf("\n\nPressione ENTER para voltar ao menu...");
    getchar();
}

// Funcao que inicia a aventura
void iniciarJogo() {
    Personagem jogador;
    Inventario inv;

    printf("\n========== INICIO DA AVENTURA ==========\n");

    iniciarInventario(&inv);        // Pedro: bolsa vazia
    escolherPersonagem(&jogador);   // Joao: escolha da classe
    iniciarHistoria();              // Emilly: prepara as missoes
    mostrarIntroducao(&jogador);    // Emilly: comeco da historia
    explorarMapa(&jogador, &inv);   // Arthur: mapa com a historia em cada lugar
}

// Funcao principal do jogo
int main() {
    int opcao;
    int caractere;

    // Repete o menu ate o jogador escolher sair
    do {
        mostrarMenu();

        // Verifica se o jogador digitou um numero
        if (scanf("%d", &opcao) != 1) {
            printf("\nEntrada invalida! Digite um numero.\n");
            opcao = 0;
        }

        // Limpa os caracteres que ficaram na entrada
        // depois que o jogador digitou uma opcao
        while ((caractere = getchar()) != '\n' &&
               caractere != EOF) {
        }

        // Executa a opcao escolhida pelo jogador
        switch (opcao) {

            case 1:
                iniciarJogo();
                break;

            case 2:
                mostrarInstrucoes();
                break;

            case 3:
                mostrarCreditos();
                break;

            case 4:
                printf("\nObrigado por jogar! Ate a proxima!\n");
                break;

            default:
                printf("\nOpcao invalida! Tente novamente.\n");
                break;
        }

    } while (opcao != 4);

    return 0;
}