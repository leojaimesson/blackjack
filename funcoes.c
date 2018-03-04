#include "funcoes.h"
#include <stdlib.h>
#include <stdio.h>
void iniJogadores(Jogador *jog, jgd jogador) {
    jog->vetTam = 1;
    jog->vet = malloc(sizeof(int) * jog->vetTam);
    jog->total = 0;
    jog->as = 0;
    jog->saldo = 100;
    jog->aposta = 0;
    jog->maior_valor = FALSE;
    if(jogador == MESA){
        jog->nome = malloc(sizeof(char) * 4);
        jog->nome[0] = 'M'; jog->nome[1] = 'e'; jog->nome[2] = 's'; jog->nome[3] = 'a';
    }
    else {
        jog->nome = malloc(sizeof(char) * 20);
    }
}

/* nessa função é retornado as cartas na tela */
void MostrarCartas(Jogador * jog) {
    int i;

    if(jog->vet[jog->vetTam-1] == 11)
        printf("# %s recebe K - Total %d [", jog->nome, jog->total);
    else if(jog->vet[jog->vetTam-1] == 12)
        printf("# %s recebe Q - Total %d [", jog->nome, jog->total);
    else if(jog->vet[jog->vetTam-1] ==  13)
        printf("# %s recebe J - Total %d [", jog->nome, jog->total);
    else if(jog->vet[jog->vetTam-1] == 1)
        printf("# %s recebe A - Total %d [", jog->nome, jog->total);
    else
        printf("# %s recebe %d - Total %d [", jog->nome, jog->vet[jog->vetTam-1], jog->total);

    for(i = 0; i < jog->vetTam; i++){
        if(jog->vet[i] == 11)
            printf(" K");
        else if(jog->vet[i] == 12)
            printf(" Q");
        else if(jog->vet[i] ==  13)
            printf(" J");
        else if(jog->vet[i] == 1)
            printf(" A");
        else
            printf(" %d",jog->vet[i]);
    }
    printf(" ]\n");
}

/* nessa função é verificado se o jogador(mesa,jogador) ultrapassaram o limite */
boolean estourouMesa(Jogador *jog) {
    while(jog->total > 21 && jog->as != 0){
        jog->total -= 10;
        jog->as -= 1;
    }
    if(jog->total > 21)
        return TRUE;
    return FALSE;
}

/* nessa função ele adiciona as cartas no vetor e faz a contagem do total de pontos,
e ele chama a função estourou_mesa para verificar se o jogador ultrapassou 21 */

boolean addCarta(Jogador * jog, int carta) {
    jog->vet = realloc(jog->vet,sizeof(int)*(jog->vetTam));
    jog->vet[jog->vetTam-1] = carta;

    /* incrementa a quantidades de ases caso saia algum*/
    /* incrementa a quantidade total conforme a carta é adicionada*/
    if(carta == 1){
        jog->total += 11;
        jog->as++;
    }
    else if(carta > 10){
        jog->total +=  10;
    }
    else{
        jog->total += carta;
    }


    estourouMesa(jog);
    MostrarCartas(jog);

    /* incrementa o tamanho do vetor */
    if(estourouMesa(jog) == FALSE)
        jog->vetTam++;
    return estourouMesa(jog);
}


/* aqui mostra, se o jogador deseja continuar, as cartas que ele possui e o total */
void menu(int * continuar , Jogador * jog) {
    printf("\n%s [ ", jog->nome);
    int i=0;
    for(i = 0; i < jog->vetTam-1; i++){

        if(jog->vet[i] == 11)
            printf("K ");
        else if(jog->vet[i] == 12)
            printf("Q ");
        else if(jog->vet[i] ==  13)
            printf("J ");
        else if(jog->vet[i] == 1)
            printf("A ");
        else
            printf("%d ",jog->vet[i]);
    }
    printf("] total: %d\n",jog->total);
    printf("Pedir = 1, Parar = 2\n");
    scanf("%d",continuar);

}


/* nessa função caso o jogador não tenha estourado a mesa, a mesa vai tentar passar ou empatar com o jogador */

void vezMesa(Jogador * jogadores, Jogador * mesa, int qtd_jogadores) {
    int i=0;//f(jog->total <= 21) {
    while(i < qtd_jogadores){
        if(jogadores[i].total <= 21 && jogadores[i].aposta > 0){
            while(mesa->total <= jogadores[i].total && mesa->total < 21) {
                if(addCarta(mesa,(rand()%13) + 1) == TRUE)
                    break;
            }
        }
        i++;
    }

}

/* nessa função é retornado o ganhador */
void resultadoJogo(Jogador * jogadores, Jogador * mesa, int qtd_jogadores, float bolada) {

    int i = 0;
    int maior_valor = 0;

    /* nesse laço se obtem o maior resultado da rodada e armazena na variavel maior_valor*/
    for(i = 0; i < qtd_jogadores; i++) {

        if(jogadores[i].total <= 21 && jogadores[i].total > maior_valor && jogadores[i].aposta > 0){
                maior_valor = jogadores[i].total;
        }

    }


    /* aqui se marca se o jogador ou jogadores que obtiveram maior resultado durante o jogo */
    int total_vencedores = 0;
    for(i = 0; i < qtd_jogadores; i++){
        if (jogadores[i].total == maior_valor && jogadores[i].aposta > 0){
            jogadores[i].maior_valor = TRUE;
            total_vencedores += 1;
        }

    }


    /* nesse laço é verificado se a mesa ganhou ou não a partida, caso ela tenha perdido a variavel mesa_ganhou recebe FALSE */
    boolean mesa_ganhou = TRUE;
    for(i = 0; i < qtd_jogadores; i++){
        if ((jogadores[i].maior_valor == TRUE && jogadores[i].aposta > 0 && jogadores[i].total > mesa->total) || mesa->total > 21){
            mesa_ganhou = FALSE;
            break;
        }
    }


    /* aqui se mostra o vencedor na tela, sendo possivel a mesa ter ganhado, ou um ou mais jogadores terem ganhado */
    if(mesa_ganhou == TRUE){
        printf("\n* MESA GANHOU! *\n# Mesa(%d)\n",mesa->total);
        for(i = 0; i < qtd_jogadores; i++){
            if(jogadores[i].aposta > 0 && jogadores[i].saldo > 0){
                jogadores[i].saldo -= jogadores[i].aposta;
                printf("|%s(%d) saldo:%2.f |",jogadores[i].nome, jogadores[i].total, jogadores[i].saldo);
            }
        }
        printf("\n");
    }

    else{
        printf("\n* MESA PERDEU! *\n# Mesa(%d)\n# ganhadores: ",mesa->total);
        for(i = 0; i < qtd_jogadores; i++){
            if (jogadores[i].maior_valor == TRUE && jogadores[i].aposta > 0){
                jogadores[i].saldo += (bolada /total_vencedores);
                printf("|%s(%d) saldo: %2.f |",jogadores[i].nome, jogadores[i].total, jogadores[i].saldo);
            }
            if (jogadores[i].maior_valor == FALSE && jogadores[i].aposta > 0 && jogadores[i].saldo > 0){
                jogadores[i].saldo -= jogadores[i].aposta;
            }

        }
        printf("\n");
    }

}


/* nessa função é zerado os campos e vetores do jogador passado, (mesa, e jogadores) */
void zerar_jogador(Jogador * jog){
    free(jog->vet);
    jog->vetTam = 1;
    jog->total = 0;
    jog->vet = malloc(sizeof(int)*(jog->vetTam));
    jog->maior_valor = FALSE;
    jog->aposta = 0;
    jog->as = 0;

}

/* aqui ocorre as rodadas com os jogadores que iram participar da partida */
void rodada(Jogador * jogadores, Jogador * mesa, int qtd_jogadores, float bolada) {
    int continuar = 1;
    int i;
    for(i = 0; i < qtd_jogadores; i++) {
        if(jogadores[i].aposta > 0 && jogadores[i].saldo > 0){
            addCarta(&jogadores[i],(rand()%13) + 1);
            addCarta(&jogadores[i],(rand()%13) + 1);
            printf("\n");
        }
    }

    addCarta(mesa,(rand()%13) + 1);

    for(i = 0; i < qtd_jogadores; i++) {
        if(jogadores[i].aposta > 0 && jogadores[i].saldo > 0){
            menu(&continuar,&jogadores[i]);

            while(continuar == 1) {
                system("clear");
                if(addCarta(&jogadores[i],(rand()%13) + 1) == TRUE)
                    break;
                menu(&continuar,&jogadores[i]);
            }
        }
    }

    vezMesa(jogadores,mesa,qtd_jogadores);
    resultadoJogo(jogadores,mesa,qtd_jogadores,bolada);
}
