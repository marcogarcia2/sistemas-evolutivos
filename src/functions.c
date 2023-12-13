#include "functions.h"

// Função que cria o indivíduo perfeito alvo
int ***create_target(int width, int height){

    int ***matrix = (int***)malloc(width * sizeof(int**));
    
    for (int i = 0; i < width; i++){
        matrix[i] = (int**)malloc(height * sizeof(int*));
        for(int j = 0; j < height; j++){
            matrix[i][j] = (int*)malloc(3 * sizeof(int));
        }
    }

    return matrix;
}

// Função que cria o mundo
Individual ***create_world(int width, int height){
    
    Individual ***matrix = (Individual***)malloc(width * sizeof(Individual**));
    
    for (int i = 0; i < width; i++){
        matrix[i] = (Individual**)malloc(height * sizeof(Individual*));
        for(int j = 0; j < height; j++){
            matrix[i][j] = (Individual*)malloc(POP_SIZE * sizeof(Individual));
        }
    }

    return matrix;
}

// Função que cria a matriz de melhores indivíduos
Individual **create_best(int width, int height){
        
    Individual **matrix = (Individual**)malloc(width * sizeof(Individual*));
    
    for (int i = 0; i < width; i++){
        matrix[i] = (Individual*)malloc(height * sizeof(Individual));
    }

    return matrix;
}

// Função que lê a matriz alvo
void read_target(int ***target, FILE *src, int width, int height){
    int a = 0, b = 0; // Lê primeiro da esquerda para a direita, depois de cima para baixo

        while (fscanf(src, "%d %d %d\n", &target[a][b][0], &target[a][b][1], &target[a][b][2]) == 3){
            b++;
            if(b % height == 0){
                b = 0;
                a++;
            }
            if (a == width) break;
        }
}

void initialize_world(Individual ***world, Individual **best, int ***target, int width, int height){

     for (int i = 0; i < width; i++){
        for (int j = 0; j < height; j++){
            for (int k = 0; k < POP_SIZE; k++){

                for (int l = 0; l < 3; l++) 
                    // Gera valores aleatórios para cada canal de cor
                    world[i][j][k].rgb[l] = rand() % 256;

                // Compara população de pixels com o pixel correspondente na matriz alvo
                evaluateFitness(&world[i][j][k], target[i][j]);

                // Gravando a população inicial aleatória para exibir no vídeo
                best[i][j] = world[i][j][0];
            }
        }
    }  
}


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

// Função que escreve os dados da matriz em um arquivo
void write_ind_matrix(FILE *file, Individual **matrix, int width, int height, int depth){
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            for (int k = 0; k < depth; k++) {
                fprintf(file, "%d ", matrix[i][j].rgb[k]);
            }
            fprintf(file, "\n");
        }
    }
}





