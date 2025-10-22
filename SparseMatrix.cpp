#include "SparseMatrix.h"
#include <iostream>
#include <ctime>
#include <cstdlib>

SparseMatrix::SparseMatrix() {
    start = nullptr;
    modoPrueba = false; // por defecto imprime mensajes
}

void SparseMatrix::setModoPrueba(bool state) {
    modoPrueba = state;
}

void SparseMatrix::add(int value, int xPos, int yPos) {
    if (xPos < 0 || yPos < 0) {
        if (!modoPrueba)
            std::cout << "Error: Coordenadas negativas no permitidas" << std::endl;
        return;
    }

    Node* actual = start;
    Node* anterior = nullptr;

    while (actual != nullptr) {
        if (actual->xPos == xPos && actual->yPos == yPos) {
            if (value == 0) {
                remove(xPos, yPos);
                if (!modoPrueba)
                    std::cout << "Elemento en (" << xPos << "," << yPos << ") eliminado (valor = 0)" << std::endl;
            } else {
                actual->valor = value;
                if (!modoPrueba)
                    std::cout << "Elemento en (" << xPos << "," << yPos << ") actualizado a " << value << std::endl;
            }
            return;
        }
        if (actual->xPos > xPos || (actual->xPos == xPos && actual->yPos > yPos)) {
            break;
        }

        anterior = actual;
        actual = actual->next;
    }

    if (value == 0) {
        if (!modoPrueba)
            std::cout << "Info: No se crea nodo para valor 0 en (" << xPos << "," << yPos << ")" << std::endl;
        return;
    }

    Node* nuevo = new Node(value, xPos, yPos);
    if (anterior == nullptr) {
        nuevo->next = start;
        start = nuevo;
    } else {
        anterior->next = nuevo;
        nuevo->next = actual;
    }

    if (!modoPrueba)
        std::cout << "Elemento " << value << " agregado en (" << xPos << "," << yPos << ")" << std::endl;
}

int SparseMatrix::get(int xPos, int yPos) {
    if (xPos < 0 || yPos < 0) {
        if (!modoPrueba)
            std::cout << "Error: Coordenadas negativas no permitidas" << std::endl;
        return 0;
    }

    Node* actual = start;

    while (actual != nullptr) {
        if (actual->xPos == xPos && actual->yPos == yPos) {
            return actual->valor;
        }
        if (actual->xPos > xPos || (actual->xPos == xPos && actual->yPos > yPos)) {
            break;
        }
        actual = actual->next;
    }
    return 0;
}

void SparseMatrix::remove(int xPos, int yPos) {
    if (xPos < 0 || yPos < 0) {
        if (!modoPrueba)
            std::cout << "Error: Coordenadas negativas no permitidas" << std::endl;
        return;
    }

    Node* actual = start;
    Node* anterior = nullptr;

    while (actual != nullptr) {
        if (actual->xPos == xPos && actual->yPos == yPos) {
            if (anterior == nullptr) {
                start = actual->next;
            } else {
                anterior->next = actual->next;
            }
            delete actual;
            if (!modoPrueba)
                std::cout << "Elemento en (" << xPos << "," << yPos << ") eliminado exitosamente" << std::endl;
            return;
        }
        if (actual->xPos > xPos || (actual->xPos == xPos && actual->yPos > yPos)) {
            break;
        }
        anterior = actual;
        actual = actual->next;
    }

    if (!modoPrueba)
        std::cout << "Info: No existe elemento en (" << xPos << "," << yPos << ") para eliminar" << std::endl;
}

void SparseMatrix::printStoredValues() {
    Node* actual = start;
    if (actual == nullptr) {
        std::cout << "La matriz esta vacia" << std::endl;
        return;
    }

    std::cout << "=== ELEMENTOS ALMACENADOS ===" << std::endl;
    int contador = 0;
    while (actual != nullptr) {
        std::cout << "(" << actual->xPos << ", " << actual->yPos << ") --> " << actual->valor << std::endl;
        actual = actual->next;
        contador++;
    }
    std::cout << "Total elementos: " << contador << std::endl;
}

int SparseMatrix::density() {
    if (start == nullptr) {
        if (!modoPrueba)
            std::cout << "Densidad: 0% (matriz vacia)" << std::endl;
        return 0;
    }

    int maxX = 0;
    int maxY = 0;
    int cont = 0;

    Node* actual = start;
    while (actual != nullptr) {
        if (actual->xPos > maxX) maxX = actual->xPos;
        if (actual->yPos > maxY) maxY = actual->yPos;
        cont++;
        actual = actual->next;
    }

    int totalElementos = (maxX + 1) * (maxY + 1);
    if (totalElementos == 0) return 0;

    int densidad = (cont * 100) / totalElementos;
    if (!modoPrueba)
        std::cout << "Densidad: " << cont << " elementos / " << totalElementos
                  << " espacios = " << densidad << "%" << std::endl;

    return densidad;
}

SparseMatrix* SparseMatrix::multiply(SparseMatrix* second) {
    SparseMatrix* result = new SparseMatrix();
    result->setModoPrueba(modoPrueba); // hereda modo de impresión

    if (second == nullptr) {
        if (!modoPrueba)
            std::cout << "Error: Matriz nula para multiplicacion" << std::endl;
        return result;
    }

    int maxX1 = 0, maxY1 = 0, maxX2 = 0, maxY2 = 0;

    Node* actual1 = start;
    while (actual1 != nullptr) {
        if (actual1->xPos > maxX1) maxX1 = actual1->xPos;
        if (actual1->yPos > maxY1) maxY1 = actual1->yPos;
        actual1 = actual1->next;
    }

    Node* actual2 = second->start;
    while (actual2 != nullptr) {
        if (actual2->xPos > maxX2) maxX2 = actual2->xPos;
        if (actual2->yPos > maxY2) maxY2 = actual2->yPos;
        actual2 = actual2->next;
    }

    if (maxY1 != maxX2) {
        if (!modoPrueba)
            std::cout << "Error: Dimensiones incompatibles para multiplicacion ("
                      << (maxX1 + 1) << "x" << (maxY1 + 1) << ") * ("
                      << (maxX2 + 1) << "x" << (maxY2 + 1) << ")" << std::endl;
        return result;
    }

    if (!modoPrueba)
        std::cout << "Multiplicando matrices (" << (maxX1 + 1) << "x" << (maxY1 + 1)
                  << ") * (" << (maxX2 + 1) << "x" << (maxY2 + 1) << ")..." << std::endl;

    for (int i = 0; i <= maxX1; i++) {
        for (int j = 0; j <= maxY2; j++) {
            int sum = 0;
            for (int k = 0; k <= maxY1; k++) {
                int val1 = this->get(i, k);
                int val2 = second->get(k, j);
                sum += val1 * val2;
            }
            if (sum != 0) {
                result->add(sum, i, j);
            }
        }
    }

    if (!modoPrueba)
        std::cout << "Multiplicacion completada" << std::endl;

    return result;
}

SparseMatrix::~SparseMatrix() {
    Node* actual = start;
    int contador = 0;
    while (actual != nullptr) {
        Node* temp = actual;
        actual = actual->next;
        delete temp;
        contador++;
    }
    if (!modoPrueba)
        std::cout << "Matriz liberada: " << contador << " nodos eliminados" << std::endl;
}
