#ifndef PRCP_H_INCLUDED
#define PRCP_H_INCLUDED

#define MAX_PTS 14000 // maximo de pontos a serem rotulados

// Definição da solução para o problema
typedef struct tSolucao
{
    int vet_sol[MAX_PTS];
    int fo;
}Solucao;

// Dados globais do problema
int num_pts;         // numero de pontos
int num_pos;         // numero de posicoes candidatas por ponto
int num_ids;         // numero total (num_pts * num_pos) de identificadores (posicoes possiveis)
int* vet_qtd_conf;   // vetor com a quantidade de conflitos de cada posicao
int** mat_conflitos; // matriz com o "id" dos conflitos de cada posicao

// Definições e funções para o Algoritmo Genetico

#define MAX_POP 20000
Solucao vet_populacao[MAX_POP];
void mutacao(Solucao& s);
void crossover(const int& p1, const int& p2, const int& f1, const int& f2);
void AG(const int& tam_pop, const int& per_eli, const int& num_cru, const int& pro_mut,
        const double& tem_max, Solucao& s, double& tem_tot, double& tem_mel);
void ordenar(const int& tamanho);

// Heuristicas construtivas

void gerar_vizinha(Solucao& s);
void heu_const_ale(Solucao& s);
void heu_const_gul(Solucao& s);
void heu_const_ale_gul(Solucao& s);

// Heuristicas de refinamento

void heu_BL_rand(Solucao& s, const int& iter);
void heu_BL_MM(Solucao& s);
void heu_BL_PM(Solucao& s);

// Funções destinadas a solução

void calcular_fo(Solucao& s);
int get_ponto(const int& id);
int get_posicao(const int& id);
int get_id(const int& pt, const int& pos);
void escrever_solucao(const Solucao& s, char* arq);
void testar_dados(char* arq);
void ler_dados(char* arq);

#endif
