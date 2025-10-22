#include "SparseMatrix.h"
#include <iostream>

SparseMatrix::SparseMatrix() {
    start = nullptr;
}

void SparseMatrix::add(int value, int xPos, int yPos) {
    if(xPos<0 || yPos<0) { return; }

    Node* actual = start;
    Node* anterior = nullptr;

    while(actual != nullptr){
        if(actual->xPos == xPos && actual->yPos == yPos){
            if (value == 0)
            {
                remove(xPos, yPos);
            }
            else
            {
                actual->valor = value;
            }
            return;
            
        }
        if(actual->xPos > xPos || (actual->xPos == xPos && actual->yPos > yPos)){
            break;
        }

        anterior = actual;
        actual = actual->next;  
    }
    if (value == 0)
    {
        return;
    }

    Node* nuevo = new Node(value, xPos, yPos);
    if (anterior == nullptr)
    {
        nuevo->next = start;
        start = nuevo;
    }
    else
    {
        anterior->next = nuevo;
        nuevo->next = actual;
    }
}

int SparseMatrix::get(int xPos, int yPos) {
    Node* actual = start;

    while(actual != nullptr){
        if(actual->xPos == xPos && actual->yPos == yPos){
            return actual->valor;
        }
        if(actual->xPos > xPos || (actual->xPos == xPos && actual->yPos > yPos)){
            break;
        }
        actual = actual->next;  
    }
    return 0;
    
}

void SparseMatrix::remove(int xPos, int yPos) {
    Node* actual = start;
    Node* anterior = nullptr;

    while(actual != nullptr){
        if(actual->xPos == xPos && actual->yPos == yPos){
            if (anterior == nullptr)
            {
                start = actual->next;
            }
            else
            {
                anterior->next = actual->next;
            }
            delete actual;
            return;
        }
        if(actual->xPos > xPos || (actual->xPos == xPos && actual->yPos > yPos)){
            break;
        }
        anterior = actual;
        actual = actual->next;  
    }
   
}

void SparseMatrix::printStoredValues() {
    Node* actual = start;
    if(actual == nullptr){
        std::cout << "La matriz esta vacia" << std::endl;
    } 
    while(actual != nullptr){
        std::cout << "Valor: " << actual->valor << " Posicion: (" << actual->xPos << ", " << actual->yPos << ")" << std::endl;
        actual = actual->next;  
    }  
}

int SparseMatrix::density() {
    if(start == nullptr) { return 0; }
    int maxX = 0;
    int maxY = 0;
    int cont = 0;

    Node* actual = start;
    while(actual != nullptr){
        if(actual->xPos > maxX){
            maxX = actual->xPos;
        }
        if(actual->yPos > maxY){
            maxY = actual->yPos;
        }
        cont++;
        actual = actual->next;  
    }
    int totalElementos = (maxX + 1) * (maxY + 1);
    if(totalElementos == 0) { return 0; }
    return (cont * 100) / totalElementos;

   
}

SparseMatrix* SparseMatrix::multiply(SparseMatrix* second) {
    SparseMatrix* result = new SparseMatrix();

    if(second == nullptr) { return result; }

    int maxX1 = 0;
    int maxY1 = 0;
    Node *actual1 = start;
    while(actual1 != nullptr){
        if(actual1->xPos > maxX1){
            maxX1 = actual1->xPos;
        }
        if(actual1->yPos > maxY1){
            maxY1 = actual1->yPos;
        }
        actual1 = actual1->next;
    }

    int maxX2 = 0;
    int maxY2 = 0;
    Node *actual2 = second->start;
    while(actual2 != nullptr){
        if(actual2->xPos > maxX2){
            maxX2 = actual2->xPos;
        }
        if(actual2->yPos > maxY2){
            maxY2 = actual2->yPos;
        }
        actual2 = actual2->next;
    }
    if (maxY1 != maxX2) { return result; }

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

}

SparseMatrix::~SparseMatrix() {
    Node* actual = start;
    while(actual != nullptr){
        Node* temp = actual;
        actual = actual->next;
        delete temp;
        actual = temp;
    }

   
}
