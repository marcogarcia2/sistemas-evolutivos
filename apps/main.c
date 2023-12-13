#include "functions.h"

// Funcionalidade 1
/*
    target é uma matriz de width x height x 3 elementos, ela irá guardar os valores RGB
    de cada pixel da nossa imagem alvo. 
*/

int main(int argc, char *argv[]) {

    srand(time(NULL));
    clock_t fim, ini = clock();
    char filename[25];    

    // Abrindo o arquivo alvo
    FILE *src = fopen("individuals/target.txt", "r");
    if (src == NULL) {
        printf("Error while opening file \"target.txt\".\n");
        return 1;
    }

    // Lendo do cabeçalho as dimensões da imagem
    int width, height;
    fscanf(src, "%d %d\n", &width, &height);

    // Criando as matrizes para guardar os dados
    int ***target = create_target(width, height);
    Individual ***world = create_world(width, height);
    Individual **best = create_best(width, height);

    /*  
        target é a matriz alvo RGB;
        world é uma matriz tal que world[i][j] é uma população de POP_SIZE indivíduos
        best é uma matriz que irá guardar os melhores indivíduos de cada geração      
    */

    // Lendo a matriz alvo
    read_target(target, src, width, height);
    
    // Fechando o arquivo alvo
    fclose(src);


    //Inicializando o mundo com valores aleatórios
    initialize_world(world, best, target, width, height); 

    // Escrevendo a imagem aleatória
    FILE *file = fopen("individuals/file0.txt", "w");
    if (file == NULL){
        printf("Error while creating file individuals/file0.txt");
        exit(1);
    }
    write_ind_matrix(file, best, width, height, 3);
    fclose(file);

    // Percorrendo world para determinar os melhores
    Individual bestOne;
    for (int i = 0; i < width; i++){
        for (int j = 0; j < height; j++){
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
        for (int i = 0; i < width; i++){
            for (int j = 0; j < height; j++){

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
            return 1;
        }
        write_ind_matrix(fopen(filename, "w"), best, width, height, 3);
        fclose(file);
    }
    
    // Fim do Algoritmo Genético

    // Calculando o tempo decorrido em todo o processo
    fim = clock() - ini;
    printf("Time ellapsed: %.2f seconds\n", (float)fim/CLOCKS_PER_SEC);
    //printf("Best Fitness: ");

    // Liberando a memória de todas as alocações
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
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

    return 0;
}
