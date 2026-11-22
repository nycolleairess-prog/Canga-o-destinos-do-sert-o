#include <stdio.h>
#include <string.h>
#include "personagem.h"

// Limpa o que ficou na entrada depois de um scanf
static void limparEntrada() {
    int caractere;
    while ((caractere = getchar()) != '\n' && caractere != EOF) {
    }
}

// Mostra as classes disponiveis para o jogador
void escolherPersonagem(Personagem *jogador) {
    int opcao;

    printf("\n========== ESCOLHA SUA CLASSE ==========\n");
    printf("\n1 - Vaqueiro");
    printf("\n2 - Cangaceiro");
    printf("\n3 - Curandeira");
    printf("\n4 - Rastreador");
    printf("\n\nEscolha sua classe: ");

    if (scanf("%d", &opcao) != 1) {
        opcao = 0;
    }
    limparEntrada();

    switch (opcao) {
        case 1:
            strcpy(jogador->nome, "Vaqueiro");
            jogador->vidaMaxima = 120;
            jogador->ataque = 15;
            jogador->defesa = 0;
            break;

        case 2:
            strcpy(jogador->nome, "Cangaceiro");
            jogador->vidaMaxima = 100;
            jogador->ataque = 20;
            jogador->defesa = 0;
            break;

        case 3:
            strcpy(jogador->nome, "Curandeira");
            jogador->vidaMaxima = 90;
            jogador->ataque = 10;
            jogador->defesa = 0;
            break;

        case 4:
            strcpy(jogador->nome, "Rastreador");
            jogador->vidaMaxima = 95;
            jogador->ataque = 18;
            jogador->defesa = 0;
            break;

        default:
            printf("\nOpcao invalida! Vaqueiro selecionado.\n");
            strcpy(jogador->nome, "Vaqueiro");
            jogador->vidaMaxima = 120;
            jogador->ataque = 15;
            jogador->defesa = 0;
            break;
    }

    jogador->vida = jogador->vidaMaxima;
    printf("\nClasse escolhida: %s\n", jogador->nome);
    mostrarPersonagem(jogador);
}

// Mostra os dados do personagem
void mostrarPersonagem(const Personagem *jogador) {
    printf("\n========== PERSONAGEM ==========\n");
    printf("\nClasse: %s", jogador->nome);
    printf("\nVida: %d/%d", jogador->vida, jogador->vidaMaxima);
    printf("\nAtaque: %d", jogador->ataque);
    printf("\nDefesa: %d\n", jogador->defesa);
}

// Prepara os dados de um inimigo
void iniciarInimigo(Inimigo *inimigo, const char *nome, int vida, int ataque, int defesa) {
    strcpy(inimigo->nome, nome);
    inimigo->vida = vida;
    inimigo->ataque = ataque;
    inimigo->defesa = defesa;
}

// Procura a maior defesa entre os equipamentos do inventario
static int calcularDefesa(const Inventario *inv) {
    int i;
    int defesa = 0;

    for (i = 0; i < inv->quantidade; i++) {
        if (inv->itens[i].tipo == ITEM_EQUIPAMENTO &&
            inv->itens[i].poder > defesa) {
            defesa = inv->itens[i].poder;
        }
    }

    return defesa;
}

// Procura o maior dano entre as armas do inventario
static int calcularAtaque(const Personagem *jogador, const Inventario *inv) {
    int i;
    int ataque = jogador->ataque;

    for (i = 0; i < inv->quantidade; i++) {
        if (inv->itens[i].tipo == ITEM_ARMA &&
            inv->itens[i].poder > ataque) {
            ataque = inv->itens[i].poder;
        }
    }

    return ataque;
}

// Permite usar comida, bebida ou remedio durante a batalha
static int usarItem(Personagem *jogador, Inventario *inv) {
    int i;
    int numero;

    printf("\n========== ITENS DE CURA ==========\n");

    for (i = 0; i < inv->quantidade; i++) {
        if (inv->itens[i].tipo == ITEM_COMIDA ||
            inv->itens[i].tipo == ITEM_BEBIDA ||
            inv->itens[i].tipo == ITEM_REMEDIO) {
            printf("\n%d - %s (recupera %d de vida)",
                   i + 1, inv->itens[i].nome, inv->itens[i].poder);
        }
    }

    printf("\n\nDigite 0 para cancelar.");
    printf("\nEscolha um item: ");

    if (scanf("%d", &numero) != 1) {
        numero = 0;
    }
    limparEntrada();

    if (numero == 0) {
        printf("\nVoce nao usou nenhum item.\n");
        return 0;
    }

    numero--;

    if (numero < 0 || numero >= inv->quantidade) {
        printf("\nNumero invalido!\n");
        return 0;
    }

    if (inv->itens[numero].tipo != ITEM_COMIDA &&
        inv->itens[numero].tipo != ITEM_BEBIDA &&
        inv->itens[numero].tipo != ITEM_REMEDIO) {
        printf("\nEsse item nao pode recuperar vida.\n");
        return 0;
    }

    jogador->vida += inv->itens[numero].poder;

    if (jogador->vida > jogador->vidaMaxima) {
        jogador->vida = jogador->vidaMaxima;
    }

    printf("\nVoce usou %s e recuperou vida.\n", inv->itens[numero].nome);
    removerItem(inv, numero);
    return 1;
}

// Realiza uma batalha por turnos
void batalhar(Personagem *jogador, Inventario *inv, Inimigo *inimigo) {
    int opcao;
    int defendendo;
    int dano;

    printf("\n========== BATALHA ==========");
    printf("\nUm inimigo apareceu: %s!\n", inimigo->nome);

    while (jogador->vida > 0 && inimigo->vida > 0) {
        defendendo = 0;

        printf("\n--------------------------------");
        printf("\n%s: %d de vida", jogador->nome, jogador->vida);
        printf("\n%s: %d de vida", inimigo->nome, inimigo->vida);
        printf("\n\n1 - Atacar");
        printf("\n2 - Defender");
        printf("\n3 - Usar item");
        printf("\n4 - Fugir");
        printf("\n\nEscolha uma acao: ");

        if (scanf("%d", &opcao) != 1) {
            opcao = 0;
        }
        limparEntrada();

        switch (opcao) {
            case 1:
                dano = calcularAtaque(jogador, inv) - inimigo->defesa;
                if (dano < 1) {
                    dano = 1;
                }
                inimigo->vida -= dano;
                printf("\nVoce atacou e causou %d de dano!\n", dano);
                break;

            case 2:
                defendendo = 1;
                printf("\nVoce se preparou para defender o proximo ataque.\n");
                break;

            case 3:
                usarItem(jogador, inv);
                break;

            case 4:
                printf("\nVoce fugiu da batalha.\n");
                return;

            default:
                printf("\nOpcao invalida! Tente novamente.\n");
                continue;
        }

        if (inimigo->vida <= 0) {
            inimigo->vida = 0;
            break;
        }

        dano = inimigo->ataque - calcularDefesa(inv);
        if (defendendo) {
            dano -= 5;
        }
        if (dano < 1) {
            dano = 1;
        }

        jogador->vida -= dano;
        if (jogador->vida < 0) {
            jogador->vida = 0;
        }

        printf("\n%s atacou e causou %d de dano!\n", inimigo->nome, dano);
    }

    if (jogador->vida > 0) {
        printf("\nVoce venceu a batalha!\n");
    } else {
        printf("\nVoce foi derrotado!\n");
    }
}
