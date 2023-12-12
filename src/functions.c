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




// Funcionalidade 1
/*
    target é uma matriz de WIDTH x HEIGHT x 3 elementos, ela irá guardar os valores RGB
    de cada pixel da nossa imagem alvo. 
*/

void func1(void) {

    srand(time(NULL));
    clock_t fim, ini = clock();
    char filename[25];    

    // Abre o arquivo e realiza a leitura dos valores
    FILE *src = fopen("individuals/target.txt", "r");
    if (src == NULL) {
        printf("Error while opening file \"target.txt\".\n");
        exit(0);
    }
    int width, height;
    fscanf(src, "%d %d\n", &width, &height);

    // create_target();
    // create_world();
    // create_best();

    // mudar essas constantes para variáveis acima

    //* Alocando toda a memória necessária em um único loop (eficiência) *//
    int ***target = (int***)malloc(WIDTH * sizeof(int**));
    Individual ***world = (Individual***)malloc(WIDTH * sizeof(Individual**));
    Individual **best = (Individual**)malloc(WIDTH * sizeof(Individual*));
    for (int i = 0; i < WIDTH; i++){
        target[i] = (int**)malloc(HEIGHT * sizeof(int*));
        world[i] = (Individual**)malloc(HEIGHT * sizeof(Individual*));
        best[i] = (Individual*)malloc(HEIGHT * sizeof(Individual));
        //best é a matriz que irá guardar os melhores indivíduos a cada geração
        for(int j = 0; j < HEIGHT; j++){
            target[i][j] = (int*)malloc(3 * sizeof(int)); // target é a matriz alvo RGB
            world[i][j] = (Individual*)malloc(POP_SIZE * sizeof(Individual)); //Agora, world[i][j] é uma população.
        }
    }

    /*  
        target é a matriz alvo RGB;
        world é uma matriz tal que world[i][j] é uma população de POP_SIZE indivíduos
        best é uma matriz que irá guardar os melhores indivíduos de cada geração      
    */

    // Lendo a matriz alvo
    int a = 0, b = 0; // Lê primeiro da esquerda para a direita, depois de cima para baixo
    while (fscanf(src, "%d %d %d\n", &target[a][b][0], &target[a][b][1], &target[a][b][2]) == 3){
        b++;
        if(b % HEIGHT == 0){
            b = 0;
            a++;
        }
        if (a == WIDTH) break;
    }
    fclose(src);


    //Inicializando o mundo com valores aleatórios
    for (int i = 0; i < WIDTH; i++){
        for (int j = 0; j < HEIGHT; j++){
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

    // Escrevendo a imagem aleatória
    FILE *file = fopen("individuals/file0.txt", "w");
    if (file == NULL){
        printf("Error while creating file individuals/file0.txt");
        exit(1);
    }
    write_ind_matrix(file, best, WIDTH, HEIGHT, 3);
    fclose(file);

    // Percorrendo world para determinar os melhores
    Individual bestOne;
    for (int i = 0; i < WIDTH; i++){
        for (int j = 0; j < HEIGHT; j++){
            bestOne = world[i][j][0];
            for (int k = 1; k < POP_SIZE; k++){

                //
                if (bestOne.totalFitness > world[i][j][k].totalFitness)
                    bestOne = world[i][j][k];
                
            }
            best[i][j] = bestOne;
        }
    }

    // Algoritmo Evolutivo
    Individual child;
    
    for (int generation = 0; generation < MAX_GENERATIONS; generation++) {
        printf("Gen %d\n", generation);
        // Vamos percorrer toda a imagem 
        for (int i = 0; i < WIDTH; i++){
            for (int j = 0; j < HEIGHT; j++){

                // Sobre cada pixel, vamos iterar sobre a população
                for (int k = 0; k < POP_SIZE/2; k++){
                    
                    // world[i][j][k] é o indivíduo da iteração atual
                    int parent1index = 2 * k;
                    int parent2index = 2 * k + 1;
                    crossover(&world[i][j][parent1index], &world[i][j][parent2index], &child);
                    mutate(&child);
                    evaluateFitness(&child, target[i][j]);

                    int random_index = rand() % POP_SIZE;

                    // Agora que temos a criança, vamos testá-la
                    if (k % 2 == 0) {
                        // Quanto menor o fitness melhor
                        if (child.totalFitness < world[i][j][random_index].totalFitness){
                            // Se a cor da criança for melhor que o ind. da iteração, copio a cor 
                            world[i][j][random_index] = child;

                            if (child.totalFitness < best[i][j].totalFitness)
                                // Se a cor da criança for melhor que a cor do melhor, copio a cor
                                best[i][j] = child;
                        }
                    } 
                    else{
                        // Quanto menor o fitness melhor
                        if (child.totalFitness < world[i][j][random_index].totalFitness){
                            // Se a cor da criança for melhor que o ind. da iteração, copio a cor 
                            world[i][j][random_index] = child;

                            if (child.totalFitness < best[i][j].totalFitness) 
                                // Se a cor da criança for melhor que a cor do melhor, copio a cor
                                best[i][j] = child;
                        }  
                    }
                }
            }
        }

        // Ao final da geração, salvo a matriz dos melhores indivíduos em um arquivo
        snprintf(filename, sizeof(filename), "individuals/file%d.txt", generation + 1);
        FILE *file = fopen(filename, "w"); 
        if (file == NULL){
            printf("Error while creating file %s\n", filename);
            exit(0);
        }
        write_ind_matrix(fopen(filename, "w"), best, WIDTH, HEIGHT, 3);
        fclose(file);
    }
    
    // Fim do Algoritmo Genético, exibindo o resultado

    // Calculando o tempo decorrido em todo o processo
    fim = clock() - ini;
    printf("Time ellapsed: %.2f seconds\n", (float)fim/CLOCKS_PER_SEC);
    //printf("Best Fitness: ");

    //* Liberando a memória de todas as alocações *//
    for (int i = 0; i < WIDTH; i++) {
        for (int j = 0; j < HEIGHT; j++) {
            free(target[i][j]);
            free(world[i][j]);
        }
        free(target[i]);
        free(world[i]);
        free(best[i]);
    }
    free(target);
    free(world);
    free(best);

    return;
}
