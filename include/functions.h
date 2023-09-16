#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <limits.h>

#define WIDTH 960
#define HEIGHT 600
#define POP_SIZE 2
#define MAX_GENERATIONS 25
#define MUTATION_RATE 0.1

// Estrutura para representar um indivíduo
typedef struct _individual{
    int rgb[3];                    // Matriz de três dimensões com os valores RGB
    int fitness[3];                // Valores de aptidão, quanto menores melhor
    int totalFitness;              // Soma das aptidões de cana canal de cor
} Individual;

// Função para avaliar a aptidão de um indivíduo
void evaluateFitness(Individual *individual, const int target[3]);

// Função para realizar cruzamento por média entre dois indivíduos
void crossover(const Individual *parent1, const Individual *parent2, Individual *child);

// Função para aplicar mutação a um indivíduo
void mutate(Individual *individual);

// Função que aloca memória para uma matriz de três dimensões
int ***alloc_3d_matrix(int width, int height, int depth);

// Função que copia dados de uma matriz 3D para outra 
void copy_3d_matrix(int ***dest, int ***src, int width, int height, int depth);

// Função que escreve os dados da matriz em um arquivo
void write_ind_matrix(FILE *file, Individual **matrix, int width, int height);


#endif
