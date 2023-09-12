#include "functions.h"

#define WIDTH 960
#define HEIGHT 600
#define POP_SIZE 100
#define MAX_GENERATIONS 50
#define MUTATION_RATE 0.1

// Estrutura para representar um indivíduo
typedef struct _individual{
    int ***rgb;                 // Matriz de três dimensões com os valores RGB
    int fitness;              // Valor de aptidão, quanto menor melhor
} Individual;

// Função para calcular a diferença entre duas cores RGB
int colorDifference(int color1[3], int color2[3]) {
    int diff = 0;
    for (int i = 0; i < 3; i++) {
        diff += abs(color1[i] - color2[i]);
    }
    return diff;
}

// Função para avaliar a aptidão de um indivíduo
int evaluateFitness(Individual *individual, int ***target) {
    int totalDifference = 0;
    for (int i = 0; i < WIDTH; i++) {
        for (int j = 0; j < HEIGHT; j++) {
            totalDifference += colorDifference(individual->rgb[i][j], target[i][j]);   
        }
    }
    return totalDifference;
}

// Função para realizar cruzamento por média entre dois indivíduos
void crossover(Individual *parent1, Individual *parent2, Individual *child) {
    for (int i = 0; i < WIDTH; i++) {
        for (int j = 0; j < HEIGHT; j++) {
            for (int k = 0; k < 3; k++) {
                child->rgb[i][j][k] = (parent1->rgb[i][j][k] + parent2->rgb[i][j][k]) / 2;
            }
        }
    }
}

// Função para aplicar mutação a um indivíduo
void mutate(Individual *individual) {
    for (int i = 0; i < WIDTH; i++) {
        for (int j = 0; j < HEIGHT; j++) {
            for (int k = 0; k < 3; k++) {
                if ((float)rand() / RAND_MAX < MUTATION_RATE) {
                    individual->rgb[i][j][k] = rand() % 256;
                }
            }
        }
    }
}

int main(int argc, char *argv[]) {

    srand(time(NULL));

    // Declaração das variáveis //*---*//*---*//*---*//*---*//*---*//*---*//*---*//
    int ***target = alloc_3d_matrix(WIDTH, HEIGHT, 3); // Matriz alvo RGB
    Individual *population = (Individual*)malloc(sizeof(Individual) * POP_SIZE); // population é um array de indivíduos
    Individual bestIndividual, child;  // Melhor indivíduo encontrado e filho
    int bestFitness = INT_MAX;    // Inicialize com um valor alto
    int arq_num = 1;
    char filename[25];
    //*---*//*---*//*---*//*---*//*---*//*---*//*---*//*---*//*---*//*---*//*---*//


    // Abre o arquivo e realiza a leitura dos valores
    FILE *arq = fopen("values.txt", "r");
    if (arq == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }
    int a = 0, b = 0;
    while (fscanf(arq, " (%d, %d, %d)\n", &target[a][b][0], &target[a][b][1], &target[a][b][2]) == 3){
        b++;
        if(b % HEIGHT == 0){
            b = 0;
            a++;
        }
    }
    fclose(arq); // fecha o arquivo

    // Inicialize a população com valores aleatórios
    for (int i = 0; i < POP_SIZE; i++) {
        population[i].rgb = alloc_3d_matrix(WIDTH, HEIGHT, 3);
        for (int j = 0; j < WIDTH; j++) {
            for (int k = 0; k < HEIGHT; k++) {
                for (int l = 0; l < 3; l++) {
                    
                    population[i].rgb[j][k][l] = rand() % 256;
                }
            }
        }
        population[i].fitness = evaluateFitness(&population[i], target);
    }

    // Algoritmo evolutivo
    bestIndividual.rgb = alloc_3d_matrix(WIDTH, HEIGHT, 3);
    child.rgb = alloc_3d_matrix(WIDTH, HEIGHT, 3);
    for (int generation = 0; generation < MAX_GENERATIONS; generation++) {
        for (int i = 0; i < POP_SIZE; i++) {
            
            // Criando um filho diferente a cada iteração, com pais aleatórios dentre a população
            int parent1Index = rand() % POP_SIZE;
            int parent2Index = rand() % POP_SIZE;
            crossover(&population[parent1Index], &population[parent2Index], &child);
            mutate(&child);
            child.fitness = evaluateFitness(&child, target);

            // Quanto menor o fitness, melhor o indivíduo
            if (child.fitness < population[i].fitness) {

                // Se o filho for melhor que o indivíduo da iteração, substitua-o
                copy_3d_matrix(population[i].rgb, child.rgb, WIDTH, HEIGHT, 3); 
                population[i].fitness = child.fitness;
                
                // Se o filho for melhor que o melhor indivíduo, substitua-o
                if (child.fitness < bestFitness) {
                    printf("Best Individual %d\n", arq_num);
                    copy_3d_matrix(bestIndividual.rgb, child.rgb, WIDTH, HEIGHT, 3);
                    bestFitness = child.fitness;

                    // Salvando o novo melhor indivíduo em um arquivo
                    snprintf(filename, sizeof(filename), "individuals/file%d.txt", arq_num++);
                    FILE *file = fopen(filename, "w"); 
                    if (file == NULL){
                        printf("Erro ao criar o arquivo %s\n", filename);
                        return 1;
                    }
                    write_3d_matrix(file, bestIndividual.rgb, WIDTH, HEIGHT, 3);
                    fclose(file);
                }
            } 
        }
    }

    // Fim do Algoritmo Genético, exibindo o resultado
    printf("Melhor indivíduo encontrado com fitness %d:\n", bestFitness);
    /*for (int i = 0; i < WIDTH; i++) {
        for (int j = 0; j < HEIGHT; j++) {
            printf("(%d, %d, %d) ", bestIndividual.rgb[i][j][0], bestIndividual.rgb[i][j][1], bestIndividual.rgb[i][j][2]);
        }
        printf("\n");
    }*/

    // Liberando a memória de todas as alocações
    free_3d_matrix(target, WIDTH, HEIGHT);
    for(int i = 0; i < POP_SIZE; i++)
        free_3d_matrix(population[i].rgb, WIDTH, HEIGHT);
    free(population);
    free_3d_matrix(bestIndividual.rgb, WIDTH, HEIGHT);
    free_3d_matrix(child.rgb, WIDTH, HEIGHT);

    return 0;
}
