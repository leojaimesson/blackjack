#ifndef FUNCOES_H
#define FUNCOES_H

typedef enum{FALSE,TRUE}boolean;
typedef enum{JOGADOR,MESA}jgd;

typedef struct{
    int *vet;
    int vetTam;
    int total;
    int as;
    char *nome;
    float saldo;
    float aposta;
    boolean maior_valor;
}Jogador;


void iniJogadores(Jogador *jog, jgd jogador);
void MostrarCartas(Jogador * jog);
boolean estourouMesa(Jogador *jog);
boolean addCarta(Jogador * jog, int carta);
void menu(int * continuar , Jogador * jog);
void vezMesa(Jogador * jogadores, Jogador * mesa, int qtd_jogadores);
void resultadoJogo(Jogador * jogadores, Jogador * mesa, int qtd_jogadores, float bolada);
void zerar_jogador(Jogador * jog);
void rodada(Jogador * jogadores, Jogador * mesa, int qtd_jogadores, float bolada);


#endif // FUNCOES_H
