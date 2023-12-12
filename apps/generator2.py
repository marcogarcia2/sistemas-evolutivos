from PIL import Image
import os

# Obter o diretório do script Python atual
script_dir = os.path.dirname(os.path.abspath(__file__))

# Caminhos para salvar os arquivos nas pastas corretas
image1_path = os.path.join(script_dir, '../1.jpeg')
image2_path = os.path.join(script_dir, '../2.jpeg')
target_path = os.path.join(script_dir, '../individuals/')

# Imagens desejadas
image1 = Image.open(image1_path)
image2 = Image.open(image2_path)

# Verificar se as imagens têm o mesmo tamanho
if image1.size != image2.size:
    print("Imagens com dimensões diferentes!")
    exit()

width, height = image1.size

# Obtém os valores RGB dos pixels como listas
pixel_values1 = list(image1.getdata())
pixel_values2 = list(image2.getdata())

# Calcule a média dos pixels
average_pixel_values = [
    (
        (p1[0] + p2[0]) // 2,
        (p1[1] + p2[1]) // 2,
        (p1[2] + p2[2]) // 2
    )
    for p1, p2 in zip(pixel_values1, pixel_values2)
]

# Abre o arquivo no modo de escrita
with open(os.path.join(target_path, 'target.txt'), 'w') as file:
    file.write(f"{width} {height}\n")
    for i, pixel in enumerate(average_pixel_values):
        # Escreve uma linha no arquivo no formato desejado (R, G, B)
        file.write(f"{pixel[0]} {pixel[1]} {pixel[2]}")
        if i < len(average_pixel_values) - 1:
            file.write('\n')

print("Arquivo gerado com sucesso!")
print(f'Dimensões: {width}x{height}')
