#include <iostream>
#include "SparseMatrix.h"
#include <ctime>
#include <limits>

using namespace std;

void mostrarMenu();

int main() {
    SparseMatrix matrizPrincipal;
    int opcion;

    do {
        mostrarMenu();
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1: {
                agregarElemento(matrizPrincipal);
                break;
            }
            case 2: {
                obtenerElemento(matrizPrincipal);
                break;
            }
            case 3: {
                eliminarElemento(matrizPrincipal);
                break;
            }
            case 4: {
                matrizPrincipal.printStoredValues();
                break;
            }
            case 5: {
                int densidad = matrizPrincipal.density();
                cout << "La densidad de la matriz es: " << densidad << "%" << endl;
                break;
            }
            case 6: {
                SparseMatrix segundaMatriz;
                cout << "Ingrese los elementos de la segunda matriz dispersa:" << endl;
                agregarElemento(segundaMatriz);
                SparseMatrix* resultado = matrizPrincipal.multiply(&segundaMatriz);
                cout << "Resultado de la multiplicacion:" << endl;
                resultado->printStoredValues();
                delete resultado;
                break;
            }
            case 7: {
                cout << "Saliendo del programa." << endl;
                break;
            }
            default: {
                cout << "Opcion invalida. Intente de nuevo." << endl;
                break;
            }
        }
    } while (opcion != 7);

    return 0;
}

void mostrarMenu() {
    cout << "**** Sistema de Matrices Poco Pobladas ****" << endl;
    cout << "1. Agregar dato" << endl;
    cout << "2. Obtener dato" << endl;
    cout << "3. Eliminar dato" << endl;
    cout << "4. Imprimir datos almacenados" << endl;
    cout << "5. Calcular densidad" << endl;
    cout << "6. Multiplicar por otra matriz dispersa" << endl;
    cout << "7. Salir" << endl;
}

void agregarElemento(SparseMatrix &m) {
    int valor, x, y;
    cout << "Ingrese valor, fila (x) y columna (y) separados por espacios: ";
    if (!(cin >> valor >> x >> y)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Entrada invalida." << endl;
        return;
    }
    m.add(valor, x, y);
}

void obtenerElemento(SparseMatrix &m) {
    int x, y;
    cout << "Ingrese fila (x) y columna (y): ";
    if (!(cin >> x >> y)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Entrada invalida." << endl;
        return;
    }
    int val = m.get(x, y);
    cout << "Valor en (" << x << "," << y << ") = " << val << endl;
}

void eliminarElemento(SparseMatrix &m) {
    int x, y;
    cout << "Ingrese fila (x) y columna (y) a eliminar: ";
    if (!(cin >> x >> y)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Entrada invalida." << endl;
        return;
    }
    m.remove(x, y);
}
