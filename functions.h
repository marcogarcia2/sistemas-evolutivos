#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <limits.h>

// Função que aloca memória para uma matriz de três dimensões
int ***alloc_3d_matrix(int width, int height, int depth);

// Função que libera a memória de uma matriz de três dimensões
void free_3d_matrix(int*** matrix, int width, int height);

// Função que copia dados de uma matriz 3D para outra 
void copy_3d_matrix(int ***dest, int ***src, int width, int height, int depth);

// Função que escreve os dados da matriz em um arquivo
void write_3d_matrix(FILE *file, int ***matrix, int width, int height, int depth);




#endif
