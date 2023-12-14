#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define POP_SIZE 4
#define MAX_GENERATIONS 50
#define MUTATION_RATE 10 // escolher entre 0 e 100

// Estrutura para representar um indivíduo
typedef struct _individual{
    int rgb[3];                    // Vetor que guarda os valores RGB
    int fitness[3];                // Valores de aptidão, quanto menores melhor
    int totalFitness;              // Soma das aptidões de cana canal de cor
} Individual;

/*--------------- Funções de criação, desalocação e inicialização ------------*/

// -> Alocação de memória

// Função que cria o indivíduo perfeito alvo
int ***create_target(int width, int height); 

// Função que cria o mundo
Individual ***create_world(int width, int height); 

// Função que cria a matriz de melhores indivíduos
Individual **create_best(int width, int height); 

// -> Desalocação de memória

void destroy_world(Individual**** world_ref, int width, int height);
void destroy_target(int**** target_ref, int width, int height);
void destroy_best(Individual*** best_ref, int width);

// -> Inicialização

// Função que incializa o mundo com valores aleatórios
void initialize_world(Individual ***world, Individual **best, int ***target, int width, int height); 

/*---------------- Funções relacionadas a arquivos ---------------*/

// Função que lê a matriz alvo a partir de um arquivo de texto
void read_target(int ***target, FILE *src, int width, int height); 

// Função que escreve os dados da matriz em um arquivo
void write_ind_matrix(FILE *file, Individual **matrix, int width, int height, int depth);

/*---------------- Funções relacionadas à Evolução -------------*/

// Função para realizar cruzamento entre dois indivíduos
void crossover(const Individual *parent1, const Individual *parent2, Individual *child);

// Função para aplicar mutação a um indivíduo
void mutate(Individual *individual);

// Função para avaliar a aptidão de um indivíduo
void evaluateFitness(Individual *individual, const int target[3]);

// Função que percorre o mundo e encontra os melhores
void find_best(Individual **best, Individual ***world, int width, int height);

// Função que calcula a média das aptidões da matriz best
int fitness_mean(Individual **best, int width, int height);


#endif
