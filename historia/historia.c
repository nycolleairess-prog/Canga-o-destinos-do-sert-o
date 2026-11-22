#include <stdio.h>
#include "historia.h"

Missao missoes[MAX_MISSOES];
int honra = 0;  /* sobe com boas escolhas e desce com as mas */

/* ---------- Utilidades ---------- */

void pausar() {
    char linha[10];
    printf("\n[ENTER para continuar]");
    fgets(linha, sizeof(linha), stdin);
}

void dialogo(char quem[], char fala[]) {
    printf("\n%s: \"%s\"\n", quem, fala);
}

/* Mostra duas opcoes e devolve 1 ou 2 */
int fazerEscolha(char op1[], char op2[]) {
    char linha[20];
    int e = 0;
    printf("\n  1) %s\n  2) %s\n", op1, op2);
    while (e != 1 && e != 2) {
        printf("Sua escolha: ");
        if (!fgets(linha, sizeof(linha), stdin)) return 1;
        if (sscanf(linha, "%d", &e) != 1) e = 0;
    }
    return e;
}

/* Usa a batalha do Joao: 1 = venceu, 0 = fugiu, -1 = perdeu */
int lutar(Personagem *jogador, Inventario *inv, char nome[], int vida, int ataque) {
    Inimigo inimigo;
    iniciarInimigo(&inimigo, nome, vida, ataque, 2);
    batalhar(jogador, inv, &inimigo);
    if (jogador->vida <= 0) return -1;
    if (inimigo.vida > 0) return 0;
    return 1;
}

/* ---------- Missoes ---------- */

void iniciarHistoria() {
    Missao m[MAX_MISSOES] = {
        {"Achar agua no Rio Seco", 0},
        {"Pegar o mapa na Caatinga", 0},
        {"Vencer o chefe no Acampamento", 0}
    };
    int i;
    for (i = 0; i < MAX_MISSOES; i++) missoes[i] = m[i];
    honra = 0;
}

void mostrarMissoes() {
    int i;
    printf("\n------ MISSOES ------\n");
    for (i = 0; i < MAX_MISSOES; i++)
        printf("[%c] %s\n", missoes[i].concluida ? 'X' : ' ', missoes[i].titulo);
}

/* Conclui a missao e, se era a ultima, mostra o final. Retorna 1 se acabou. */
int concluirMissao(int i, const Personagem *jogador) {
    int j;
    missoes[i].concluida = 1;
    printf("\n*** MISSAO CONCLUIDA: %s ***\n", missoes[i].titulo);

    for (j = 0; j < MAX_MISSOES; j++)
        if (!missoes[j].concluida) return 0;

    printf("\n=========== FIM ===========\n");
    if (honra > 0)
        printf("A chuva voltou, e o %s virou heroi dos cordeis!\n", jogador->nome);
    else
        printf("O coronel caiu, mas o povo teme o %s tanto quanto temia ele.\n", jogador->nome);
    return 1;
}

/* ---------- Historia ---------- */

void mostrarIntroducao(const Personagem *jogador) {
    printf("\n=== CANGACO: DESTINOS DO SERTAO ===\n\n");
    printf("O sol racha o chao do sertao. Faz meses que nao chove.\n");
    printf("Voce, um %s, chega a Vila do Sertao.\n", jogador->nome);
    dialogo("Dona Zefa", "O coronel tomou a unica agua que sobrou!");

    if (fazerEscolha("Pode contar comigo.", "E o que eu ganho?") == 1) {
        dialogo("Dona Zefa", "Que Padre Cicero te proteja!");
        honra++;
    } else {
        dialogo("Dona Zefa", "O povo nunca esquece quem ajuda...");
        honra--;
    }
    mostrarMissoes();
    pausar();
}

int eventoDoLugar(int lugar, Personagem *jogador, Inventario *inv) {
    int resultado;
    Item bacamarte = {"Bacamarte", "Espingarda de cano largo.", ITEM_ARMA, 20};
    Item cabaca = {"Cabaca de agua", "Cabaca com agua fresquinha.", ITEM_BEBIDA, 20};

    switch (lugar) {
    case 1: /* Vila do Sertao */
        dialogo("Seu Bento", "Tem um acude escondido perto do Rio Seco.");
        dialogo("Beata Maria", "Os capangas levaram um mapa para a Caatinga.");
        mostrarMissoes();
        return 0;

    case 2: /* Caatinga */
        if (missoes[1].concluida) return 0;
        dialogo("Capanga", "Para ai! Essas terras sao do coronel.");
        if (fazerEscolha("Conversar com ele", "Ameacar ele") == 1 && honra > 0) {
            dialogo("Capanga", "Minha mae mora na vila... Toma o mapa.");
            honra++;
        } else {
            resultado = lutar(jogador, inv, "Capanga", 40, 10);
            if (resultado == -1) { printf("\nGAME OVER\n"); return 1; }
            if (resultado == 0) return 0;
            adicionarItem(inv, bacamarte);
            printf("\nVoce pegou o mapa e o bacamarte do capanga!\n");
        }
        return concluirMissao(1, jogador);

    case 3: /* Rio Seco */
        if (missoes[0].concluida) return 0;
        printf("\nSeguindo os mandacarus, voce acha o acude cheio de agua!\n");
        adicionarItem(inv, cabaca);
        return concluirMissao(0, jogador);

    case 4: /* Acampamento */
        if (!missoes[1].concluida) {
            printf("\nSem o mapa, voce se perde no caminho.\n");
            return 0;
        }
        dialogo("Chefe do bando", "Entao voce e quem anda ajudando a vila...");
        resultado = lutar(jogador, inv, "Chefe do bando", 70, 14);
        if (resultado == -1) { printf("\nGAME OVER\n"); return 1; }
        if (resultado == 0) return 0;
        return concluirMissao(2, jogador);
    }
    return 0;
}