#include <stdio.h>
#include "mapa.h"

// Funcao que mostra os lugares do mapa
void mostrarMapa() {
    printf("\n========== MAPA DO SERTAO ==========\n");

    printf("\n1 - Vila do Sertao");
    printf("\n2 - Caatinga");
    printf("\n3 - Rio Seco");
    printf("\n4 - Acampamento dos Cangaceiros");
    printf("\n5 - Voltar ao menu principal");

    printf("\n\nEscolha um lugar para explorar: ");
}

// Funcao que permite explorar os lugares
void explorarMapa() {
    int opcao;
    int caractere;

    // O mapa continua aparecendo ate o jogador voltar
    do {
        mostrarMapa();

        // Verifica se foi digitado um numero
        if (scanf("%d", &opcao) != 1) {
            printf("\nEntrada invalida! Digite um numero.\n");
            opcao = 0;
        }

        // Limpa o que ficou depois da digitacao
        while ((caractere = getchar()) != '\n' &&
               caractere != EOF) {
        }

        // Mostra o lugar escolhido
        switch (opcao) {

            case 1:
                printf("\n========== VILA DO SERTAO ==========\n");
                printf("\nVoce chegou a uma pequena vila.");
                printf("\nOs moradores vivem em casas simples.");
                printf("\nO lugar parece tranquilo.\n");
                break;

            case 2:
                printf("\n========== CAATINGA ==========\n");
                printf("\nVoce entrou na caatinga.");
                printf("\nO sol esta forte e a vegetacao e seca.");
                printf("\nTenha cuidado durante a caminhada.\n");
                break;

            case 3:
                printf("\n========== RIO SECO ==========\n");
                printf("\nVoce encontrou um rio quase sem agua.");
                printf("\nO calor do sertao deixou o lugar seco.");
                printf("\nTalvez existam recursos por perto.\n");
                break;

            case 4:
                printf("\n===== ACAMPAMENTO DOS CANGACEIROS =====\n");
                printf("\nVoce encontrou um acampamento escondido.");
                printf("\nAlguns cangaceiros estao reunidos.");
                printf("\nE melhor ficar atento.\n");
                break;

            case 5:
                printf("\nVoltando ao menu principal...\n");
                break;

            default:
                printf("\nOpcao invalida! Tente novamente.\n");
                break;
        }

        // Espera o jogador apertar ENTER
        if (opcao >= 1 && opcao <= 4) {
            printf("\nPressione ENTER para continuar...");
            getchar();
        }

    } while (opcao != 5);
}