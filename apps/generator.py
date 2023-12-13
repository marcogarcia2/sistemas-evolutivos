from PIL import Image
import os

# Obter o diretório do script Python atual
script_dir = os.path.dirname(os.path.abspath(__file__))

# Caminhos para salvar os arquivos nas pastas corretas
image_path = os.path.join(script_dir, '../1.jpeg')
target_path = os.path.join(script_dir, '../individuals/')

# Imagem desejada
image = Image.open(image_path)

# Obtém os valores RGB dos pixels como uma matriz
pixel_values = list(image.getdata())
width, height = image.size

# O programa lê primeiro da esquerda para a direita, e depois de cima para baixo
# Portanto, para saber o valor de um pixel:
# x, y = 100, 100
# print(pixel_values[width * y + x])

# Abre o arquivo no modo de escrita
with open(target_path + 'target.txt', 'w') as file:
    file.write(f"{width} {height}\n")
    for i, pixel in enumerate(pixel_values):
        # Escreve uma linha no arquivo no formato desejado (R, G, B)
        file.write(f"{pixel[0]} {pixel[1]} {pixel[2]}")
        if i < len(pixel_values) - 1:
            file.write('\n')

print("Matriz da imagem gerada com sucesso!")
print(f'Dimensões: {width}x{height}')