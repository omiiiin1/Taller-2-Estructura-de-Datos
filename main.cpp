#include <iostream>
#include "SparseMatrix.h"
#include <ctime>
#include <cstdlib>
#include <cmath>

using namespace std;

void mostrarMenu();
void agregarElemento(SparseMatrix& matriz);
void obtenerElemento(SparseMatrix& matriz);
void eliminarElemento(SparseMatrix& matriz);
void pruebaRendimientoCompleto();
bool generarCoordenadaUnica(int x, int y, bool** ocupadas, int maxCoord);

bool generarCoordenadaUnica(int x, int y, bool** ocupadas, int maxCoord) {
    if (x >= maxCoord || y >= maxCoord) return false;
    if (!ocupadas[x][y]) {
        ocupadas[x][y] = true;
        return true;
    }
    return false;
}

int main() {
    SparseMatrix matrizPrincipal;
    int opcion;

    do {
        mostrarMenu();
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        clock_t inicio, fin;
        double tiempo;

        switch (opcion) {
            case 1: {
                inicio = clock();
                agregarElemento(matrizPrincipal);
                fin = clock();
                tiempo = double(fin - inicio) / CLOCKS_PER_SEC;
                cout << "Tiempo de ejecucion: " << tiempo << " segundos" << endl;
                break;
            }
            case 2: {
                inicio = clock();
                obtenerElemento(matrizPrincipal);
                fin = clock();
                tiempo = double(fin - inicio) / CLOCKS_PER_SEC;
                cout << "Tiempo de ejecucion: " << tiempo << " segundos" << endl;
                break;
            }
            case 3: {
                inicio = clock();
                eliminarElemento(matrizPrincipal);
                fin = clock();
                tiempo = double(fin - inicio) / CLOCKS_PER_SEC;
                cout << "Tiempo de ejecucion: " << tiempo << " segundos" << endl;
                break;
            }
            case 4: {
                inicio = clock();
                matrizPrincipal.printStoredValues();
                fin = clock();
                tiempo = double(fin - inicio) / CLOCKS_PER_SEC;
                cout << "Tiempo de ejecucion: " << tiempo << " segundos" << endl;
                break;
            }
            case 5: {
                inicio = clock();
                int densidad = matrizPrincipal.density();
                fin = clock();
                tiempo = double(fin - inicio) / CLOCKS_PER_SEC;
                cout << "La densidad de la matriz es: " << densidad << "%" << endl;
                cout << "Tiempo de ejecucion: " << tiempo << " segundos" << endl;
                break;
            }
            case 6: {
                SparseMatrix segundaMatriz;
                cout << "Ingrese los elementos de la segunda matriz dispersa:" << endl;
                agregarElemento(segundaMatriz);

                inicio = clock();
                SparseMatrix* resultado = matrizPrincipal.multiply(&segundaMatriz);
                fin = clock();
                tiempo = double(fin - inicio) / CLOCKS_PER_SEC;

                cout << "Resultado de la multiplicacion:" << endl;
                resultado->printStoredValues();
                cout << "Tiempo de ejecucion de multiplicacion: " << tiempo << " segundos" << endl;

                delete resultado;
                break;
            }
            case 7: {
                pruebaRendimientoCompleto();
                break;
            }
            case 0: {
                cout << "Saliendo del sistema." << endl;
                break;
            }
            default: {
                cout << "Opcion invalida. Intente de nuevo." << endl;
                break;
            }
        }
        cout << "----------------------------------------" << endl;
    } while (opcion != 0);

    return 0;
}

void mostrarMenu() {
    cout << "\n**** Sistema de Matrices Poco Pobladas ****" << endl;
    cout << "1. Agregar dato " << endl;
    cout << "2. Obtener dato " << endl;
    cout << "3. Eliminar dato " << endl;
    cout << "4. Imprimir datos almacenados " << endl;
    cout << "5. Calcular densidad " << endl;
    cout << "6. Multiplicar por otra matriz " << endl;
    cout << "7. Ejecutar pruebas de rendimiento" << endl;
    cout << "0. Salir del sistema" << endl;
}

void agregarElemento(SparseMatrix& matriz) {
    int valor, xPos, yPos;
    cout << "Ingrese el valor a agregar: ";
    cin >> valor;
    cout << "Ingrese la posicion X: ";
    cin >> xPos;
    cout << "Ingrese la posicion Y: ";
    cin >> yPos;
    matriz.add(valor, xPos, yPos);
    cout << "Elemento agregado." << endl;
}

void obtenerElemento(SparseMatrix& matriz) {
    int xPos, yPos;
    cout << "Ingrese la posicion X del elemento a obtener: ";
    cin >> xPos;
    cout << "Ingrese la posicion Y del elemento a obtener: ";
    cin >> yPos;
    int valor = matriz.get(xPos, yPos);
    if (valor != 0) {
        cout << "El valor en la posicion (" << xPos << ", " << yPos << ") es: " << valor << endl;
    } else {
        cout << "No hay elemento almacenado en la posicion (" << xPos << ", " << yPos << ")." << endl;
    }
}

void eliminarElemento(SparseMatrix& matriz) {
    int xPos, yPos;
    cout << "Ingrese la posicion X del elemento a eliminar: ";
    cin >> xPos;
    cout << "Ingrese la posicion Y del elemento a eliminar: ";
    cin >> yPos;
    matriz.remove(xPos, yPos);
    cout << "Elemento eliminado si existia." << endl;
}

// --------------------------- PRUEBAS DE RENDIMIENTO -----------------------------

void pruebaAdd(int cantidadDatos, double densidadObjetivo, int numeroPrueba) {
    SparseMatrix matriz;
    matriz.setModoPrueba(true); 

    srand(time(nullptr));
    int dimension = (int)(sqrt(cantidadDatos / densidadObjetivo)) + 1;
    if (dimension < 10) dimension = 10;

    bool** ocupadas = new bool*[dimension];
    for (int i = 0; i < dimension; i++) ocupadas[i] = new bool[dimension]();

    clock_t inicio = clock();
    int insertados = 0, intentos = 0, maxIntentos = cantidadDatos * 10;

    while (insertados < cantidadDatos && intentos < maxIntentos) {
        int x = rand() % dimension;
        int y = rand() % dimension;
        int valor = rand() % 100 + 1;

        if (generarCoordenadaUnica(x, y, ocupadas, dimension)) {
            matriz.add(valor, x, y);
            insertados++;
        }
        intentos++;
    }

    clock_t fin = clock();
    double tiempo = double(fin - inicio) / CLOCKS_PER_SEC;

    cout << "Prueba " << numeroPrueba << " - ADD: " << cantidadDatos
         << " datos, Densidad " << (densidadObjetivo * 100)
         << "%, Tiempo: " << tiempo << "s, Insertados: "
         << insertados << "/" << cantidadDatos << endl;

    for (int i = 0; i < dimension; i++) delete[] ocupadas[i];
    delete[] ocupadas;
}

void pruebaGet(int cantidadDatos, double densidadObjetivo, int numeroPrueba) {
    SparseMatrix matriz;
    matriz.setModoPrueba(true);

    srand(time(nullptr));
    int dimension = (int)(sqrt(cantidadDatos / densidadObjetivo)) + 1;
    if (dimension < 10) dimension = 10;

    bool** ocupadas = new bool*[dimension];
    for (int i = 0; i < dimension; i++) ocupadas[i] = new bool[dimension]();

    int insertados = 0, intentos = 0, maxIntentos = cantidadDatos * 10;
    while (insertados < cantidadDatos && intentos < maxIntentos) {
        int x = rand() % dimension;
        int y = rand() % dimension;
        int valor = rand() % 100 + 1;
        if (generarCoordenadaUnica(x, y, ocupadas, dimension)) {
            matriz.add(valor, x, y);
            insertados++;
        }
        intentos++;
    }

    clock_t inicio = clock();
    for (int i = 0; i < 1000; i++) {
        matriz.get(rand() % dimension, rand() % dimension);
    }
    clock_t fin = clock();
    double tiempo = double(fin - inicio) / CLOCKS_PER_SEC;

    cout << "Prueba " << numeroPrueba << " - GET: " << cantidadDatos
         << " datos, Densidad " << (densidadObjetivo * 100)
         << "%, Tiempo: " << tiempo << "s (1000 operaciones)" << endl;

    for (int i = 0; i < dimension; i++) delete[] ocupadas[i];
    delete[] ocupadas;
}

void pruebaMultiply(int cantidadDatos, double densidadObjetivo, int numeroPrueba) {
    SparseMatrix matrizA, matrizB;
    matrizA.setModoPrueba(true);
    matrizB.setModoPrueba(true);

    srand(time(nullptr));
    int dimension = (int)(sqrt(cantidadDatos / densidadObjetivo)) + 1;
    if (dimension < 10) dimension = 10;

    bool** ocupadasA = new bool*[dimension];
    for (int i = 0; i < dimension; i++) ocupadasA[i] = new bool[dimension]();

    bool** ocupadasB = new bool*[dimension];
    for (int i = 0; i < dimension; i++) ocupadasB[i] = new bool[dimension]();

    int insertadosA = 0, intentosA = 0, insertadosB = 0, intentosB = 0;
    int maxIntentos = cantidadDatos * 10;

    while (insertadosA < cantidadDatos && intentosA < maxIntentos) {
        if (generarCoordenadaUnica(rand() % dimension, rand() % dimension, ocupadasA, dimension)) {
            matrizA.add(rand() % 10 + 1, rand() % dimension, rand() % dimension);
            insertadosA++;
        }
        intentosA++;
    }

    while (insertadosB < cantidadDatos && intentosB < maxIntentos) {
        if (generarCoordenadaUnica(rand() % dimension, rand() % dimension, ocupadasB, dimension)) {
            matrizB.add(rand() % 10 + 1, rand() % dimension, rand() % dimension);
            insertadosB++;
        }
        intentosB++;
    }

    clock_t inicio = clock();
    SparseMatrix* resultado = matrizA.multiply(&matrizB);
    clock_t fin = clock();
    double tiempo = double(fin - inicio) / CLOCKS_PER_SEC;

    cout << "Prueba " << numeroPrueba << " - MULTIPLY: " << cantidadDatos
         << " datos, Densidad " << (densidadObjetivo * 100)
         << "%, Tiempo: " << tiempo << "s" << endl;

    delete resultado;

    for (int i = 0; i < dimension; i++) {
        delete[] ocupadasA[i];
        delete[] ocupadasB[i];
    }
    delete[] ocupadasA;
    delete[] ocupadasB;
}

void pruebaRendimientoCompleto() {
    cout << "\n=== PRUEBAS DE RENDIMIENTO===" << endl;

    int setsDatos[] = {50, 250, 500, 1000, 5000};
    double densidades[] = {0.2, 0.7};

    srand(time(nullptr));

    cout << "\n--- Pruebas ADD ---" << endl;
    int pruebaCount = 1;
    for (int cantidad : setsDatos)
        for (double densidad : densidades)
            for (int muestra = 0; muestra < 2; muestra++)
                pruebaAdd(cantidad, densidad, pruebaCount++);

    cout << "\n--- Pruebas GET ---" << endl;
    pruebaCount = 1;
    for (int cantidad : setsDatos)
        for (double densidad : densidades)
            for (int muestra = 0; muestra < 2; muestra++)
                pruebaGet(cantidad, densidad, pruebaCount++);

    cout << "\n--- Pruebas MULTIPLY ---" << endl;
    pruebaCount = 1;
    for (int cantidad : setsDatos)
        for (double densidad : densidades)
            for (int muestra = 0; muestra < 2; muestra++)
                pruebaMultiply(cantidad, densidad, pruebaCount++);

    cout << "\n=== TODAS LAS PRUEBAS COMPLETADAS ===" << endl;
}
