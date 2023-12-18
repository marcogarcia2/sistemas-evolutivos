#include "functions.h"

/*----------------- Definição da estrutura do Indivíduo ----------------------*/

// Estrutura para representar um indivíduo
// typedef struct _individual{
//     int rgb[3];                    // Vetor que guarda os valores RGB
//     int fitness[3];                // Valores de aptidão, quanto menores melhor
//     int totalFitness;              // Soma das aptidões de cana canal de cor
//     int location;
// } Individual;


/*--------------- Funções de criação, desalocação e inicialização ------------*/

// -> Alocação

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

// -> Desalocação de memória

void destroy_world(Individual**** world_ref, int width, int height){
    Individual ***world = *world_ref;

    for (int i = 0; i < width; i++){
        for (int j = 0; j < height; j++){
            free(world[i][j]);
        }
        free(world[i]);
    }
    free(world);

    world_ref = NULL;
}

void destroy_target(int**** target_ref, int width, int height){
    int ***target = *target_ref;

    for (int i = 0; i < width; i++){
        for (int j = 0; j < height; j++){
            free(target[i][j]);
        }
        free(target[i]);
    }
    free(target);

    target_ref = NULL;
}

void destroy_best(Individual*** best_ref, int width){
    Individual **best = *best_ref;

    for (int i = 0; i < width; i++){
        free(best[i]);
    }
    free(best);

    best_ref = NULL;
}

// -> Inicialização

// Função que incializa o mundo com valores aleatórios
void initialize_world(Individual ***world, Individual **best, int ***target, int width, int height){

     for (int i = 0; i < width; i++){
        for (int j = 0; j < height; j++){
            for (int k = 0; k < POP_SIZE; k++){

                for (int l = 0; l < 3; l++) 
                    // Gera valores aleatórios para cada canal de cor
                    world[i][j][k].rgb[l] = rand() % 256;

                // Compara população de pixels com o pixel correspondente na matriz alvo
                evaluate_fitness(&world[i][j][k], target[i][j]);

                // Guardando a sua localização na população
                world[i][j][k].location = k;

                // Gravando a população inicial aleatória para exibir no vídeo
                best[i][j] = world[i][j][0];
            }
        }
    }  
}

/*---------------- Funções relacionadas a arquivos ---------------*/

// Função que lê a matriz alvo a partir de um arquivo de texto
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

// Função que escreve os dados da matriz em um arquivo
void write_ind_matrix(FILE *file, Individual **matrix, int width, int height, int depth){ // Função que escreve os dados da matriz em um arquivo
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            for (int k = 0; k < depth; k++) {
                fprintf(file, "%d ", matrix[i][j].rgb[k]);
            }
            fprintf(file, "\n");
        }
    }
}

/*---------------- Funções relacionadas à Evolução -------------*/

// Função para realizar cruzamento por média entre dois indivíduos
void crossover(const Individual *parent1, const Individual *parent2, Individual *child) { 
    for (int i = 0; i < 3; i++){

        int random = rand() % 2;
        
        if (random == 0) child->rgb[i] = parent1->rgb[i];
        else child->rgb[i] = parent2->rgb[i];
    }
}

// Função para aplicar mutação a um indivíduo
void mutate(Individual *individual) { 
        
    int chance = (rand() % 100) + 1;
    //printf("chance = %d || M = %d\n", chance, (int)MUTATION_RATE*100);
    if (chance <= (unsigned int) (MUTATION_RATE*100)){

        // Mutação acontecerá em R, G ou B?
        // Para mais ou para menos?
        int x = (chance % 2 == 0) ? 1 : -1;

        for (int i = 0; i < 3; i++){

            individual->rgb[i] += MUTATION_SCALE * x; 

            if (individual->rgb[i] > 255) individual->rgb[i] = 255;
            else if (individual->rgb[i] < 0) individual->rgb[i] = 0;
        }
    }   
}

// Função para avaliar a aptidão de um indivíduo
void evaluate_fitness(Individual *individual, const int target[3]) { 
    individual->totalFitness = 0;
    for (int i = 0; i < 3; i++){
        individual->fitness[i] = abs(individual->rgb[i] - target[i]);
        individual->totalFitness += individual->fitness[i];
    }
}

// Função que percorre a população e retorna a localização do melhor indivíduo
int search_best(const Individual *population){

    int aux = population[0].totalFitness;
    int location = 0;

    for (int i = 1; i < POP_SIZE; i++){
        
        if(aux > population[i].totalFitness){
            aux = population[i].totalFitness;
            location = i;
        }

    }

    return location;
}

// Função que percorre o mundo e encontra os melhores inicialmente
void first_find_best(Individual **best, Individual ***world, int width, int height){ 
    Individual bestOne;
    for (int i = 0; i < width; i++){
        for (int j = 0; j < height; j++){
            bestOne = world[i][j][0];
            for (int k = 1; k < POP_SIZE; k++){

                // Se o fitness desse indivíduo for menor que o do melhor até então, ele é o novo melhor
                if (bestOne.totalFitness > world[i][j][k].totalFitness)
                    bestOne = world[i][j][k];
                
            }
            best[i][j] = bestOne;
        }
    }
}

// Função que calcula a média dos Fitness da matriz best
int fitness_mean(Individual **best, int width, int height){
    int mean = 0;
    for (int i = 0; i < width; i++){
        for (int j = 0; j < height; j++){
                mean += best[i][j].totalFitness;
        }
    }
    return mean / (width * height);
}
/*---------------- Funções Auxiliares -------------*/

// Função que gera um inteiro aleatório entre os números dados
int _random(int min, int max){
    return (rand() % (max - min + 1)) + min;
}

// function to swap elements
void swap(Individual *a, Individual *b) {
    Individual t = *a;
    *a = *b;
    *b = t;
}

// function to find the partition position
int partition(Individual *population, int low, int high) {

// select the rightmost element as pivot
Individual pivot = population[high];

    // pointer for greater element
    int i = (low - 1);

    // traverse each element of the array
    // compare them with the pivot
    for (int j = low; j < high; j++) {
        if (population[j].totalFitness <= pivot.totalFitness) {
            
            // if element smaller than pivot is found
            // swap it with the greater element pointed by i
            i++;
            
            // swap element at i with element at j
            swap(&population[i], &population[j]);
        }
    }

    // swap the pivot element with the greater element at i
    swap(&population[i + 1], &population[high]);

    // return the partition point
    return (i + 1);
}

void quickSort(Individual *population, int low, int high) {
    if (low < high) {
    
        // find the pivot element such that
        // elements smaller than pivot are on left of pivot
        // elements greater than pivot are on right of pivot
        int pi = partition(population, low, high);
        
        // recursive call on the left of pivot
        quickSort(population, low, pi - 1);
        
        // recursive call on the right of pivot
        quickSort(population, pi + 1, high);
    }
}

void kill(Individual *individual){

    // Setando valores inválidos para o indivíduo
    for (int i = 0; i < 3; i++){
        individual->rgb[i] = -1;
        individual->fitness[i] = -1;
    }
    individual->totalFitness = INT_MAX;
}

// Função que causa um genocídio
void genocide(Individual ***world, int width, int height){

    for (int i = 0; i < width; i++){
        for (int j = 0; j < height; j++){
            
            // Ordenando a população do melhor para o pior
            quickSort(world[i][j], 0, POP_SIZE - 1);

            // Iremos matar metade da população
            for (int k = POP_SIZE/2; k < POP_SIZE; k++){

                kill(&world[i][j][k]);
            }
        }
    }
}
