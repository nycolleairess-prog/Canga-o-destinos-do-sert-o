#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "inventario.h"

// ------------------------------------------------------------
// CATALOGO DE ITENS
// Todos os itens que podem aparecer no jogo.
// Formato de cada linha: {nome, descricao, tipo, poder}
// Para criar um item novo, basta adicionar uma linha aqui.
// ------------------------------------------------------------
static const Item catalogo[] = {

    // ----- Armas (poder = dano) -----
    {"Peixeira", "Faca longa e afiada, muito usada pelos cangaceiros.", ITEM_ARMA, 12},
    {"Pistola velha", "Arma antiga e enferrujada, mas ainda dispara.", ITEM_ARMA, 15},
    {"Facao enferrujado", "Serve para abrir caminho na caatinga e para se defender.", ITEM_ARMA, 10},
    {"Bacamarte", "Espingarda de cano largo que espalha chumbo a curta distancia.", ITEM_ARMA, 20},
    {"Rifle Mauser antigo", "Rifle de cano longo, raro e muito poderoso.", ITEM_ARMA, 25},
    {"Estilingue", "Arma simples de madeira e borracha, boa para caca e sustos.", ITEM_ARMA, 5},

    // ----- Bebidas (poder = vida recuperada) -----
    {"Cabaca de agua", "Cabaca seca que guarda agua fresquinha.", ITEM_BEBIDA, 20},
    {"Moringa de barro", "Mantem a agua fria mesmo no sol forte do sertao.", ITEM_BEBIDA, 30},
    {"Garapa de cana", "Caldo de cana doce e gelado, enche o corpo de energia.", ITEM_BEBIDA, 15},

    // ----- Comidas (poder = vida recuperada) -----
    {"Carne de sol", "Carne salgada e seca ao sol, comida forte de viagem.", ITEM_COMIDA, 30},
    {"Farinha de mandioca", "Farinha grossa que sustenta o viajante por muito tempo.", ITEM_COMIDA, 15},
    {"Rapadura", "Doce de cana, pequena e muito energetica.", ITEM_COMIDA, 20},
    {"Queijo coalho", "Queijo firme, bom de comer puro ou assado.", ITEM_COMIDA, 20},
    {"Pacoca", "Doce de carne seca e farinha, feito no pilao.", ITEM_COMIDA, 15},
    {"Umbu", "Fruta do sertao, azedinha e cheia de agua.", ITEM_COMIDA, 10},

    // ----- Remedios (poder = vida recuperada) -----
    {"Garrafada de ervas", "Remedio caseiro feito com raizes e folhas da caatinga.", ITEM_REMEDIO, 40},
    {"Folha de babosa", "Planta que ajuda a curar cortes e queimaduras.", ITEM_REMEDIO, 15},
    {"Faixa de pano limpo", "Pano para cobrir ferimentos e estancar o sangue.", ITEM_REMEDIO, 20},

    // ----- Equipamentos (poder = defesa) -----
    {"Chapeu de couro", "Chapeu de aba larga, simbolo dos cangaceiros.", ITEM_EQUIPAMENTO, 6},
    {"Gibao de couro", "Casaco grosso de couro, protege contra espinhos e golpes.", ITEM_EQUIPAMENTO, 12},
    {"Alpercata", "Sandalia de couro, leve e resistente para andar na caatinga.", ITEM_EQUIPAMENTO, 3},

    // ----- Ferramentas (poder = 0) -----
    {"Bolsa de couro", "Bolsa resistente para carregar suas coisas.", ITEM_FERRAMENTA, 0},
    {"Lamparina", "Lampiao de querosene que ilumina as noites escuras.", ITEM_FERRAMENTA, 0},
    {"Corda de sisal", "Corda forte, util para escalar, amarrar e puxar.", ITEM_FERRAMENTA, 0},
    {"Bussola velha", "Instrumento antigo que ainda aponta o norte.", ITEM_FERRAMENTA, 0},

    // ----- Tesouros (poder = 0) -----
    {"Moeda de ouro antiga", "Moeda rara, talvez escondida por algum cangaceiro.", ITEM_TESOURO, 0},
    {"Terco de madeira", "Terco simples, carregado por muitos romeiros do sertao.", ITEM_TESOURO, 0}
};

// Quantidade de itens do catalogo (calculada sozinha,
// entao nao precisa mudar nada ao criar itens novos)
#define TOTAL_ITENS (int)(sizeof(catalogo) / sizeof(catalogo[0]))

// ------------------------------------------------------------
// FUNCOES AUXILIARES (so usadas aqui dentro)
// ------------------------------------------------------------

// Limpa o que ficou na entrada depois de um scanf
static void limparEntrada() {
    int caractere;
    while ((caractere = getchar()) != '\n' && caractere != EOF) {
    }
}

// Devolve o nome do tipo do item para mostrar na tela
static const char *nomeDoTipo(TipoItem tipo) {
    switch (tipo) {
        case ITEM_ARMA:        return "Arma";
        case ITEM_COMIDA:      return "Comida";
        case ITEM_BEBIDA:      return "Bebida";
        case ITEM_REMEDIO:     return "Remedio";
        case ITEM_EQUIPAMENTO: return "Equipamento";
        case ITEM_FERRAMENTA:  return "Ferramenta";
        case ITEM_TESOURO:     return "Tesouro";
        default:               return "Desconhecido";
    }
}

// ------------------------------------------------------------
// FUNCOES DO INVENTARIO
// ------------------------------------------------------------

// Deixa o inventario vazio
void iniciarInventario(Inventario *inv) {
    inv->quantidade = 0;
}

// Sorteia um item do catalogo
Item sortearItem() {
    static int sorteioIniciado = 0;

    // Prepara o rand() so na primeira vez, para os sorteios
    // nao serem iguais toda vez que o jogo abrir
    if (!sorteioIniciado) {
        srand((unsigned int)time(NULL));
        sorteioIniciado = 1;
    }

    // rand() % N gera um numero de 0 ate N-1, que e a posicao no catalogo
    int posicao = rand() % TOTAL_ITENS;
    return catalogo[posicao];
}

// Guarda um item no inventario
int adicionarItem(Inventario *inv, Item item) {
    // Se nao houver espaco, nao guarda
    if (inv->quantidade >= CAPACIDADE_INVENTARIO) {
        return 0;
    }

    inv->itens[inv->quantidade] = item;
    inv->quantidade++;
    return 1;
}

// Remove o item de uma posicao e puxa os seguintes para tras
int removerItem(Inventario *inv, int posicao) {
    int i;

    if (posicao < 0 || posicao >= inv->quantidade) {
        return 0;
    }

    for (i = posicao; i < inv->quantidade - 1; i++) {
        inv->itens[i] = inv->itens[i + 1];
    }

    inv->quantidade--;
    return 1;
}

// Procura um item pelo nome
int temItem(const Inventario *inv, const char *nome) {
    int i;

    for (i = 0; i < inv->quantidade; i++) {
        if (strcmp(inv->itens[i].nome, nome) == 0) {
            return 1;
        }
    }

    return 0;
}

// Mostra os dados de um item
void mostrarItem(Item item) {
    printf("%s [%s]\n", item.nome, nomeDoTipo(item.tipo));
    printf("   %s\n", item.descricao);

    // O significado do "poder" muda de acordo com o tipo
    switch (item.tipo) {
        case ITEM_ARMA:
            printf("   Dano: %d\n", item.poder);
            break;

        case ITEM_COMIDA:
        case ITEM_BEBIDA:
        case ITEM_REMEDIO:
            printf("   Recupera: %d de vida\n", item.poder);
            break;

        case ITEM_EQUIPAMENTO:
            printf("   Defesa: %d\n", item.poder);
            break;

        default:
            break;
    }
}

// Mostra todos os itens guardados
void mostrarInventario(const Inventario *inv) {
    int i;

    printf("\n========== INVENTARIO (%d/%d) ==========\n",
           inv->quantidade, CAPACIDADE_INVENTARIO);

    if (inv->quantidade == 0) {
        printf("\nSua bolsa esta vazia.\n");
        return;
    }

    for (i = 0; i < inv->quantidade; i++) {
        printf("\n%d - ", i + 1);
        mostrarItem(inv->itens[i]);
    }
}

// Abre um bau: sorteia o item e tenta guardar no inventario
void abrirBau(Inventario *inv) {
    printf("\nVoce abriu um bau velho e empoeirado...\n");

    Item item = sortearItem();

    printf("\nVoce encontrou:\n");
    mostrarItem(item);

    if (adicionarItem(inv, item)) {
        printf("\nItem guardado na bolsa! (%d/%d)\n",
               inv->quantidade, CAPACIDADE_INVENTARIO);
    } else {
        printf("\nSua bolsa esta cheia! Voce precisou deixar o item para tras.\n");
    }
}

// Menu do inventario: ver os itens e descartar algum
void menuInventario(Inventario *inv) {
    int opcao;
    int numero;

    do {
        mostrarInventario(inv);

        printf("\n1 - Descartar item");
        printf("\n2 - Voltar");
        printf("\n\nEscolha uma opcao: ");

        // Verifica se o jogador digitou um numero
        if (scanf("%d", &opcao) != 1) {
            printf("\nEntrada invalida! Digite um numero.\n");
            opcao = 0;
        }
        limparEntrada();

        switch (opcao) {

            case 1:
                if (inv->quantidade == 0) {
                    printf("\nNao ha nada para descartar.\n");
                    break;
                }

                printf("\nNumero do item (0 para cancelar): ");

                if (scanf("%d", &numero) != 1) {
                    numero = 0;
                }
                limparEntrada();

                // O jogador ve a lista a partir do 1, mas o vetor comeca no 0
                if (numero == 0) {
                    printf("\nNenhum item foi descartado.\n");
                } else if (removerItem(inv, numero - 1)) {
                    printf("\nItem descartado.\n");
                } else {
                    printf("\nNumero invalido!\n");
                }
                break;

            case 2:
                printf("\nFechando o inventario...\n");
                break;

            default:
                printf("\nOpcao invalida! Tente novamente.\n");
                break;
        }

    } while (opcao != 2);
}