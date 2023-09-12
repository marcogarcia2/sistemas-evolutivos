from PIL import Image
import os

# Abra o arquivo de dados para leitura
with open('../individuals/file0.txt', 'r') as file:
    lines = file.readlines()

# Crie uma lista para armazenar os valores RGB
pixels = []

# Analise as linhas do arquivo e converta para valores RGB
for line in lines:
    values = line.strip().split() 
    print(values)
    r, g, b = map(int, values)     # Converta os valores para inteiros
    pixels.extend((r, g, b))       # Adicione os valores à lista

# Crie uma imagem usando os valores RGB
width = 960  # Largura da imagem (3 pixels neste exemplo)
height = 600  # Altura da imagem (número de linhas)
image = Image.new('RGB', (width, height))
image.putdata(pixels)

# Salve a imagem
image.save('imagem0.png')
