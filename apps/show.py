from PIL import Image
import os, cv2

print("Loading video...")

# dimensões da imagem
width = 960  # Largura da imagem
height = 600  # Altura da imagem

# Obter o diretório do script Python atual
script_dir = os.path.dirname(os.path.abspath(__file__))

# Caminhos para salvar os arquivos nas pastas corretas
txt_path = os.path.join(script_dir, os.pardir, 'individuals')
pics_path = os.path.join(script_dir, os.pardir, 'pics')

# Listar os arquivos .txt no diretório
txt_files = [f for f in os.listdir(txt_path) if f.endswith('.txt') and f.startswith('file')]

# Iterar sobre os arquivos .txt
for txt_file in txt_files:
    # Construir o caminho completo para o arquivo .txt
    txt_file_path = os.path.join(txt_path, txt_file)

    # Lista para armazenar as triplas RGB lidas do arquivo
    pixel_values = []

    # Abrindo o arquivo de triplas RGB para leitura
    with open(txt_file_path, 'r') as file:
        for line in file:
            # Divida a linha por espaços em branco e converta os valores para inteiros
            values = [int(val) for val in line.strip().split()]
            # Verifique se há três valores (R, G e B)
            if len(values) == 3:
                pixel_values.append(tuple(values))

    # Crie uma nova imagem com base nas triplas RGB
    pic = Image.new('RGB', (width, height))

    # Preencha a imagem com os pixels com base nas triplas RGB lidas
    for x in range(width):
        for y in range(height):
            pixel_index = y * width + x
            if pixel_index < len(pixel_values):
                pixel_color = pixel_values[pixel_index]
                pic.putpixel((x, y), pixel_color)

    # Salve a imagem gerada com um nome correspondente (por exemplo, pic01.png, pic02.png, ...)
    output_image_name = os.path.join(pics_path, f'pic{str(int(os.path.splitext(txt_file)[0][4:])).zfill(3)}.png')
    pic.save(output_image_name, 'PNG')

# Gerando um vídeo a partir das imagens
output_video = 'Evolution.mp4'
fps = 3

images = [img for img in os.listdir(pics_path) if img.endswith(".png") and img.startswith('pic')]
images.sort()

frame = cv2.imread(os.path.join(pics_path, images[0]))

# Use o codec H.264 para o vídeo
fourcc = cv2.VideoWriter_fourcc(*'mp4v')
video = cv2.VideoWriter(output_video, fourcc, fps, (width, height))
for image in images:
    img = cv2.imread(os.path.join(pics_path, image))
    video.write(img)

cv2.destroyAllWindows()
video.release()
