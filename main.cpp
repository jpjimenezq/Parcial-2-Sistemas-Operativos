#include "imagen.h"
#include "buddy_allocator.h"
#include <iostream>
#include <chrono>
#include <cstring>
#include <cstdlib>

using namespace std;
using namespace std::chrono;

void mostrarUso() {
    cout << "Uso: ./programa_imagen <entrada> <salida> -angulo <grados> -escalar <factor> <-buddy|-no-buddy>\n";
    cout << "Ejemplo: ./programa_imagen entrada.jpg salida.jpg -angulo 90 -escalar 1.5 -buddy\n";
}

void mostrarListaChequeo(const string &entrada, const string &salida, float angulo, float escala, bool usarBuddy) {
    cout << "\n=== LISTA DE CHEQUEO ===\n";
    cout << "Archivo de entrada : " << entrada << endl;
    cout << "Archivo de salida  : " << salida << endl;
    cout << "Ángulo de rotación : " << angulo << "°" << endl;
    cout << "Factor de escala   : " << escala << endl;
    cout << "Modo de asignación : " << (usarBuddy ? "Buddy System" : "new/delete") << endl;
    cout << "------------------------\n";
}

int main(int argc, char* argv[]) {
    if (argc != 8) {
        cerr << "Error: Número incorrecto de argumentos.\n";
        mostrarUso();
        return 1;
    }

    string archivoEntrada = argv[1];
    string archivoSalida = argv[2];
    string opcionAngulo = argv[3];
    float angulo = atof(argv[4]);
    string opcionEscala = argv[5];
    float factorEscala = atof(argv[6]);
    string modoAsignacion = argv[7];

    if (opcionAngulo != "-angulo" || opcionEscala != "-escalar") {
        cerr << "Error: Opciones '-angulo' y '-escalar' requeridas.\n";
        mostrarUso();
        return 1;
    }

    bool usarBuddy = false;
    if (modoAsignacion == "-buddy") usarBuddy = true;
    else if (modoAsignacion != "-no-buddy") {
        cerr << "Error: Opción de asignación inválida.\n";
        mostrarUso();
        return 1;
    }

    mostrarListaChequeo(archivoEntrada, archivoSalida, angulo, factorEscala, usarBuddy);
    auto inicio = high_resolution_clock::now();

    if (usarBuddy) {
        BuddyAllocator allocador(32 * 1024 * 1024);
        Imagen img(archivoEntrada, &allocador);

        if (static_cast<int>(angulo) % 360 != 0) img.rotar();

        if (factorEscala != 1.0f) {
            cout << "\n[ANTES DE ESCALAR]\n";
            img.mostrarInfo();
            img.escalar(factorEscala);
            cout << "\n[DESPUÉS DE ESCALAR]\n";
            img.mostrarInfo();
        }

        img.guardarImagen(archivoSalida);
    } else {
        Imagen img(archivoEntrada);

        if (static_cast<int>(angulo) % 360 != 0) img.rotar();

        if (factorEscala != 1.0f) {
            cout << "\n[ANTES DE ESCALAR]\n";
            img.mostrarInfo();
            img.escalar(factorEscala);
            cout << "\n[DESPUÉS DE ESCALAR]\n";
            img.mostrarInfo();
        }

        img.guardarImagen(archivoSalida);
    }

    auto fin = high_resolution_clock::now();
    auto duracion = duration_cast<milliseconds>(fin - inicio).count();

    cout << "\nTiempo total de procesamiento: " << duracion << " ms\n";
    cout << "[INFO] Proceso completado con éxito.\n";
    return 0;
}
