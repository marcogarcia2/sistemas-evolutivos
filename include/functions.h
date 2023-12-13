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
//Alocação
int ***create_target(int width, int height); // Função que cria o indivíduo perfeito alvo
Individual ***create_world(int width, int height); // Função que cria o mundo
Individual **create_best(int width, int height); // Função que cria a matriz de melhores indivíduos

//Desalocação
void destroy_world(Individual**** world_ref, int width, int height);
void destroy_target(int**** target_ref, int width, int height);
void destroy_best(Individual*** best_ref, int width);

//Inicialização
void initialize_world(Individual ***world, Individual **best, int ***target, int width, int height); // Função que incializa o mundo com valores aleatórios

/*---------------- Funções relacionadas a arquivos ---------------*/
void read_target(int ***target, FILE *src, int width, int height); // Função que lê a matriz alvo a partir de um arquivo txt


/*---------------- Funções relacionadas à evolução em si -------------*/
void evolution(Individual ***world, int ***target, Individual **best, int width, int height, char *filename, char *fitness_file); //Engloba o processo evolutivo em si

// Função que percorre o mundo e encontra os melhores
void find_best(Individual **best, Individual ***world, int width, int height);

// Função para avaliar a aptidão de um indivíduo
void evaluateFitness(Individual *individual, const int target[3]);

// Função para realizar cruzamento por média entre dois indivíduos
void crossover(const Individual *parent1, const Individual *parent2, Individual *child);

// Função para aplicar mutação a um indivíduo
void mutate(Individual *individual);

// Função que calcula a média dos Fitness da matriz best
int fitness_mean(Individual **best, int width, int height);

/*----------------- Funções auxiliares ----------*/
// Função que escreve os dados da matriz em um arquivo
void write_ind_matrix(FILE *file, Individual **matrix, int width, int height, int depth);


#endif
