# Sistemas Evolutivos
## Projeto da disciplina SSC0713 - Sistemas Evolutivos
Professor: Eduardo do Valle Simões

O projeto consiste na geração de imagens que evoluem a partir dos conceitos de Algoritmos Genéticos aprendidos em sala de aula. O projeto pode evoluir uma imagem do zero para uma imagem escolhida, ou fazer a mescla de duas imagens a escolha do usuário.

## Como rodar o programa
É importante que todas as imagens utilizadas sejam do formato JPEG. O projeto utiliza C para o algoritmo genético, e a parte visual é feita em Python, e utiliza as bibliotecas Pillow e OpenCV, por isso é necessário instalá-las antes de rodar o programa.

> pip install pillow
> pip install opencv-python

Primeiramente, compile os códigos em C digitando no terminal:

```make```

Posteriormente, escolha uma das funcionalidades. Se você deseja evoluir apenas uma imagem, coloque-a no diretório raiz do projeto e renomeie-a para "1.jpeg", e então digite:

```make func1```

Se você deseja realizar o merge de duas imagens, coloque ambas no diretório raiz e renomeie-as com "1.jpeg" e "2.jpeg". Após isso, digite no terminal:

```make func2```

Posteriormente, para finalmente rodar o programa, digite:

```make run```

Ao final da execução, será gerado um vídeo da evolução no diretório raiz. Para limpar todos os arquivos desta execução, digite no terminal:

```make clean```


