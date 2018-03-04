#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "funcoes.h"

int main() {
    system("clear");
    srand(time(NULL));

    int qtd_jogadores;
    printf("quantos jogadores?\n");
    scanf("%d",&qtd_jogadores);

    Jogador jogadores[qtd_jogadores];
    Jogador mesa;

    int i;
    for (i = 0; i < qtd_jogadores; i++) {
        iniJogadores(&jogadores[i],JOGADOR);
        printf("nome jogador %d\n",i+1);
        scanf("%s",jogadores[i].nome);
    }
    iniJogadores(&mesa,MESA);

    system("clear");

    float bolada = 0;

    int conf = 1;

    /* laço para o jogo continuar enquanto o usuario quiser */

    while(conf == 1){

        /* nesse laço ele pede a aposta de cada jogador, sendo que o jogador deve possuir um saldo superior a 0,
         caso o jogador digite -1 ele fica sem participar dessa rodada, o valor da sua aposta se torna 0,
         assim ele não interfere durante o jogo, já se o jogador digitar um valor superior a 0 ele entra na partida */
        i = 0;
        int jogadores_sem_saldo = 0;

        system("clear");
        while (i < qtd_jogadores){

            if(jogadores[i].saldo > 0){
                printf("%s\ndigite sua aposta ou -1 para não participar dessa rodada.\nseu saldo atual é de: %.2f\n", jogadores[i].nome, jogadores[i].saldo);
                scanf("%f",&jogadores[i].aposta);
                if(jogadores[i].aposta <= jogadores[i].saldo){
                    if(jogadores[i].aposta > 0)
                        bolada += jogadores[i].aposta;
                    else
                        jogadores[i].aposta = 0;

                }else{
                    jogadores[i].aposta = 0;
                    printf("saldo insuficiente\n");
                    i--;
                }

            }
            if (jogadores[i].saldo <= 0){
                jogadores_sem_saldo += 1;
            }
            i++;
            printf("\n");
        }

        system("clear");
        rodada(jogadores,&mesa,qtd_jogadores,bolada);

        printf("\n\nmais uma rodada? 1 -para sim   2- para não\n");

        scanf("%d",&conf);

        /* aqui os dados dos jogadores são zerados */
        for (int i = 0; i < qtd_jogadores; i++) {
            zerar_jogador(&jogadores[i]);
        }
        zerar_jogador(&mesa);
        bolada = 0;



        if (jogadores_sem_saldo == qtd_jogadores){
            conf = 0;
        }
    }

    system("clear");

    for(i = 0; i < qtd_jogadores; i++){
        printf("jogador: %s || saldo final: %.2f\n", jogadores[i].nome, jogadores[i].saldo);
    }

    return 0;
}

