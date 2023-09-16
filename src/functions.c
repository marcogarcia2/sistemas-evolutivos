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
    /*
    // definir algum padrão aleatório para herdar os genes
    for (int i = 0; i < 3; i++){
        if (i == 0) child->rgb[i] = parent1->rgb[i];
        else if (i == 1) child->rgb[i] = parent2->rgb[i];
        else{
            if (rand() % 2 == 0) child->rgb[i] = parent1->rgb[i];
            else child->rgb[i] = parent2->rgb[i];
        }
    }
    */
}

// Função para aplicar mutação a um indivíduo
void mutate(Individual *individual) {
    for (int c = 0; c < 3; c++)
        if ((float)(rand() % 10) / 100 <= MUTATION_RATE)
            individual->rgb[c] = rand() % 256;    
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
