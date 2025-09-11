#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <memory.h>

#include "cabecalho.h"

#define MAX(X,Y)((X > Y) ? (X) : (Y))
#define MIN(X,Y)((X < Y) ? (X) : (Y))

int main()
{
    ler_dados("i1000.txt");
    //testar_dados("");

	Solucao s;
    double tem_tot, tem_mel;
	AG(100, 10, 500, 10, 600, s, tem_tot, tem_mel);
	printf("\n\FO: %d\tTM: %.2f\tTT: %.2f\n", s.fo, tem_mel, tem_tot);

    delete[] vet_qtd_conf;
    for(int i = 0; i < num_ids; i++)
        delete[] mat_conflitos[i];
    delete[] mat_conflitos;
    return 0;
}

// Definições e funções para o Algoritmo Genetico

void mutacao(Solucao& s)
{
    int pt, pos;
    pt = rand() % num_pts;
    do
        pos = rand() % num_pos;
    while (pos == s.vet_sol[pt]);
    s.vet_sol[pt] = pos;
    calcular_fo(s);
}

void crossover(const int& p1, const int& p2, const int& f1, const int& f2)
{
    int p = 1 + rand() % (num_pts - 1);
    for (int i = 0; i < p; i++)
    {
        vet_populacao[f1].vet_sol[i] = vet_populacao[p1].vet_sol[i];
        vet_populacao[f2].vet_sol[i] = vet_populacao[p2].vet_sol[i];
    }
    for (int i = p; i < num_pts; i++)
    {
        vet_populacao[f1].vet_sol[i] = vet_populacao[p2].vet_sol[i];
        vet_populacao[f2].vet_sol[i] = vet_populacao[p1].vet_sol[i];
    }
    calcular_fo(vet_populacao[f1]);
    calcular_fo(vet_populacao[f2]);
}

void AG(const int& tam_pop, const int& per_eli, const int& num_cru, const int& pro_mut,
        const double& tem_max, Solucao& s, double& tem_tot, double& tem_mel)
{
    clock_t h;
    h = clock();
    for (int i = 0; i < tam_pop; i++)
        heu_const_ale_gul(vet_populacao[i]);
    ordenar(tam_pop);
    memcpy(&s, &vet_populacao[0], sizeof(Solucao));
    tem_tot = ((double)clock() - h) / CLOCKS_PER_SEC;
    tem_mel = tem_tot;
    int elite = (per_eli / 100.00) * tam_pop;
    int qtd_eli = MAX(1, rand() % elite);
    printf("FO: %d\tTempo: %.2f\n", vet_populacao[0].fo, tem_mel);
    int qtd_sol = tam_pop;
    while (tem_tot < tem_max)
    {
        int p1, p2, pos_fil;
        pos_fil = tam_pop;
        for (int i = 0; i < num_cru; i++)
        {
            p1 = rand() % qtd_eli;
            do
                p2 = rand() % tam_pop;
            while (p2 == p1);
            crossover(p1, p2, pos_fil, pos_fil + 1);
            qtd_sol += 2;
            if (vet_populacao[pos_fil].fo > s.fo)
            {
                memcpy(&s, &vet_populacao[pos_fil], sizeof(Solucao));
                tem_mel = ((double)clock() - h) / CLOCKS_PER_SEC;
                printf("FO: %d\tTempo: %.2f\n", s.fo, tem_mel);
            }
            if (vet_populacao[pos_fil + 1].fo > s.fo)
            {
                memcpy(&s, &vet_populacao[pos_fil + 1], sizeof(Solucao));
                tem_mel = ((double)clock() - h) / CLOCKS_PER_SEC;
                printf("FO: %d\tTempo: %.2f\n", s.fo, tem_mel);
            }
            if (rand() % 101 < pro_mut)
            {
                mutacao(vet_populacao[pos_fil]);
                qtd_sol++;
                if (vet_populacao[pos_fil].fo > s.fo)
                {
                    memcpy(&s, &vet_populacao[pos_fil], sizeof(Solucao));
                    tem_mel = ((double)clock() - h) / CLOCKS_PER_SEC;
                    printf("FO: %d\tTempo: %.2f\n", s.fo, tem_mel);
                }
            }
            if (rand() % 101 < pro_mut)
            {
                mutacao(vet_populacao[pos_fil + 1]);
                qtd_sol++;
                if (vet_populacao[pos_fil + 1].fo > s.fo)
                {
                    memcpy(&s, &vet_populacao[pos_fil + 1], sizeof(Solucao));
                    tem_mel = ((double)clock() - h) / CLOCKS_PER_SEC;
                    printf("FO: %d\tTempo: %.2f\n", s.fo, tem_mel);
                }
            }
            pos_fil += 2;
        }
        ordenar(tam_pop + num_cru * 2);
        tem_tot = ((double)clock() - h) / CLOCKS_PER_SEC;
    }
    printf("\nQTD SOL: %d\n\n", qtd_sol);
}

void ordenar(const int& tamanho)
{
    Solucao aux;
    int flag = 1;
    while(flag)
    {
        flag = 0;
        for (int i = 0; i < tamanho - 1; i++)
        {
            if (vet_populacao[i].fo < vet_populacao[i + 1].fo)
            {
                flag = 1;
                memcpy(&aux, &vet_populacao[i], sizeof(Solucao));
                memcpy(&vet_populacao[i], &vet_populacao[i + 1], sizeof(Solucao));
                memcpy(&vet_populacao[i + 1], &aux, sizeof(Solucao));
            }
        }
    }
}

// Heuristicas construtivas

void gerar_vizinha(Solucao& s)
{
    int pt, pos;
    pt = rand() % num_pts;
    do
        pos = rand() % num_pos;
    while (pos == s.vet_sol[pt]);
    s.vet_sol[pt] = pos;
}

void heu_const_ale(Solucao& s)
{
    for (int i = 0; i < num_pts; i++)
        s.vet_sol[i] = rand() % num_pos;
}

void heu_const_gul(Solucao& s)
{
    memset(&s.vet_sol, -1, sizeof(s.vet_sol));
    for (int i = 0; i < num_pts; i++)
    {
        int melhor_pos;
        int melhor_id = -1;
        int min_conflitos = num_pts;
        for (int j = 0; j < num_pos; j++)
        {
            int id = get_id(i, j);
            int conflitos = 0;
            for (int k = 0; k < vet_qtd_conf[id]; k++)
            {
                int pt = get_ponto(mat_conflitos[id][k]);
                int pos = get_posicao(mat_conflitos[id][k]);
                if (s.vet_sol[pt] == pos)
                    conflitos++;
            }
            if ((conflitos < min_conflitos) || ((conflitos == min_conflitos) && vet_qtd_conf[id] < vet_qtd_conf[melhor_id]))
            {
                min_conflitos = conflitos;
                melhor_id = id;
                melhor_pos = j;
            }
        }
        s.vet_sol[i] = melhor_pos;
    }
}

void heu_const_ale_gul(Solucao& s)
{
    int id, pt, pos, melhor, conflitos, min_conflitos;
    int sel, aux, vet_pts[MAX_PTS];
    for (int i = 0; i < num_pts; i++)
        vet_pts[i] = i;
    memset(&s.vet_sol, -1, sizeof(s.vet_sol));
    for (int i = 0; i < num_pts; i++)
    {
        sel = i + rand() % (num_pts - i);
        //---
        min_conflitos = num_pts;
        for (int j = 0; j < num_pos; j++)
        {
            conflitos = 0;
            id = get_id(vet_pts[sel], j);
            for (int k = 0; k < vet_qtd_conf[id]; k++)
            {
                pt = get_ponto(mat_conflitos[id][k]);
                pos = get_posicao(mat_conflitos[id][k]);
                if (s.vet_sol[pt] == pos)
                    conflitos++;
            }
            if (conflitos < min_conflitos)
            {
                min_conflitos = conflitos;
                melhor = j;
            }
        }
        s.vet_sol[vet_pts[sel]] = melhor;
        //---
        aux = vet_pts[i];
        vet_pts[i] = vet_pts[sel];
        vet_pts[sel] = aux;
    }
    calcular_fo(s);
}

// Heuristicas de refinamento

void heu_BL_rand(Solucao& s, const int& iter)
{
    int mel_fo = s.fo;
    int pos1, pos2, fo_aux, ponto;
    while(true)
    {
        int flag = 1;

        for(int i = 0; i < iter; i++)
        {

            ponto = rand() % num_pts;
            pos2 = s.vet_sol[ponto];
            do
            {
                pos1 = rand() % num_pos;
            }
            while(pos1 == pos2);
            fo_aux = s.fo;
            s.vet_sol[ponto] = pos1;
            calcular_fo(s);

            if(s.fo > mel_fo)
            {
                mel_fo = s.fo;
                flag = 0;
            }
            else
            {
                s.fo = fo_aux;
                s.vet_sol[ponto] = pos2;
            }
        }
        if(flag) break;
    }
}

void heu_BL_MM(Solucao& s)
{
    int mel_fo = s.fo;
    while(true)
    {
        int mel_ponto, mel_pos;
        int flag = 0;
        for(int i = 0; i < num_pts; i++)
        {
            int pos_ori = s.vet_sol[i];
            for(int j = 0; j < num_pos; j++)
            {
                s.vet_sol[i] = j;
                calcular_fo(s);
                if(s.fo > mel_fo)
                {
                    mel_fo = s.fo;
                    mel_ponto = i;
                    mel_pos = j;
                    flag = 1;
                }
            }
            s.vet_sol[i] = pos_ori;
        }
        s.fo = mel_fo;
        printf(" %d ", s.fo);
        if(flag) s.vet_sol[mel_ponto] = mel_pos;
        else break;

    }
}

void heu_BL_PM(Solucao& s)
{
    int mel_fo = s.fo;

    int mel_ponto, mel_pos;
    INICIO : ;
    for(int i = 0; i < num_pts; i++)
    {
        int pos_ori = s.vet_sol[i];
        int fo_ori =  s.fo;
        for(int j = 0; j < num_pos; j++)
        {
            s.vet_sol[i] = j;
            calcular_fo(s);
            if(s.fo > mel_fo)
            {
                mel_fo = s.fo;
                goto INICIO;
            }
            else
            {
                s.vet_sol[i] = pos_ori;
                s.fo = fo_ori;
            }
        }
        s.fo = mel_fo;
    }
}

// Funções destinadas a solução

void calcular_fo(Solucao& s)
{
    int id, pt, pos, conflito;
    s.fo = num_pts;                                  // considera que todos os pontos estao livres (sem conflito)
    for (int i = 0; i < num_pts; i++)                // para cada ponto
    {
        id = get_id(i, s.vet_sol[i]);                // pega o id da posicao candidata selecionada para o ponto na solucao
        conflito = 0;                                // considera que o ponto esta livre (nao esta em conflito)
        for (int j = 0; j < vet_qtd_conf[id]; j++)   // para cada possivel conflito do id (posicao selecionada do ponto)
        {
            pt = get_ponto(mat_conflitos[id][j]);    // pega o ponto do possivel conflito
            pos = get_posicao(mat_conflitos[id][j]); // pega a posicao candidata do possivel conflito
            if (s.vet_sol[pt] == pos)                // verifica se na solucao para o ponto foi selecionada a posicao candidata confitante
            {
                conflito = 1;                        // o ponto nao esta livre, ha pelo menos um conflito
                break;
            }
        }
        s.fo -= conflito;                            // atualiza a fo
    }
}

// recebe um ponto (0 a num_pts - 1) e uma posicao candidata (0 a num_pos - 1) e retorna o id (0 a num_ids - 1)
int get_id(const int& pt, const int& pos)
{
    return (pt * num_pos) + pos;
}

// recebe um id (0 a num_ids - 1) e retorna o ponto (0 a num_pts - 1)
int get_ponto(const int& id)
{
    return id / num_pos;
}

// recebe um id (0 a num_ids - 1) e retorna a posicao candidata (0 a num_pos - 1)
int get_posicao(const int& id)
{
    return id % num_pos;
}

void escrever_solucao(const Solucao& s, char* arq)
{
    FILE* f;
    if (arq == "")
        f = stdout;
    else
        f = fopen(arq, "w");
    fprintf(f, "\n\nFO: %d\n", s.fo);
    for (int i = 0; i < num_pts; i++)
        fprintf(f, "Ponto: %d\tPos: %d\n", i + 1, s.vet_sol[i] + 1); // os ids no arquivo de entrada comecam em 1 (ao inves de 0)
    if (arq != "")
        fclose(f);
}

void testar_dados(char* arq)
{
    FILE* f;
    if (arq == "")
        f = stdout;
    else
        f = fopen(arq, "w");
    fprintf(f, "%d\n%d", num_pts, num_pos);
    for(int i = 0; i < num_ids; i++)
    {
        fprintf(f, "\n%d\n", vet_qtd_conf[i]);
        for(int j = 0; j < vet_qtd_conf[i]; j++)
            fprintf(f, "%d ", mat_conflitos[i][j] + 1); // os ids no arquivo de entrada comecam em 1 (ao inves de 0)
    }
    if (arq != "")
        fclose(f);
}

void ler_dados(char* arq)
{
    FILE* f = fopen(arq, "r");
    fscanf(f, "%d %d", &num_pts, &num_pos);
    num_ids = num_pts * num_pos;
    vet_qtd_conf = new int[num_ids];
    mat_conflitos = new int*[num_ids];
    for(int i = 0; i < num_ids; i++)
    {
        fscanf(f, "%d", &vet_qtd_conf[i]);
        mat_conflitos[i] = new int[vet_qtd_conf[i]];
        for(int j = 0; j < vet_qtd_conf[i]; j++)
        {
            fscanf(f, "%d", &mat_conflitos[i][j]);
            mat_conflitos[i][j]--; // os ids no arquivo de entrada comecam em 1 (ao inves de 0)
        }
    }
    fclose(f);
}