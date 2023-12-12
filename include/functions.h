#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define POP_SIZE 5
#define MAX_GENERATIONS 50
#define MUTATION_RATE 0.5

// Estrutura para representar um indivíduo
typedef struct _individual{
    int rgb[3];                    // Vetor que guarda os valores RGB
    int fitness[3];                // Valores de aptidão, quanto menores melhor
    int totalFitness;              // Soma das aptidões de cana canal de cor
} Individual;


// Funcionalidade 1
void func1(void);

// Funcionalidade 2
//void func2(void);

// Função para avaliar a aptidão de um indivíduo
void evaluateFitness(Individual *individual, const int target[3]);

// Função para realizar cruzamento por média entre dois indivíduos
void crossover(const Individual *parent1, const Individual *parent2, Individual *child);

// Função para aplicar mutação a um indivíduo
void mutate(Individual *individual);

// Função que escreve os dados da matriz em um arquivo
void write_ind_matrix(FILE *file, Individual **matrix, int width, int height, int depth);


#endif
