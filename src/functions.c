#include "functions.h"

// Função para avaliar a aptidão de um indivíduo
void evaluateFitness(Individual *individual, const int target[3]) {
    individual->totalFitness = 0;
    for (int i = 0; i < 3; i++){
        individual->fitness[i] = abs(individual->rgb[i] - target[i]);
        individual->totalFitness += individual->fitness[i];
    }
}

// Função para realizar cruzamento por média entre dois indivíduos
void crossover(const Individual *parent1, const Individual *parent2, Individual *child) {
    for (int i = 0; i < 3; i++){
        child->rgb[i] = (parent1->rgb[i] + parent2->rgb[i]) / 2;
    }
}

// Função para aplicar mutação a um indivíduo
void mutate(Individual *individual) {
    for (int c = 0; c < 3; c++){
        float chance = (float)(rand() % 100) / 100;
        if (chance <= MUTATION_RATE){
            individual->rgb[c] = rand() % 256; 
        }   
    }
}

void copy_3d_matrix(int ***dest, int ***src, int width, int height, int depth) {
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            for (int k = 0; k < depth; k++) {
                dest[i][j][k] = src[i][j][k];
            }
        }
    }
}

void write_ind_matrix(FILE *file, Individual **matrix, int width, int height){
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            for (int k = 0; k < 3; k++) {
                fprintf(file, "%d ", matrix[i][j].rgb[k]);
            }
            fprintf(file, "\n");
        }
    }
}
