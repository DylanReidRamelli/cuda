#!/usr/bin/python
import sys
import matplotlib.pyplot as plt
import numpy as np
from PIL import Image


def write_data():
    image_path_png = "../../Images/Roberts-Claude-Shannon-1.jpg"
    original_png_data = Image.open(image_path_png).convert('L')
    numpy_data = np.asarray(original_png_data)
    numpy_data = numpy_data.astype(np.float32)
    numpy_data = np.reshape(numpy_data, (numpy_data.shape[0] * numpy_data.shape[1],))
    print(numpy_data.shape)
    print(numpy_data)
    numpy_data.tofile("../../Images/data_roberts.raw")


def read_data(image_path):
    nx = 1303
    ny = 2000

    # Load the data from the file
    data = np.fromfile(image_path, dtype=np.float32)
    n = nx * ny
    data = np.reshape(data, (ny, nx))

    print(data)


    plt.title("Original Image")
    plt.xlabel("X pixel scaling.")
    plt.ylabel("Y pixel scaling.")

    # Visualize the data as an image
    plt.imshow(data, cmap='gray')
    plt.show()



def read_data_no_loss(image_path, image_info):
    f = open(image_info)
    line = f.readlines()
    line = line[0].split(',')
    nx = int(line[0])
    ny = int(line[1])
    n = nx * ny

    print(nx,ny)

    # Load the data from the file
    data = np.fromfile(image_path, dtype=np.float32)
    data = np.reshape(data, (ny, nx))

    print(data)


    plt.title("Original Image")
    plt.xlabel("X pixel scaling.")
    plt.ylabel("Y pixel scaling.")

    # Visualize the data as an image
    plt.imshow(data, cmap='gray')
    plt.show()



def read_data_no_loss(image_path, image_info, image_n):
    f = open(image_info)
    line = f.readlines()
    line = line[0].split(',')
    nx = int(line[0])
    ny = int(line[1])
    n = nx * ny

    print(nx,ny)

    # Load the data from the file
    data = np.fromfile(image_path, dtype=np.float32)
    data = np.reshape(data, (ny, nx))

    print(data)


    plt.title("Rotation")
    plt.xlabel("X pixel scaling.")
    plt.ylabel("Y pixel scaling.")
    print("Image: "+ image_n)

    # Visualize the data as an image
    plt.imshow(data, cmap='gray')
    # plt.show()
    plt.savefig("output_images/image_" + image_n)



if __name__ == "__main__":
    # write_data()
    # main()
    if len(sys.argv) == 3:
        read_data_no_loss(sys.argv[1], sys.argv[2])

    elif len(sys.argv) == 4:
        read_data_no_loss(sys.argv[1], sys.argv[2], sys.argv[3])
    else:
        read_data(sys.argv[1])
