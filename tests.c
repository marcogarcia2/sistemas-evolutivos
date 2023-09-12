#include <stdio.h>
#include <string.h>

int main() {
    int numFiles = 5; // Número de arquivos que você deseja criar

    for (int i = 1; i <= numFiles; i++) {
        char filename[100]; // Declarando filename

        // Use snprintf para criar o caminho completo do arquivo no diretório "values"
        snprintf(filename, sizeof(filename), "individuals/file%d.txt", i);

        FILE *file = fopen(filename, "w"); // Crie o arquivo com o caminho gerado

        if (file == NULL) {
            printf("Erro ao criar o arquivo %s\n", filename);
            return 1;
        }

        // Faça operações no arquivo, se necessário
        // ...

        fclose(file); // Feche o arquivo quando terminar de usá-lo
    }

    return 0;
}
