#include "functions.h"

int*** alloc_3d_matrix(int width, int height, int depth){

    int ***matrix = (int***)malloc(width * sizeof(int**));
    for (int i = 0; i < width; i++) {
        matrix[i] = (int**)malloc(height * sizeof(int*));
        for (int j = 0; j < height; j++) {
            matrix[i][j] = (int*)malloc(depth * sizeof(int));
        }
    }

    return matrix;
}

void free_3d_matrix(int*** matrix, int width, int height){

    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            free(matrix[i][j]);
        }
        free(matrix[i]);
    }
    free(matrix);
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

void write_3d_matrix(FILE *file, int ***matrix, int width, int height, int depth){
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            for (int k = 0; k < depth; k++) {
                fprintf(file, "%d ", matrix[i][j][k]);
            }
            fprintf(file, "\n");
        }
    }
}
