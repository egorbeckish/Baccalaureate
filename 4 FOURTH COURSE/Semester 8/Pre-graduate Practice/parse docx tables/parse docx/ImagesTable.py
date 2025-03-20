import fitz
import os
from PIL import Image

pdf = fitz.open('image.pdf')

pages = len(pdf)

def data_image(image):
    info_image = pdf.extract_image(image[0])
    bytes_image = info_image['image']
    format_image = info_image['ext']
    name_image = f'page_{count_image}.{format_image}'

    return bytes_image, name_image

def exists_folder_images():
    return os.path.exists('images')

def create_folder_images():
    if not exists_folder_images():
        os.mkdir('images')

def save_image(name_image, bytes_image):
    create_folder_images()
    with open(os.path.join('images/', name_image), 'wb') as file_image:
        file_image.write(bytes_image)

count_image = 1
for page in range(pages):
    images = pdf[page].get_images()

    if not images:
        continue

    if len(images) == 1:
        bytes_image, name_image = data_image(images[0])
        save_image(name_image, bytes_image)
        count_image += 1

    else:
        for image in images:
            bytes_image, name_image = data_image(image)
            save_image(name_image, bytes_image)
            count_image += 1
