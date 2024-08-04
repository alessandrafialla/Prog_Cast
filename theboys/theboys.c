#include <stdio.h>
#include <stdlib.h>
#include "fila.h"
#include "lef.h"
#include "mundo.h"
#include "conjunto.h"

int *cria_vetor(){
    int i;
    int *vetor = malloc(N_MISSOES * sizeof(int));

    if(vetor == NULL)
        return NULL;

    for(i = 0; i < N_MISSOES; i++)
        vetor[i] = 0;

    return vetor;
}

int main()
{
    struct mundo_t w;
    struct evento_t *ev;
    int agendadas, cumpridas; /* contabilizar missoes */
    int fim_simulacao;
    int *tentativas_missoes; /*vetor para as tentativas de missoes*/

    srand(0); /* use zero, nao faca com time (0) */
    agendadas = 0;
    cumpridas = 0;

    w = cria_mundo();
    tentativas_missoes = cria_vetor();

    fim_simulacao = 0;
    while (!fim_simulacao && (ev = retira_lef(w.lef)) != NULL)
    {
        w.relogio = ev->tempo; /* Atualiza o tempo do mundo */
        switch (ev->tipo)
        {
            case CHEGA:
                chega(&w, ev->tempo, ev->dado1, ev->dado2);
            break;
            case ESPERA:
                espera(&w, ev->tempo, ev->dado1, ev->dado2);
                break;
            case DESISTE:
                desiste(&w, ev->tempo, ev->dado1, ev->dado2);
                break;
            case VIAJA:
                viaja(&w, ev->tempo, ev->dado1, ev->dado2);
                break;
            case MISSAO:
                if (missao(&w, ev->tempo, ev->dado1, tentativas_missoes))
                    cumpridas++;
                else
                    agendadas++;
                break;
            case AVISA:
                avisa(&w, ev->tempo, ev->dado2);
                break;
            case ENTRA:
                entra(&w, ev->tempo, ev->dado1, ev->dado2);
                break;
            case SAI:
                sai(&w, ev->tempo, ev->dado1, ev->dado2);
                break;
            case FIM:
                fim(&w, cumpridas, agendadas, tentativas_missoes);
                fim_simulacao = 1;
                break;
        }
        destroi_evento(ev);
    }
    return 1;
}
