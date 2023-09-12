from PIL import Image

# Carrega a imagem
image = Image.open('noite-estrelada.jpeg')

# Obtém os valores RGB dos pixels como uma matriz
pixel_values = list(image.getdata())
width, height = image.size
print(width)
print(height)
# Exibe os valores RGB de um pixel específico (x, y)
x, y = 100, 50
print(x * width + y)
rgb_value = pixel_values[y * width + x]
# Abre o arquivo no modo de escrita
with open('temp.txt', 'w') as arquivo:
    # Escreve uma linha no arquivo
    arquivo.write(str(pixel_values))

char_1 = '['
char_2 = ']'
char_3 = '),'

with open('temp.txt', 'r') as temp_file, open('values.txt', 'w') as new_file:
    for line in temp_file:
        modified_line = line.replace(char_1, '(0')
        modified_line = line.replace(char_2, '25)')
        modified_line = line.replace(char_3, ')\n')
        new_file.write(modified_line)