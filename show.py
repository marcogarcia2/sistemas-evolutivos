from PIL import Image

# Lista para armazenar as triplas RGB lidas do arquivo
pixel_values = []

# Abra o arquivo de triplas RGB para leitura
with open('values.txt', 'r') as file:
    for line in file:
        # Remova os caracteres não numéricos da linha e divida-a em uma lista de valores
        values = [int(val) for val in line.replace('(', '').replace(')', '').replace(',', '').split()]
        # Verifique se há três valores (R, G e B)
        if len(values) == 3:
            pixel_values.append(tuple(values))

# Crie uma nova imagem com base nas triplas RGB
width = 960  # Largura da imagem
height = 600  # Altura da imagem
image = Image.new('RGB', (width, height))

# Preencha a imagem com os pixels com base nas triplas RGB lidas
for x in range(width):
    for y in range(height):
        pixel_index = y * width + x
        if pixel_index < len(pixel_values):
            pixel_color = pixel_values[pixel_index]
            image.putpixel((x, y), pixel_color)

# Salve a imagem gerada
image.save('output.png', 'PNG')
