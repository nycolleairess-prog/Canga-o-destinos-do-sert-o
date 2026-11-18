#ifndef INVENTARIO_H
#define INVENTARIO_H

// Tamanhos usados no modulo
#define MAX_NOME 40
#define MAX_DESCRICAO 100
#define CAPACIDADE_INVENTARIO 15

// Tipos de item do jogo
typedef enum {
    ITEM_ARMA,
    ITEM_COMIDA,
    ITEM_BEBIDA,
    ITEM_REMEDIO,
    ITEM_EQUIPAMENTO,
    ITEM_FERRAMENTA,
    ITEM_TESOURO
} TipoItem;

// Um item do jogo
// poder: dano (arma), vida recuperada (comida, bebida, remedio)
//        ou defesa (equipamento). Nos outros tipos fica 0.
typedef struct {
    char nome[MAX_NOME];
    char descricao[MAX_DESCRICAO];
    TipoItem tipo;
    int poder;
} Item;

// O inventario do jogador: uma lista de itens e quantos ja existem nela
typedef struct {
    Item itens[CAPACIDADE_INVENTARIO];
    int quantidade;
} Inventario;

// Deixa o inventario vazio (chamar uma vez, no inicio do jogo)
void iniciarInventario(Inventario *inv);

// Sorteia um item qualquer do catalogo
Item sortearItem();

// Guarda um item no inventario (retorna 1 se deu certo, 0 se estiver cheio)
int adicionarItem(Inventario *inv, Item item);

// Tira o item da posicao indicada, comecando em 0 (retorna 1 se deu certo, 0 se a posicao for invalida)
int removerItem(Inventario *inv, int posicao);

// Verifica se o jogador tem um item pelo nome (retorna 1 se tem, 0 se nao tem)
int temItem(const Inventario *inv, const char *nome);

// Mostra os dados de um item na tela
void mostrarItem(Item item);

// Mostra todos os itens do inventario
void mostrarInventario(const Inventario *inv);

// Abre um bau: sorteia um item e guarda no inventario
void abrirBau(Inventario *inv);

// Menu para o jogador ver e descartar itens
void menuInventario(Inventario *inv);

#endif
