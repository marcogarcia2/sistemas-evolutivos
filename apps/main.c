#include "functions.h"

/*
    target é uma matriz de width x height x 3 elementos, ela irá guardar os valores RGB
    de cada pixel da nossa imagem alvo. 
*/

int main(int argc, char *argv[]) {

    if (POP_SIZE == 1){
        printf("POP_SIZE must be greater than 1.\n");
        return 1;
    }

    // Definindo algumas variáveis
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
    int ***target = create_target(width, height); //Matriz que representa a img, onde cada índice/pixel é um int[3] (RGB)
    Individual ***world = create_world(width, height); //Matriz tal que world[i][j] é uma população de POP_SIZE indivíduos
    Individual **best = create_best(width, height); //Matriz que irá guardar os melhores indivíduos de cada geração

    // Lendo a matriz alvo e guardando em target
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

    // Este arquivo salvará as médias dos fitness
    FILE *fitness_file = fopen("fitness.txt", "w");
    if (fitness_file == NULL){
        printf("Error while creating file fitness.txt");
        exit(1);
    }

    // Percorrendo world para determinar os melhores
    first_find_best(best, world, width, height);

    // Escrevendo o fitness médio da geração 0
    fprintf(fitness_file, "%d,", fitness_mean(best, width, height));



    //* Algoritmo Genético *//
    
    // Variáveis auxiliares
    int parent1index, parent2index;
    Individual child;
    
    for (int generation = 1; generation <= MAX_GENERATIONS; generation++) {

        // Imprimindo a geração atual
        print_generation(generation);
        
        // Matando os piores indivíduos
        genocide(world, width, height);

        // Vamos percorrer toda a imagem 
        for (int i = 0; i < width; i++){
            for (int j = 0; j < height; j++){

                
                // Vamos iterar sobre cada lugar vazio da população
                for (int k = POP_SIZE/2; k < POP_SIZE; k++){

                    // Vamos escolher dois pais aleatórios e diferentes entre si
                    parent1index = rand() % POP_SIZE/2;
                    parent2index = rand() % POP_SIZE/2;
                    while (parent1index == parent2index)
                        parent2index = rand() % POP_SIZE/2;

                    // Agora que temos pais diferentes, vamos gerar a criança
                    crossover(&world[i][j][parent1index], &world[i][j][parent2index], &child);
                    mutate(&child);
                    evaluate_fitness(&child, target[i][j]);

                    // Agora que temos a criança, vamos inserí-la na população
                    world[i][j][k] = child;

                    // A criança pode ser melhor que o melhor indivíduo da geração
                    if (child.totalFitness < best[i][j].totalFitness){
                        best[i][j] = child;
                    }
                }
            }
        }

        // Ao final da geração, salvo a matriz dos melhores indivíduos em um arquivo
        snprintf(filename, sizeof(filename), "individuals/file%d.txt", generation);
        FILE *file = fopen(filename, "w"); 
        if (file == NULL){
            printf("Error while creating file %s\n", filename);
            return 1;
        }
        write_ind_matrix(fopen(filename, "w"), best, width, height, 3);
        fclose(file);

        // Escrevendo o fitness médio
        fprintf(fitness_file, "%d,", fitness_mean(best, width, height));
    }
    
    // Fim do Algoritmo Genético

    // Calculando o tempo decorrido em todo o processo
    fim = clock() - ini;
    printf("Time ellapsed: %.2f seconds\n", (float)fim/CLOCKS_PER_SEC);
    //printf("Best Fitness: ");

    // Liberando a memória de todas as alocações
    destroy_world(&world, width, height);
    destroy_target(&target, width, height);
    destroy_best(&best, width);
    fclose(fitness_file);

    return 0;
}
