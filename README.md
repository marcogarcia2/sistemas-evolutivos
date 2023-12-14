# Sistemas Evolutivos
## Projeto da disciplina SSC0713 - Sistemas Evolutivos
**Professor:** Eduardo do Valle Simões

O projeto consiste na geração de imagens que evoluem a partir dos conceitos de Algoritmos Genéticos aprendidos em sala de aula. O projeto pode evoluir uma imagem do zero para uma imagem escolhida, ou fazer a mescla de duas imagens a escolha do usuário.



## Requisitos
É importante que todas as imagens utilizadas sejam do formato JPEG. O projeto utiliza ```C``` para a implementação do algoritmo genético, e ```Python``` para confeccionar o vídeo final, através das bibliotecas Pillow e OpenCV. Por isso é necessário ter essas duas linguagens instaladas no computador, além das duas bibliotecas de Python para rodar o programa.

```
pip install pillow
pip install opencv-python
```

## Como executar o projeto

Primeiramente, na pasta raiz do projeto, compile os códigos em C digitando no terminal:

```
make
```

Posteriormente, escolha uma das funcionalidades. Se você deseja evoluir apenas uma imagem, coloque-a no diretório raiz do projeto e renomeie-a para "1.jpeg", e então digite:

```
make func1
```

Se você deseja realizar o merge de duas imagens, coloque ambas no diretório raiz e renomeie-as com "1.jpeg" e "2.jpeg". Após isso, digite no terminal:

```
make func2
```

Então, para finalmente rodar o programa, digite:

```
make run
```

Ao final da execução, será gerado um vídeo da evolução no diretório raiz. Para limpar todos os arquivos desta execução, digite no terminal:

```
make clean
```

## Customizando as constantes

No arquivo ```"include/functions.h"```, existem três constantes definidas, fundamentais para o funcionamento do algoritmo genético. A fim de testar diferentes combinações, o usuário pode alterá-las da seguinte forma:

- **\#define MAX_GENERATIONS 50**
Este é o número de total de gerações, e define quantas rodadas de evolução acontecerão. Quanto maior o número de gerações, melhor será a geração final, entretanto, mais tempo será necessário para gerar o vídeo final.

- **\#define POP_SIZE 4**
Este é o número de indivíduos de uma população. Quanto maior for este número, mais rápido será a evolução. Este número deve ser sempre maior que um, pois não há como realizar um crossover com apenas um indivíduo.

- **\#define MUTATION_RATE 10**
Esta é a taxa de mutação dos indivíduos, nesse caso variando de 0 a 100. Quanto maior esta taxa, menor será a velocidade da evolução.

