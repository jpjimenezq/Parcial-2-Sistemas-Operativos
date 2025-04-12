#include "imagen.h"
#include "stb_image.h"
#include "stb_image_write.h"
#include <iostream>
#include <cmath>
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

using namespace std;

// ✅ Implementación del constructor
Imagen::Imagen(const std::string &nombreArchivo, BuddyAllocator *allocador)
    : allocador(allocador) {

    unsigned char* buffer = stbi_load(nombreArchivo.c_str(), &ancho, &alto, &canales, 0);
    if (!buffer) {
        cerr << "Error: No se pudo cargar la imagen '" << nombreArchivo << "'.\n";
        exit(1);
    }

    convertirBufferAMatriz(buffer);
    stbi_image_free(buffer);
}

// ✅ Implementación del destructor
Imagen::~Imagen() {
    if (!allocador) {
        for (int y = 0; y < alto; y++) {
            for (int x = 0; x < ancho; x++) {
                delete[] pixeles[y][x];
            }
            delete[] pixeles[y];
        }
        delete[] pixeles;
    }
}

// ✅ Implementación de convertirBufferAMatriz()
void Imagen::convertirBufferAMatriz(unsigned char* buffer) {
    int indice = 0;
    pixeles = new unsigned char**[alto];

    for (int y = 0; y < alto; y++) {
        pixeles[y] = new unsigned char*[ancho];
        for (int x = 0; x < ancho; x++) {
            pixeles[y][x] = new unsigned char[canales];
            for (int c = 0; c < canales; c++) {
                pixeles[y][x][c] = buffer[indice++];
            }
        }
    }
}

// ✅ Implementación de mostrarInfo()
void Imagen::mostrarInfo() const {
    cout << "Dimensiones: " << ancho << " x " << alto << endl;
    cout << "Canales: " << canales << endl;
}

// ✅ Implementación de guardarImagen()
void Imagen::guardarImagen(const std::string &nombreArchivo) const {
    unsigned char* buffer = new unsigned char[alto * ancho * canales];
    int indice = 0;

    for (int y = 0; y < alto; y++) {
        for (int x = 0; x < ancho; x++) {
            for (int c = 0; c < canales; c++) {
                buffer[indice++] = pixeles[y][x][c];
            }
        }
    }

    if (!stbi_write_png(nombreArchivo.c_str(), ancho, alto, canales, buffer, ancho * canales)) {
        cerr << "Error: No se pudo guardar la imagen en '" << nombreArchivo << "'.\n";
        delete[] buffer;
        exit(1);
    }

    delete[] buffer;
    cout << "[INFO] Imagen guardada correctamente en '" << nombreArchivo << "'.\n";
}

void Imagen::invertirColores() {
    for (int y = 0; y < alto; y++) {
        for (int x = 0; x < ancho; x++) {
            for (int c = 0; c < canales; c++) {
                pixeles[y][x][c] = 255 - pixeles[y][x][c];
            }
        }
    }
}

void Imagen::rotar() {
    unsigned char*** nuevaMatriz = new unsigned char**[ancho];
    for (int x = 0; x < ancho; x++) {
        nuevaMatriz[x] = new unsigned char*[alto];
        for (int y = 0; y < alto; y++) {
            nuevaMatriz[x][y] = new unsigned char[canales];
            for (int c = 0; c < canales; c++) {
                nuevaMatriz[x][y][c] = pixeles[alto - 1 - y][x][c];
            }
        }
    }

    // Liberar la matriz actual
    for (int y = 0; y < alto; y++) {
        for (int x = 0; x < ancho; x++) {
            delete[] pixeles[y][x];
        }
        delete[] pixeles[y];
    }
    delete[] pixeles;

    // Actualizar puntero y dimensiones
    std::swap(ancho, alto);
    pixeles = nuevaMatriz;
}

void Imagen::escalar(float factor) {
    int nuevoAncho = static_cast<int>(ancho * factor);
    int nuevoAlto = static_cast<int>(alto * factor);

    unsigned char*** nuevaMatriz = new unsigned char**[nuevoAlto];
    for (int y = 0; y < nuevoAlto; y++) {
        nuevaMatriz[y] = new unsigned char*[nuevoAncho];
        for (int x = 0; x < nuevoAncho; x++) {
            int origenY = std::min(static_cast<int>(y / factor), alto - 1);
            int origenX = std::min(static_cast<int>(x / factor), ancho - 1);

            nuevaMatriz[y][x] = new unsigned char[canales];
            for (int c = 0; c < canales; c++) {
                nuevaMatriz[y][x][c] = pixeles[origenY][origenX][c];
            }
        }
    }

    // Liberar la matriz actual
    for (int y = 0; y < alto; y++) {
        for (int x = 0; x < ancho; x++) {
            delete[] pixeles[y][x];
        }
        delete[] pixeles[y];
    }
    delete[] pixeles;

    // Actualizar puntero y dimensiones
    pixeles = nuevaMatriz;
    ancho = nuevoAncho;
    alto = nuevoAlto;
}
