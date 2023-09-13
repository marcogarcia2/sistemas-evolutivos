# Sistemas Evolutivos
## Projeto da disciplina SSC0713 - Sistemas Evolutivos
Professor: Eduardo do Valle Simões

O projeto consiste na geração de imagens que evoluem a partir dos conceitos aprendidos em sala, para ...

## Como rodar o programa
Primeiramente, escolhe-se uma imagem para a qual deseja-se criar a evolução. A princípio, escolhi o quadro "Noite Estrelada", de Van Gogh. Coloque a imagem no mesmo diretório do projeto, e então, no script generator.py, substitua o nome do arquivo na linha 4, para que o programa rode perfeitamente. Após isso, modifique as constantes WIDTH e HEIGHT no arquivo main.c, com as dimensões nova imagem.

Após isso, execute o comando `make all` para compilar, e verifique se as dimensões fornecidas pela saída estão de acordo com as dimensões da imagem. Para rodar, finalmente, execute `make run`, e o algoritmo genético irá começar.

Todos os melhores indivíduos serão salvos na pasta "/individuals", 
